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
#include <stdio.h>
#include <stdarg.h>

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"

#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_utility_service.h"



/*
    Main application
*/

/* Wi-Fi Configuration */
#define HOME_AP_SSID        "wsn"
#define HOME_AP_PASSPHRASE  "brucenegley"
#define HOME_AP_SECURITY    RNWF_WPA2_MIXED


/* TCP Socket */
RNWF_NET_SOCKET_t tcp_server_socket = {
        .bind_type = RNWF_BIND_LOCAL,
        .sock_port = 6666,
        .sock_type = RNWF_SOCK_TCP,
        };


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
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_TCP_OPEN, &tcp_server_socket);
            break;
        case RNWF_SCAN_INDICATION:
            break;
        case RNWF_SCAN_DONE:
            break;
        default:
            break;
                    
    }    
}

void APP_SOCKET_Callback(uint32_t socket, RNWF_NET_SOCK_EVENT_t event, uint8_t *p_str)
{
      
    switch(event)
    {
        case RNWF_NET_SOCK_EVENT_CONNECTED:            
            break;
        case RNWF_NET_SOCK_EVENT_DISCONNECTED:
            break;
        case RNWF_NET_SOCK_EVENT_READ:
        {
            uint8_t rx_data[64];
            uint16_t rx_len = *(uint16_t *)p_str;         
            if(RNWF_NET_SOCK_Read(socket, rx_len, rx_data, RNWF_BINARY_MODE) == RNWF_PASS)
            {                
                RNWF_NET_SOCK_Write(socket, rx_len, rx_data, RNWF_BINARY_MODE);                
            }
            break; 
        }
        default:
            break;
                    
    }    
    
}

int main(void)
{
    uint8_t man_id[32];
    
    SYSTEM_Initialize();

    printf("%s", "##################################\n");
    printf("%s", "  Welcome RNWF02 TCP Server Demo  \n");
    printf("%s", "##################################\n");

    RNWF_IF_Init();    
    
    RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_MAN_ID, man_id);    
    
    
    
    /* RNWF Application Callback register */
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);
    RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_SET_CALLBACK, APP_SOCKET_Callback);
        
    /* Wi-Fii Connectivity */
    RNWF_WIFI_PARAM_t wifi_sta_cfg = {RNWF_WIFI_MODE_STA, HOME_AP_SSID, HOME_AP_PASSPHRASE, HOME_AP_SECURITY, 1};
    
    RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_sta_cfg);
        
    

    while(1)
    {                
        RNWF_EVENT_Handler();
    }    
}