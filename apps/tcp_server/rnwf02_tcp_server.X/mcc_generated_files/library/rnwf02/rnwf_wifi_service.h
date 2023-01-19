/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RNWF_WIFI_SERVICE_H
#define	RNWF_WIFI_SERVICE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define RNWF_WIFI_GET_STATE     "AT+WSTA\r\n"
#define RNWF_WIFI_CONNECT       "AT+WSTA=1\r\n"
#define RNWF_WIFI_DISCONNECT    "AT+WSTA=0\r\n"
#define RNWF_WIFI_SET_SSID      "AT+WSTAC=1,\"%s\"\r\n"
#define RNWF_WIFI_SET_SEC       "AT+WSTAC=2,%d\r\n"
#define RNWF_WIFI_SET_PWD       "AT+WSTAC=3,\"%s\"\r\n"
#define RNWF_WIFI_PSV_SCAN      "AT+WSCN=0\r\n"
#define RNWF_WIFI_ACT_SCAN      "AT+WSCN=1\r\n"



#define RNWF_SSID_LEN_MAX       33

#define RNWF_PWD_LEN_MAX        128

typedef enum {
    RNWF_STA_CONNECT,
    RNWF_STA_DISCONNECT,
    RNWF_STA_SET_PARAMS,
    RNWF_WIFI_PASSIVE_SCAN,
    RNWF_WIFI_ACTIVE_SCAN,                            
    RNWF_WIFI_SET_CALLBACK,    
}RNWF_WIFI_SERVICE_t;


typedef enum {
    RNWF_CONNECTED,
    RNWF_DISCONNECTED,
    RNWF_CONNECT_FAILED,
    RNWF_DHCP_DONE,        
    RNWF_SCAN_INDICATION,
    RNWF_SCAN_DONE,    
}RNWF_WIFI_EVENT_t;


typedef enum {
    RNWF_OPEN,
    RNWF_RSVD,
    RNWF_WPA2_MIXED,
    RNWF_WPA2,
    RNWF_WPA3_TRANS,
    RNWF_WPA3,        
    RNWF_WPA2_802_1X_MIXED,
    RNWF_WPA2_802_1X,
    RNWF_WPA3_802_1X_TRANS,
    RNWF_WPA3_802_1X,                
}RNWF_WIFI_SEC_t;


typedef struct {
    uint8_t ssid[RNWF_SSID_LEN_MAX];
    uint8_t passphrase[RNWF_PWD_LEN_MAX];
    RNWF_WIFI_SEC_t security;
    uint8_t channel;
    uint32_t timeout;
}RNWF_WIFI_STA_PARAM_t;


typedef void (*RNWF_WIFI_CALLBACK_t)(RNWF_WIFI_EVENT_t, uint8_t *);

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation
extern RNWF_WIFI_CALLBACK_t gWifi_CallBack_Handler;

RNWF_RESULT_t RNWF_WIFI_SrvCtrl( RNWF_WIFI_SERVICE_t request, void *input);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* RNWF_WIFI_SERVICE_H */

