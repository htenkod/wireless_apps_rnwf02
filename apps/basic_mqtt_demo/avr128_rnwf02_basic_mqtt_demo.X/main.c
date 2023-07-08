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
#define HOME_AP_SSID        "HTN_Hotspot"
#define HOME_AP_PASSPHRASE  "tenkod123"
#define HOME_AP_SECURITY    RNWF_WPA2_MIXED


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

bool gMqtt_Publish = false;

#define APP_LED_SYS_INTERVAL    10    
#define APP_LED_WIFI_INTERVAL   30     
#define APP_LED_CLOUD_INTERVAL  100 

#define APP_MQTT_PUBLISH_INTERVAL   5

uint8_t info_buf[512];

//#define AWS_CLOUD     1
#define AZURE_CLOUD   1


#ifdef AWS_CLOUD


const char *tls_cfg_1[] = {"AmazonRootCA1", "aws", "aws", NULL, "*-ats.iot.us-west-2.amazonaws.com"};
//const char *tls_cfg_1[] = {"AmazonRootCA1", "aws_dev_01_cert", "aws_dev_01_key", NULL, NULL};
                       
RNWF_MQTT_CFG_t mqtt_cfg = {
    .url = "a3adakhi3icyv9-ats.iot.us-west-2.amazonaws.com", 
//    .url = "a1gqt8sttiign3-ats.iot.us-east-2.amazonaws.com", //MCU8
    .username = "",
    .password = "",
//    .clientid = "RNWF02_Test",//"rnwf02_dev_01",
    .clientid = "rnwf02_dev_01",
    .port = 8883,
    .tls_conf = tls_cfg_1,
    .tls_idx = RNWF_NET_TLS_CONFIG_1,     
};
#elif AZURE_CLOUD

#define AZURE_DEVICE_ID         "azure_dev_01"

#define AZURE_HUB_PUB_TOPIC     "devices/"AZURE_DEVICE_ID"/messages/events/"             

/**Azure IoT HUB subscribe list */
const char *azure_hub_sub[] = {"$iothub/twin/PATCH/properties/desired/#",  "$iothub/twin/res/#", "$iothub/methods/POST/#", NULL};
/**TLS Configuration for the DPS */
const char *tls_cfg_dps[] = {"BaltimoreCyberTrustRoot", "azure_dev_01_cert", "azure_dev_01_key", NULL, "*.azure-devices-provisioning.net"};
/**TLS Configuration for the IoT HUB */
const char *tls_cfg_hub[] = {"DigiCertGlobalRootG2", "azure_dev_01_cert", "azure_dev_01_key", NULL, "*.azure-devices.net"};
                       
RNWF_MQTT_CFG_t mqtt_cfg = {
    .url = "global.azure-devices-provisioning.net",        
    .username = "0ne009FA8C7/registrations/"AZURE_DEVICE_ID"/api-version=2019-03-31",    
    .clientid = AZURE_DEVICE_ID,    
    .password = "",
    .port = 8883,
    .tls_conf = tls_cfg_dps,
    .tls_idx = RNWF_NET_TLS_CONFIG_1,  
    .azure_dps = 1
};
#else
RNWF_MQTT_CFG_t mqtt_cfg = {
    .url = "test.mosquitto.org",        
    .clientid = "rnwf02",    
    .username = "",    
    .password = "",
    .port = 1883,    
    .tls_idx = 0,  
    .azure_dps = 0
};

#endif

void APP_SYS_Tick(void)
{          
    gSysTickCount++;     
}

void APP_LED_Tick(void)
{   
    uint32_t toggleFlag = 0;
    switch(gApp_State)               
    {
        case APP_WIFI_UP:
        {                
            toggleFlag = !(gSysTickCount % APP_LED_WIFI_INTERVAL);
        }
        break;            
        
        case APP_CLOUD_UP:
        { 
            //
            gMqtt_Publish = !(gSysTickCount % APP_LED_CLOUD_INTERVAL);            
            
        }
        break;
        
        default:             
            toggleFlag = !(gSysTickCount % APP_LED_SYS_INTERVAL);
            break;
    }
    
    if(toggleFlag)    
        LED_Toggle();    
    
}

RNWF_RESULT_t APP_MQTT_Publish(const char *msg)
{    
    RNWF_MQTT_FRAME_t mqtt_pub;    
    mqtt_pub.isNew = NEW_MSG;
    mqtt_pub.qos = MQTT_QOS0;
    mqtt_pub.isRetain = NO_RETAIN;
    mqtt_pub.topic = AZURE_HUB_PUB_TOPIC;
    mqtt_pub.message = msg;        
    return RNWF_MQTT_SrvCtrl(RNWF_MQTT_PUBLISH, (void *)&mqtt_pub);              
}        

RNWF_RESULT_t APP_MQTT_Callback(RNWF_MQTT_EVENT_t event, uint8_t *p_str)
{
    static uint8_t subCnt = 0;
    uint8_t tempBuf[256];    
    switch(event)
    {
        case RNWF_MQTT_CONNECTED:
        {                        
            gApp_State = APP_CLOUD_UP;  
            LED_SetLow();        
            if(azure_hub_sub[subCnt] != NULL)
            {
                sprintf(tempBuf, "%s", azure_hub_sub[subCnt++]);
                RNWF_MQTT_SrvCtrl(RNWF_MQTT_SUBSCRIBE_QOS0, tempBuf);            
            }                        
        }
        break;
        case RNWF_MQTT_SUBCRIBE_ACK:
        {
            if(azure_hub_sub[subCnt] != NULL)
            {
                sprintf(tempBuf, "%s", azure_hub_sub[subCnt++]);
                RNWF_MQTT_SrvCtrl(RNWF_MQTT_SUBSCRIBE_QOS0, tempBuf);            
            }
        }
        break;
        case RNWF_MQTT_SUBCRIBE_MSG:
        {
            printf("RNWF02 <- %s\r\n", p_str);
        }
        break;
        case RNWF_MQTT_DISCONNECTED:
        {
            printf("MQTT - Disconnected!\r\n");
            gApp_State = APP_CLOUD_DOWN;
            printf("MQTT - Reconnecting...\r\n");
            RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONNECT, NULL);            
        }
        break; 
        case RNWF_MQTT_DPS_STATUS:
        {                                       
            printf("DPS Status = %d\r\n", *p_str);
            if(*p_str == 1)
            {
                RNWF_NET_SOCK_SrvCtrl(mqtt_cfg.tls_idx, (void *)tls_cfg_hub);  
                RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_MQTT_INFO, info_buf);
                printf("%s\n", info_buf);        
            }
            else
            {   
                RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONFIG, (void *)&mqtt_cfg);                                                           
            }
            RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONNECT, NULL);                
        }
        break;
        
        default:
        break;
    }
    return RNWF_PASS;
}


void APP_WIFI_Callback(RNWF_WIFI_EVENT_t event, uint8_t *p_str)
{       
    switch(event)
    {
        case RNWF_SNTP_UP:
        {
            printf("SNTP UP:%s\n", &p_str[2]);  
            if(gApp_State < APP_CLOUD_DOWN)
            {                
                gApp_State = APP_CLOUD_DOWN;
                RNWF_MQTT_SrvCtrl(RNWF_MQTT_SET_CALLBACK, APP_MQTT_Callback);
                RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONFIG, (void *)&mqtt_cfg);
                RNWF_MQTT_SrvCtrl(RNWF_MQTT_CONNECT, NULL);
            }
        }
        break;
        case RNWF_CONNECTED:
        {
            printf("Wi-Fi Connected\n");  
            
        }    
        break;
        case RNWF_DISCONNECTED:
            printf("Wi-Fi Disconnected\nReconnecting... \n");
            RNWF_WIFI_SrvCtrl(RNWF_STA_CONNECT, NULL);
            break;
        case RNWF_DHCP_DONE:
        {
            printf("DHCP IP:%s\n", &p_str[2]);                   
            gApp_State = APP_WIFI_UP;              
        }
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
    uint32_t pub_cnt = 0;
    uint8_t idx = 0;
    
    SYSTEM_Initialize();

    PB2_SetInterruptHandler(APP_SW_RESET_Handler);
    TCA0_Compare0CallbackRegister(APP_LED_Tick);
    TCA0_OverflowCallbackRegister(APP_SYS_Tick);    
        
    printf("%s", "##################################\n");
    printf("%s", "  Welcome RNWF02 Basic Cloud Demo  \n");
    printf("%s", "##################################\n");

    RNWF_IF_Init(); 
                                            
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_CERT_LIST, info_buf);    
    printf("%s\n", info_buf);
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_GET_KEY_LIST, info_buf);    
    printf("%s\n", info_buf);
    
    RNWF_SYSTEM_SrvCtrl(RWWF_SYSTEM_GET_WIFI_INFO, info_buf);    
    printf("%s\n", info_buf);
    
//    uint32_t current_time =  1685224592;    
//    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SET_TIME_UNIX, &current_time);
    
    const char sntp_url[] =  "0.in.pool.ntp.org";    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SET_SNTP, sntp_url);             
            
//    uint32_t unix_tick =  1687368738;    
//    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SET_TIME_UNIX, &unix_tick);             
    
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SW_REV, info_buf);    
    printf("%s\n", info_buf);
    
    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_DEV_INFO, info_buf);    
    printf("%s\n", info_buf);  
    
//    const char sntp_url[] =  "0.pool.ntp.org";    
//    RNWF_SYSTEM_SrvCtrl(RNWF_SYSTEM_SET_SNTP, sntp_url); 
                
    /* RNWF Application Callback register */
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_SET_CALLBACK, APP_WIFI_Callback);
    RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_SET_CALLBACK, APP_SOCKET_Callback);    
        
        
    /* Wi-Fii Connectivity */
    RNWF_WIFI_PARAM_t wifi_sta_cfg = {RNWF_WIFI_MODE_STA, HOME_AP_SSID, HOME_AP_PASSPHRASE, HOME_AP_SECURITY, 1};    
    RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_sta_cfg);
        
    

    while(1)
    {       
                                                                         
        uint8_t pub_buf[64];                
        if(gMqtt_Publish)
        {                                                   
            pub_cnt++;
            gMqtt_Publish = 0;                    
            sprintf(pub_buf, "{\\\"WFI32IoT_temperature\\\": \\\"%d\\\"}", pub_cnt);
            APP_MQTT_Publish(pub_buf);                                        
        }           
                                    
        RNWF_EVENT_Handler();
    }    
}
