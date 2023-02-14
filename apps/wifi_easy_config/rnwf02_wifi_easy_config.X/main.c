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
#include "mcc_generated_files/library/rnwf02/rnwf_utility_service.h"

#include "http.h"
/*
    Main application
*/
extern uint32_t g_scan_socket;

/* Wi-Fi Configuration */
#define SOFT_AP_SSID        "RNWF02-AP"
#define SOFT_AP_PASSPHRASE  "12345678"
#define SOFT_AP_SECURITY    RNWF_OPEN//RNWF_WPA2_MIXED


/* TCP Socket */
RNWF_NET_SOCKET_t web_server_socket = {
        .bind_type = RNWF_BIND_LOCAL,
        .sock_port = 80,
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
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_TCP_OPEN, &web_server_socket);
            
            break;
        case RNWF_SCAN_INDICATION:
        {
            uint16_t resp_len = strlen((char *)p_str);
            uint16_t buff_len = strlen((char *)&http_buffer[HTTP_HDR_OFFSET])+HTTP_HDR_OFFSET;
            // reuse the http buffer with a offset to hold header info 
            // sanity check for buffer over flow            
            if((buff_len + resp_len + 2) < HTTP_BUFFER_LEN)
            {
                strcat((char *)&http_buffer[HTTP_HDR_OFFSET], (char *)p_str);                
                buff_len += resp_len;                
                http_buffer[buff_len] = '|';
                http_buffer[buff_len+1] = '\0';            
            }
            break;
        }
        case RNWF_SCAN_DONE:
            if(g_scan_socket)
                HTTP_RESP_Send(g_scan_socket, HTTP_RESPONSE_HDR, (char *)&http_buffer[HTTP_HDR_OFFSET], "text/html", strlen((char *)&http_buffer[HTTP_HDR_OFFSET]));                
                
            
            break;
        default:
            break;
                    
    }    
}

void APP_SOCKET_Callback(uint32_t sock, RNWF_NET_SOCK_EVENT_t event, uint8_t *p_str)
{    
    switch(event)
    {
        case RNWF_NET_SOCK_EVENT_CONNECTED:  
        {
            //RNWF_NET_SOCKET_CONFIG_t sock_cfg = {.sock_id = sock, .sock_keepalive = 0, .sock_nodelay = 1};
            //RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_CONFIG, &sock_cfg);
            break;
        }
        case RNWF_NET_SOCK_EVENT_DISCONNECTED:
        {
            RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_CLOSE, &sock);
            break;
        }
        case RNWF_NET_SOCK_EVENT_READ:
        {                        
            HTTP_REQ_Parser(sock, *(uint16_t *)p_str);
        }
        default:
            break;
                    
    }    
    
}

int main(void)
{   
    uint8_t cert_list[256];
    
    SYSTEM_Initialize();
    
    printf("%s", "########################################\n");
    printf("%s", "  Welcome RNWF02 WiFi Easy Config Demo  \n");
    printf("%s", "########################################\n");

    RNWF_IF_Init();      
    
    //RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_MAN_ID, man_id);    
    
    RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_FS_CERT_LIST, cert_list);  
    printf("Cert List:- \n%s", cert_list);
    
    /* RNWF Application Callback register */
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);
    RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_SET_CALLBACK, APP_SOCKET_Callback);
            
    const char *dhcps_cfg[] = {"192.168.1.1/24", "192.168.1.10", "192.168.1.0"};        
    RNWF_NET_SOCK_SrvCtrl(RNWF_NET_DHCP_SERVER_ENABLE, dhcps_cfg);    

    /* Wi-Fii Connectivity */
    RNWF_WIFI_PARAM_t wifi_ap_cfg = {RNWF_WIFI_MODE_AP, SOFT_AP_SSID, "", SOFT_AP_SECURITY, 1};    
    RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_ap_cfg);
    
    //RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_TCP_OPEN, &web_server_socket);

    while(1)
    {                
        RNWF_EVENT_Handler();
    }      
}