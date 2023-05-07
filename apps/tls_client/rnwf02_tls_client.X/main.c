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
� [2023] Microchip Technology Inc. and its subsidiaries.

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
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "mcc_generated_files/reset/rstctrl.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"

#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_system_service.h"



/*
    Main application
*/

/* Wi-Fi Configuration */
#define HOME_AP_SSID        "wsn"
#define HOME_AP_PASSPHRASE  "brucenegley"
#define HOME_AP_SECURITY    RNWF_WPA2

#define TCP_BUF_LEN_MAX     4096 + 2048
#define HTTP_CONTENT_LEN    "Content-Length:"

uint8_t tcp_data[TCP_BUF_LEN_MAX];
uint32_t gFile_Len = 0;

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
    uint8_t *tmpPtr;
    static uint32_t rcvd_bytes;
    switch(event)
    {
        case RNWF_NET_SOCK_EVENT_CONNECTED:            
            printf("Connected to server!\n");            
            break;
        case RNWF_NET_SOCK_EVENT_TLS_DONE:
            RNWF_NET_TCP_SOCK_Write(socket, strlen((char *)aws_file_request), aws_file_request);                            
            break;
        case RNWF_NET_SOCK_EVENT_DISCONNECTED:
            printf("Socket Closed!\n"); 
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_CLOSE, &socket);
            break;
        case RNWF_NET_SOCK_EVENT_READ:
        {                     
            int ret_val;
            uint16_t rx_len = *(uint16_t *)p_str;              
            while(rx_len)
            {
                uint16_t read_len = (rx_len > TCP_BUF_LEN_MAX)?TCP_BUF_LEN_MAX:rx_len;                
                if(((ret_val = RNWF_NET_TCP_SOCK_Read(socket, read_len, tcp_data)) > 0))
                {                              
                    if(!gFile_Len)
                    {
                        printf("%.*s\r\n", ret_val, tcp_data);
                        if((tmpPtr = (uint8_t *)strstr(tcp_data, HTTP_CONTENT_LEN)) != NULL)
                        {
                            volatile char *token = strtok(tmpPtr, "\r\n");
                            gFile_Len = strtol((token+sizeof(HTTP_CONTENT_LEN)), NULL, 10);                                                        
                            printf("File Size = %lu\r\n", gFile_Len);
                        }                                                
                        break;
                    }
                    rcvd_bytes += ret_val;
                    rx_len -= ret_val;
                    printf("Received %lu bytes\r\n", rcvd_bytes);
                    if(rcvd_bytes >= gFile_Len)
                    {
                        printf("Receive Complete!\r\n");  
                        RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_CLOSE, NULL);
                    }                    
                }            
                else
                {
                    printf("Read Timeout!\r\n");
                    break;
                }
            }
            break; 
        }
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
    uint8_t man_id[32];
    uint8_t cert_list[256];
    
    SYSTEM_Initialize();

    printf("%s", "##################################\n");
    printf("%s", "  Welcome RNWF02 TLS Client Demo  \n");
    printf("%s", "##################################\n");

    RNWF_IF_Init();    
    
    PB2_SetInterruptHandler(APP_SW_RESET_Handler);
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_MAN_ID, man_id);    
    printf("Manufacturer = %s\n", man_id);
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_CERT_LIST, cert_list);  
    printf("Cert List:- \n%s\r\n", cert_list);
    
    uint32_t current_time = 1683402763;
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SET_TIME_UNIX, &current_time);
    
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