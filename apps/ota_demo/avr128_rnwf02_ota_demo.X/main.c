 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
? [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include <string.h>
#include <stdlib.h>

#include "SST25WF080B_functions.h"
#include "mcc_generated_files/reset/rstctrl.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_system_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_ota_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_provision_service.h"

/*
    Main application
*/

#define OTA_FLASH_IMAGE_START       (0x00000000)

uint8_t hex_ascii[0x10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

typedef enum {
    APP_WIFI_INIT,
    APP_OTA_INIT,
    APP_OTA_CFG,
    APP_OTA_FW,
    APP_OTA_FS,
    APP_OTA_DFU_FW,
    APP_OTA_DFU_FS,            
    APP_OTA_WAIT,    
    APP_OTA_NONE,
}APP_STATE_t;
//
//RNWF_OTA_CFG_t ota_cfg = {
//    .mode = RNWF_OTA_MODE_HTTP,
//    .file = OTA_CFG_FILE,
//    .socket.tls_conf = 0,
//};

/* Wi-Fi Configuration */
#define HOME_AP_SSID        "wsn"
#define HOME_AP_PASSPHRASE  "brucenegley"
#define HOME_AP_SECURITY    RNWF_WPA2_MIXED

uint8_t app_buf[OTA_BUF_LEN_MAX];


void APP_SW_RESET_Handler(void)
{
//    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_RESET, NULL);    
    DFU_Reset();            
    DELAY_milliseconds(5000);    
    RSTCTRL_reset();    
}

void APP_WIFI_Callback(RNWF_WIFI_EVENT_t event, uint8_t *p_str)
{        
    switch(event)
    {
        case RNWF_CONNECTED:
            printf("Wi-Fi Connected\n");            
            break;
        case RNWF_DISCONNECTED:
            printf("Wi-Fi Disconnected\nReconnecting... \n");
            RNWF_WIFI_SrvCtrl(RNWF_STA_CONNECT, NULL);
            break;
        case RNWF_DHCP_DONE:
            printf("DHCP IP:%s\n", &p_str[2]);                           
            // Enable OTA by passing the OTA buffer space
            if(RNWF_OTA_SrvCtrl(RNWF_OTA_ENABLE, (void *)app_buf) == RNWF_PASS)
            {
                printf("Successfully Enabled the OTA\r\n");
            }
            else
            {
                printf("Enable to enable the OTA\r\n");
            }
            break;
        default:
            break;                    
    }    
}

void APP_OTA_Program(uint32_t flash_addr, uint32_t flash_size)
{    
    RNWF_OTA_CHUNK_t ota_chunk = { .chunk_addr = 0x60000000, .chunk_ptr = app_buf, .chunk_size = flash_size};
    printf("Triggering DFU %lu\r\n", flash_size);
    RNWF_OTA_SrvCtrl(RNWF_OTA_DFU_INIT, (void *)NULL);            
    while(RNWF_OTA_SrvCtrl(RNWF_OTA_DFU_ERASE, (void *)&ota_chunk) != RNWF_PASS);
    while(flash_size)
    {                
        ota_chunk.chunk_size = (flash_size < OTA_BUF_LEN_MAX)?flash_size:OTA_BUF_LEN_MAX;                 
        HighSpeed_Read_Cont(flash_addr, ota_chunk.chunk_size, (char *)app_buf);                    
        RNWF_OTA_SrvCtrl(RNWF_OTA_DFU_WRITE, (void *)&ota_chunk);
        flash_size -= ota_chunk.chunk_size;
        ota_chunk.chunk_addr += ota_chunk.chunk_size;
        flash_addr += ota_chunk.chunk_size;
        printf("Remaining %lu bytes\r\n", flash_size);  
    }
}

void APP_OTA_Callback(RNWF_OTA_EVENT_t event, void *p_str)
{
    static uint32_t flash_addr = OTA_FLASH_IMAGE_START;
    switch(event)
    {
        case RNWF_EVENT_MAKE_UART:
            break;
        case RNWF_EVENT_DWLD_START:
        {
            printf("Total Size = %lu\r\n", *(uint32_t *)p_str); 
            printf("Erasing the SPI Flash\r\n");
            WREN();
            Chip_Erase();
            Wait_Busy();
            SPI_Global_Block_Protection_Unlock();
            printf("Erasing Complete!\r\n"); 
        }
        break;
        case RNWF_EVENT_DWLD_DONE:
        {                                                            
            printf("Download Success!= %lu bytes\r\n", *(uint32_t *)p_str);  
            APP_OTA_Program(OTA_FLASH_IMAGE_START, *(uint32_t *)p_str);
            APP_SW_RESET_Handler();
        }
        break;        
        case RNWF_EVENT_FILE_CHUNK:
        {
            volatile RNWF_OTA_CHUNK_t *ota_chunk = (RNWF_OTA_CHUNK_t *)p_str;               
            Sector_Program(flash_addr, ota_chunk->chunk_ptr, ota_chunk->chunk_size);            
            flash_addr += ota_chunk->chunk_size;
        }    
        break;  
        case RNWF_EVENT_DWLD_FAIL:
        {
            WREN();
            Chip_Erase();
            Wait_Busy();            
        }
        break;
        
        default:
            break;
    }
    
}

int main(void)
{
    uint8_t Device_Id=0x00;
    uint8_t Device_Type=0x00;    
    uint8_t Manufacturer_Id=0x00;    
    RNWF_OTA_HDR_t otaHdr;
    
    SYSTEM_Initialize();
    PB2_SetInterruptHandler(APP_SW_RESET_Handler);
    
    printf("%s", "##############################################\n");
    printf("%s", "  Welcome RNWF02 WiFi Host Assisted OTA Demo  \n");
    printf("%s", "##############################################\n");            
    
           
    Jedec_ID_Read(&Manufacturer_Id, &Device_Type, &Device_Id); 
    printf("SPI Manufacturer ID = 0x%02X\r\n", Manufacturer_Id);
    printf("SPI Device Type = 0x%02X\r\n", Device_Type);
    printf("SPI Device ID = 0x%02X\r\n", Device_Id); 
    if((Device_Id != SST25WF080B_ID) && (Device_Id != SST26VF016B_ID) && (Device_Id != SST26VF064B_ID))    
    {
        printf("No valid SPI Flash found!\r\nConnect SPI MikroBus on slot1 and reset!\r\n");
        while(1);
    }
                        
    RNWF_IF_Init();  
                         
    if(RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SW_REV, app_buf) != RNWF_PASS)
    {        
        HighSpeed_Read_Cont(OTA_FLASH_IMAGE_START, sizeof(RNWF_OTA_HDR_t), (char *)&otaHdr.seq_num);
        printf("Image details in the Flash\r\n");
        printf("Sequence Number 0x%X\r\n", (unsigned int)otaHdr.seq_num);
        printf("Start Address 0x%X\r\n", (unsigned int)otaHdr.start_addr);
        printf("Image Length 0x%X\r\n", (unsigned int)otaHdr.img_len);
        if(otaHdr.seq_num != 0xFFFFFFFF && otaHdr.start_addr != 0xFFFFFFFF && otaHdr.img_len != 0xFFFFFFFF)        
        {                         
            APP_OTA_Program(OTA_FLASH_IMAGE_START, otaHdr.img_len);
        }
        else
        {
            printf("Error: Module is Bricked!");
        }        
    }
    else
    {
        printf("Software Revision: %s\n", app_buf);
    }
        
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_DEV_INFO, app_buf);
    printf("Device Info: %s\n", app_buf);            
        
    RNWF_SYSTEM_SrvCtrl(RWWF_SYSTEM_GET_WIFI_INFO, app_buf);    
    printf("%s\n", app_buf);
             
    /* Wi-Fii Connectivity */
    RNWF_WIFI_PARAM_t wifi_sta_cfg = {RNWF_WIFI_MODE_STA, HOME_AP_SSID, HOME_AP_PASSPHRASE, HOME_AP_SECURITY, 1};
    printf("Connecting to %s\r\n", HOME_AP_SSID);
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);

    RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_sta_cfg);
            
    //RNWF_OTA_SrvCtrl(RNWF_OTA_CONFIG, (void *)&ota_cfg);    
    RNWF_OTA_SrvCtrl(RNWF_OTA_SET_CALLBACK, (void *)APP_OTA_Callback);
    
        
    while(1)
    {          
            RNWF_EVENT_Handler();
    }      
}