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

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_system_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_ota_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_provision_service.h"

/*
    Main application
*/

#define OTA_SERVER              "192.168.0.108"
#define OTA_PORT                4444


RNWF_OTA_CFG_t ota_cfg = {
    .mode = RNWF_OTA_MODE_HTTP,
    .url = OTA_SERVER,       
    .port = OTA_PORT, 
    .socket.tls_conf = 0,
};

/* Wi-Fi Configuration */
#define HOME_AP_SSID        "HTN"
#define HOME_AP_PASSPHRASE  "12345678"
#define HOME_AP_SECURITY    RNWF_OPEN



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
        default:
            break;
    }
    
}


void APP_PROV_Callback(RNWF_PROV_EVENT_t event, uint8_t *p_str)
{
    switch(event)
    {
        case RNWF_PROV_COMPLTE:
            RNWF_PROV_SrvCtrl(RNWF_PROV_DISABLE, NULL);
            
            RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);
            // Application can save the configuration in NVM
            RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, (void *)p_str);
            
            
            
            break;
        case RNWF_PROV_FAILURE:
            break;
        default:
            break;        
    }
    
}


int main(void)
{   
    
    SYSTEM_Initialize();
    
    printf("%s", "########################################\n");
    printf("%s", "  Welcome RNWF02 WiFi Easy Config Demo  \n");
    printf("%s", "########################################\n");

    RNWF_IF_Init();      
               

#if 1    
    // Enable Provisioning Mode
    RNWF_PROV_SrvCtrl(RNWF_PROV_ENABLE, NULL);
    RNWF_PROV_SrvCtrl(RNWF_PROV_SET_CALLBACK, (void *)APP_PROV_Callback);
    
    
#else    
    /* Wi-Fii Connectivity */
    RNWF_WIFI_PARAM_t wifi_sta_cfg = {RNWF_WIFI_MODE_STA, HOME_AP_SSID, HOME_AP_PASSPHRASE, HOME_AP_SECURITY, 1};
    
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);
    RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_sta_cfg);
    
    RNWF_OTA_SrvCtrl(RNWF_OTA_CONFIG, (void *)&ota_cfg);    
    RNWF_OTA_SrvCtrl(RNWF_OTA_SET_CALLBACK, (void *)APP_OTA_Callback);
    
#endif    
    
    while(1)
    {                
        RNWF_EVENT_Handler();
    }      
}