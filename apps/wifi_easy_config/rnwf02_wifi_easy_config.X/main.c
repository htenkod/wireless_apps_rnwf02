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

#include "mcc_generated_files/reset/rstctrl.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_system_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_provision_service.h"

/*
    Main application
*/

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

void APP_SW_RESET_Handler(void)
{
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_RESET, NULL);
    
    DELAY_milliseconds(3500);
    
    RSTCTRL_reset();
    
}

int main(void)
{   
    uint8_t certList[512];
    SYSTEM_Initialize();
    
    printf("%s", "########################################\n");
    printf("%s", "  Welcome RNWF02 WiFi Easy Config Demo  \n");
    printf("%s", "########################################\n");

    RNWF_IF_Init();  
    

    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_CERT_LIST, certList);
    printf("%s\n", certList);
               
    PB2_SetInterruptHandler(APP_SW_RESET_Handler);

    // Enable Provisioning Mode
    RNWF_PROV_SrvCtrl(RNWF_PROV_ENABLE, NULL);
    RNWF_PROV_SrvCtrl(RNWF_PROV_SET_CALLBACK, (void *)APP_PROV_Callback);
        
    while(1)
    {                
        RNWF_EVENT_Handler();
    }      
}