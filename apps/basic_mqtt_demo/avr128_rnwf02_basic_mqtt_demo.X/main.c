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
#include <stdlib.h>
#include <stdarg.h>

#include "mcc_generated_files/reset/rstctrl.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"

#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_mqtt_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_system_service.h"



/*
    Main application
*/

/* Wi-Fi Configuration */
#define HOME_AP_SSID        "wsn"
#define HOME_AP_PASSPHRASE  "brucenegley"
#define HOME_AP_SECURITY    RNWF_WPA2


#define MQTT_PUBLISH_TOPIC      "mchp/rnwf02/from"
#define MQTT_SUBSCRIBE_TOPIC    "mchp/rnwf02/to/#"


typedef enum {
    APP_SYS_INIT,
    APP_SYS_UP,
    APP_WIFI_INIT,
    APP_WIFI_DOWN,
    APP_WIFI_UP,
    APP_CLOUD_DOWN,
    APP_CLOUD_UP
}APP_STATE_t;


APP_STATE_t gApp_State = APP_SYS_INIT;

uint32_t gSysTickCount;

#define MQTT_PUBLISH_INTERVAL   10 //100msec units





#define AWS_CLOUD   1


#ifdef AWS_CLOUD

const char *tls_cfg_1[] = {"AmazonRootCA1", "aws_rnwf_01_cert", "aws_rnwf_01_key", NULL, "iot.us-west-2.amazonaws.com"};
                       
RNWF_MQTT_CFG_t mqtt_cfg = {
    .url = "a3adakhi3icyv9-ats.iot.us-west-2.amazonaws.com",
    .username = "",
    .clientid = "RNWF02_Test",
    .port = 8883,
    .tls_conf = tls_cfg_1,
    .tls_idx = RNWF_NET_TLS_CONFIG_1,     
};
#else
const char *tls_cfg_1[] = {"BaltimoreCyberTrustRoot", "azure_rnwf_01_cert", "azure_rnwf_01_key", NULL, "global.azure-devices-provisioning.net"};
                       
RNWF_MQTT_CFG_t mqtt_cfg = {
    .url = "global.azure-devices-provisioning.net",        
    .username = "0ne009FA8C7/registrations/azure_rnwf_01/api-version=2019-03-31",
    .clientid = "azure_rnwf_01",
    .port = 8883,
    .tls_conf = tls_cfg_1,
    .tls_idx = RNWF_NET_TLS_CONFIG_1,     
};
#endif

void APP_TIMER_Callback(void)
{
    // callback here    
    gSysTickCount++;        
}

RNWF_RESULT_t APP_MQTT_Publish(const char *msg)
{    
    RNWF_MQTT_FRAME_t mqtt_pub;    
    mqtt_pub.isNew = NEW_MSG;
    mqtt_pub.qos = MQTT_QOS0;
    mqtt_pub.isRetain = NO_RETAIN;
    mqtt_pub.topic = MQTT_PUBLISH_TOPIC;
    mqtt_pub.message = msg;        
    return RNWF_MQTT_SrvCtrl(RNWF_MQTT_PUBLISH, (void *)&mqtt_pub);              
}        

void APP_MQTT_Callback(RNWF_MQTT_EVENT_t event, uint8_t *p_str)
{
    switch(event)
    {
        case RNWF_MQTT_CONNECTED:
        {
            const char sub_topic[] = MQTT_SUBSCRIBE_TOPIC;
            gApp_State = APP_CLOUD_UP;
            LED_SetLow();
            APP_MQTT_Publish("RNWF02 -> I am Up!");
            RNWF_MQTT_SrvCtrl(RNWF_MQTT_SUBSCRIBE_QOS0, (void *)sub_topic);             
        }
        break;
        case RNWF_MQTT_SUBCRIBE_MSG:
        {
            printf("RNWF02 <- %s\r\n", p_str);
        }
        break;
        case RNWF_MQTT_DISCONNECTED:
        {
            TCA0_Stop();
        }
        break;    
        default:
        break;
    }
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
            gApp_State = APP_WIFI_UP;
            RNWF_MQTT_SrvCtrl(RNWF_MQTT_SET_CALLBACK, APP_MQTT_Callback);
            RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONFIG, (void *)&mqtt_cfg);
            RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONNECT, APP_MQTT_Callback);
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
            break;
        default:
            break;
    }
}

void APP_SW_RESET_Handler(void)
{
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_RESET, NULL);
    DELAY_milliseconds(5000);
    RSTCTRL_reset();
}


int main(void)
{
    uint8_t certs_keys[512];
    uint32_t pub_cnt = 0;
    
    SYSTEM_Initialize();

    printf("%s", "##################################\n");
    printf("%s", "  Welcome RNWF02 Basic Cloud Demo  \n");
    printf("%s", "##################################\n");

    RNWF_IF_Init(); 
    
    TCA0_OverflowCallbackRegister(APP_TIMER_Callback);    
            
    PB2_SetInterruptHandler(APP_SW_RESET_Handler);
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_CERT_LIST, certs_keys);    
    printf("%s\n", certs_keys);
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_KEY_LIST, certs_keys);    
    printf("%s\n", certs_keys);
    
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
        
        switch(gApp_State)               
        {                        
            case APP_CLOUD_UP:
            {                
                uint8_t pub_buf[64];                
                if((gSysTickCount % MQTT_PUBLISH_INTERVAL) == 0)
                {                                                   
                    pub_cnt++;
                    sprintf(pub_buf, "RNWF -> Msg #%d", pub_cnt);
                    APP_MQTT_Publish(pub_buf);                    
                }
            }            
            break;            
            default:
                LED_Toggle() ;
                break;                
        }
        
        RNWF_EVENT_Handler();
    }    
}
