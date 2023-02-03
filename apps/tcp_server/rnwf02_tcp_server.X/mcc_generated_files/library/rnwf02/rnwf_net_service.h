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
#ifndef RNWF_NET_SERVICE_H
#define	RNWF_NET_SERVICE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>


#define RNWF_SOCK_ID_LEN_MAX            8
#define RNWF_SOCK_ADDR_LEN_MAX          32

#define RNWF_SOCK_TLS_CFG_LEN_MAX       64

#define RNWF_DHCPS_ENABLE       "AT+DHCPSC=1,1\r\n"
#define RNWF_DHCPS_DISABLE      "AT+DHCPSC=1,0\r\n"
#define RNWF_DHCPS_SET_POOL     "AT+DHCPSC=2,\"%s\"\r\n"
#define RNWF_DHCPS_SET_GW       "AT+DHCPSC=3,\"%s\"\r\n"

#define RNWF_NETIF_SET_IP       "AT+NETIFC=0,40,\"%s\"\r\n"

#define RNWF_SOCK_GET_LIST      "AT+SOCKLST\r\n"

#define RNWF_SOCK_OPEN_UDP      "AT+SOCKO=1,4\r\n"
#define RNWF_SOCK_OPEN_TCP      "AT+SOCKO=2,4\r\n"
#define RNWF_SOCK_OPEN_RESP     "+SOCKO:"

#define RNWF_SOCK_BIND_LOCAL    "AT+SOCKBL=%s,%d\r\n"
#define RNWF_SOCK_BIND_REMOTE   "AT+SOCKBR=%s,%s,%d\r\n"
#define RNWF_SOCK_BIND_MCAST    "AT+SOCKBM=%s,%s,%d\r\n"


#define RNWF_SOCK_BINARY_WRITE_TCP     "AT+SOCKWR=%lu,%u\r\n"
#define RNWF_SOCK_BINARY_WRITE_UDP     "AT+SOCKWRTO=%lu,%s,%d,%d\r\n"

#define RNWF_SOCK_ASCII_WRITE_TCP     "AT+SOCKWR=%d,%d,\"%.*s\"\r\n"
#define RNWF_SOCK_ASCII_WRITE_UDP     "AT+SOCKWRTO=%d,%s,%d,%d,\"%.*s\"\r\n"

#define RNWF_SOCK_READ          "AT+SOCKRD=%lu,%d,%d\r\n"
#define RNWF_SOCK_READ_RESP     "+SOCKRD:"

#define RNWF_SOCK_CLOSE         "AT+SOCKCL=%lu\r\n"

#define RNWF_SOCK_CONFIG_TLS        "AT+SOCKTLS=%s,%d\r\n"
#define RNWF_SOCK_CONFIG_KEEPALIVE  "AT+SOCKC=%lu,1,%d\r\n"
#define RNWF_SOCK_CONFIG_NODELAY    "AT+SOCKC=%lu,2,%d\r\n"


#define RNWF_SOCK_TLS_GET_CONFIG        "AT_TLSC\r\n"
#define RNWF_SOCK_TLS_SET_CA_NAME       "AT_TLSC=1,%s\r\n"
#define RNWF_SOCK_TLS_SET_CERT_NAME     "AT_TLSC=2,%s\r\n"
#define RNWF_SOCK_TLS_SET_KEY_NAME      "AT_TLSC=3,%s\r\n"
#define RNWF_SOCK_TLS_SET_KEY_PWD       "AT_TLSC=4,%s\r\n"
#define RNWF_SOCK_TLS_SERVER_NAME       "AT_TLSC=5,%s\r\n"


// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations


typedef enum {
    RNWF_NET_IF_CONFIG,
    RNWF_NET_DHCP_SERVER_ENABLE,
    RNWF_NET_DHCP_SERVER_DISABLE,
    RNWF_NET_SOCK_TCP_OPEN,
    RNWF_NET_SOCK_UDP_OPEN,
    RNWF_NET_SOCK_CLOSE,    
    RNWF_NET_SOCK_CONFIG,
    RNWF_NET_TLS_CONFIG,
    RNWF_NET_SOCK_SET_CALLBACK,                
}RNWF_NET_SOCK_SERVICE_t;

typedef enum    {    
    RNWF_SOCK_UDP = 1,
    RNWF_SOCK_TCP,    
}RNWF_SOCK_TYPE_t;


typedef enum    {    
    RNWF_BIND_LOCAL,
    RNWF_BIND_REMOTE,
    RNWF_BIND_MCAST,
    RNWF_BIND_NONE,
}RNWF_BIND_TYPE_t;

typedef enum    {    
    RNWF_ASCII_MODE = 1,
    RNWF_BINARY_MODE,    
}RNWF_SOCK_RW_MODE_t;


typedef enum {
    RNWF_NET_SOCK_EVENT_CONNECTED,
    RNWF_NET_SOCK_EVENT_DISCONNECTED,
    RNWF_NET_SOCK_EVENT_READ, 
            
}RNWF_NET_SOCK_EVENT_t;


typedef enum {
    RNWF_NET_TLS_CA_CERT = 0,
    RNWF_NET_TLS_CERT_NAME,            
    RNWF_NET_TLS_KEY_NAME,
    RNWF_NET_TLS_KEY_PWD,
    RNWF_NET_TLS_SERVER_NAME,
}RNWF_NET_TLS_CONFIG_ID_t;

typedef struct {
    uint8_t             proto_type;
    RNWF_BIND_TYPE_t    bind_type;
    RNWF_SOCK_TYPE_t    sock_type;
    uint16_t            sock_port;
    uint8_t             sock_addr[RNWF_SOCK_ADDR_LEN_MAX];
    uint8_t             sock_master[RNWF_SOCK_ID_LEN_MAX];
    uint8_t             sock_client[RNWF_SOCK_ID_LEN_MAX];
}RNWF_NET_SOCKET_t;


typedef struct {  
    uint32_t    sock_id;
    uint8_t     sock_keepalive;
    uint8_t     sock_nodelay;    
}RNWF_NET_SOCKET_CONFIG_t;


typedef void (*RNWF_NET_SOCK_CALLBACK_t)(uint32_t sock, RNWF_NET_SOCK_EVENT_t, uint8_t *);
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
extern RNWF_NET_SOCK_CALLBACK_t gSocket_CallBack_Handler;

RNWF_RESULT_t RNWF_NET_SOCK_SrvCtrl( RNWF_NET_SOCK_SERVICE_t request, void *input);

RNWF_RESULT_t RNWF_NET_SOCK_Write( uint32_t socket, uint16_t length, uint8_t *input, RNWF_SOCK_RW_MODE_t wr_mode);

RNWF_RESULT_t RNWF_NET_SOCK_Read( uint32_t socket, uint16_t length, uint8_t *input, RNWF_SOCK_RW_MODE_t read_mode);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* RNWF_NET_SERVICE_H */

