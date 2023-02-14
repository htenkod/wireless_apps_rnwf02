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
© [2023] Microchip Technology Inc. and its subsidiaries.

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
#include <string.h>

#include "mcc_generated_files/system/system.h"

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
#define HOME_AP_SECURITY    RNWF_WPA2


/* TCP Socket */
RNWF_NET_SOCKET_t tcp_client_socket = {
        .bind_type = RNWF_BIND_REMOTE,
        .sock_port = 443,
        .sock_type = RNWF_SOCK_TCP,
        .sock_addr = "52.218.137.201",
        .tls_conf  = 1,
        };


uint8_t aws_file_request[] = "GET /ref_doc.pdf HTTP/1.1\r\nHost: file-download-files.s3-us-west-2.amazonaws.com\r\nConnection: close\r\n\r\n";

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
        {            
            const char *tls_cfg_1[] = {"AmazonRootCA1", NULL, NULL, NULL, "s3-us-west-2.amazonaws.com"};
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_TLS_CONFIG_1, tls_cfg_1);             
            tcp_client_socket.tls_conf = RNWF_NET_TLS_CONFIG_1;                        
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_TCP_OPEN, &tcp_client_socket);
            printf("DHCP IP:%s\n", &p_str[2]); 
            
            break;
        }
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
            printf("Connected to server!\n");            
            break;
        case RNWF_NET_SOCK_EVENT_TLS_DONE:
            RNWF_NET_SOCK_Write(socket, strlen((char *)aws_file_request), aws_file_request, RNWF_BINARY_MODE);                            
            break;
        case RNWF_NET_SOCK_EVENT_DISCONNECTED:
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_CLOSE, &socket);
            break;
        case RNWF_NET_SOCK_EVENT_READ:
        {         
            uint8_t rx_data[512] = {0, };
            uint16_t rx_len = *(uint16_t *)p_str;                             
            if((rx_len < 512) && (RNWF_NET_SOCK_Read(socket, rx_len, rx_data, RNWF_BINARY_MODE) == RNWF_PASS))
            {                              
                printf("%.*s", rx_len, rx_data);
            }            
            else
            {
                printf("Too big file!");
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
    uint8_t cert_list[256];
    
    SYSTEM_Initialize();

    printf("%s", "##################################\n");
    printf("%s", "  Welcome RNWF02 TLS Client Demo  \n");
    printf("%s", "##################################\n");

    RNWF_IF_Init();    
    
    RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_MAN_ID, man_id);    
    printf("Manufacturer = %s\n", man_id);
    
    RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_FS_CERT_LIST, cert_list);  
    printf("Cert List:- \n%s", cert_list);
    
    uint32_t current_time = 1669999131;
    
    RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_SET_SYS_TIME_UNIX, &current_time);
    
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