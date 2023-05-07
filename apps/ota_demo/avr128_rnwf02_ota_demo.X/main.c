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

#define OTA_SERVER              "192.168.1.128"//"172.31.98.135"//
#define OTA_PORT                8000


RNWF_OTA_CFG_t ota_cfg = {
    .mode = RNWF_OTA_MODE_HTTP,
    .url = OTA_SERVER,       
    .port = OTA_PORT, 
    .socket.tls_conf = 0,
};

/* Wi-Fi Configuration */
#define HOME_AP_SSID        "wsn"
#define HOME_AP_PASSPHRASE  "brucenegley"
#define HOME_AP_SECURITY    RNWF_WPA2

uint32_t gOta_file_size = 0;

#define FLASH_READ_SIZE   16

uint8_t hex_ascii[0x10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

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
            printf("Enabling the OTA\r\n");
            RNWF_OTA_SrvCtrl(RNWF_OTA_ENABLE, NULL);
            break;
        default:
            break;                    
    }    
}



void APP_OTA_Callback(RNWF_OTA_EVENT_t event, uint8_t *p_str)
{
    
    switch(event)
    {
        case RNWF_EVENT_MAKE_UART:
            break;
        case RNWF_EVENT_DWLD_START:
            DBG_MSG_OTA("Total Size = %lu\r\n", *(uint32_t *)p_str); 
        
            break;
        case RNWF_EVENT_DWLD_DONE:
            gOta_file_size = *(uint32_t *)p_str;
            DBG_MSG_OTA("Download Success!= %lu bytes\r\n", gOta_file_size);                                                             
            break;
        default:
            break;
    }
    
}



void APP_SW_RESET_Handler(void)
{
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_RESET, NULL);
    
    DELAY_milliseconds(3500);
    
    RSTCTRL_reset();
    
}

int main(void)
{   
    volatile uint32_t addr = 0;
    uint8_t certs_keys[512];
    int Device_Id=0x00;
    int Device_Type=0x00;    
    int Manufacturer_Id=0x00;
    
    
    SYSTEM_Initialize();
    
    printf("%s", "########################################\n");
    printf("%s", "  Welcome RNWF02 WiFi Easy Config Demo  \n");
    printf("%s", "########################################\n");
        
    

    if(Read_ID(0x00) != SST25WF080B_ID)
    {
        printf("No SPI Flash found!\r\nConnect SPI MikroBus on slot1 and reset!\r\n");
        while(1);
    }
    
    Jedec_ID_Read(&Manufacturer_Id, &Device_Type, &Device_Id); 
    printf("SPI Manufacturer ID = 0x%02X\r\n", Manufacturer_Id);
    printf("SPI Device Type = 0x%02X\r\n", Device_Type);
    printf("SPI Device ID = 0x%02X\r\n", Device_Id);
    
    printf("Erasing the SPI Flash\r\n");
    WREN();
    Chip_Erase();
    Wait_Busy();
    printf("Erasing Complete!\r\n");            
        
    RNWF_IF_Init();  
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_CERT_LIST, certs_keys);    
    printf("%s\n", certs_keys);
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_KEY_LIST, certs_keys);    
    printf("%s\n", certs_keys);
        
    
                           
    PB2_SetInterruptHandler(APP_SW_RESET_Handler);

    /* Wi-Fii Connectivity */
    RNWF_WIFI_PARAM_t wifi_sta_cfg = {RNWF_WIFI_MODE_STA, HOME_AP_SSID, HOME_AP_PASSPHRASE, HOME_AP_SECURITY, 1};
    
    //printf("Connecting to %s\r\n", HOME_AP_SSID);
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);
    RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_sta_cfg);
    
    RNWF_OTA_SrvCtrl(RNWF_OTA_CONFIG, (void *)&ota_cfg);    
    RNWF_OTA_SrvCtrl(RNWF_OTA_SET_CALLBACK, (void *)APP_OTA_Callback);
    
    
    while(1)
    {              
           
        if(gOta_file_size > 0)                
        {                   
            uint8_t read_buffer[16];        
            // Read the flash and dump the contents                        
            HighSpeed_Read_Cont(addr, FLASH_READ_SIZE, read_buffer);              
            for(int i=0; i < 16; i++)
            {                                                        
                putchar(hex_ascii[(read_buffer[i] & 0xF0) >> 4]);
                putchar(hex_ascii[(read_buffer[i] & 0x0F)]);
                putchar(' ');                
            }
            putchar('\n');                
            addr += FLASH_READ_SIZE;
            gOta_file_size -= FLASH_READ_SIZE;
            
        }
        else
            RNWF_EVENT_Handler();
    }      
}