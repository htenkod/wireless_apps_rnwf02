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
#ifndef HTTP_H
#define	HTTP_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define HTTP_HDR_OFFSET     128

#define HTTP_BUFFER_LEN     1400

//#define HTTP_RESPONSE_HDR   "HTTP/1.1 200 OK\nServer: RNWF/1.0\nContent-Type: text/html\nContent-Length: %d\nConnection: keep-alive\n\n"

#define HTTP_RESPONSE_NOT_FOUND "HTTP/1.1 404 OK\nConnection: Close\n\n"

#define HTTP_RESPONSE_HDR   "HTTP/1.1 200 OK\nServer: RNWF-02/1.0\nContent-Type: %s\nContent-Length: %d\nConnection: Keep-Alive\n\n"

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

typedef void (*WEB_REQUEST_HANDLER_t)(uint32_t socket, uint8_t *input);


typedef struct {    
    WEB_REQUEST_HANDLER_t   handler;     
    const char              *url;
}WEB_PAGES_t;


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

extern uint8_t http_buffer[HTTP_BUFFER_LEN];    
    
void HTTP_REQ_Parser(uint32_t socket, uint16_t rx_len);
uint16_t HTTP_RESP_Send(uint32_t socket, const char * resp_hdr, const char *webpage, const char *page_type, uint16_t page_len);

void HTTP_CB_Index(uint32_t socket, uint8_t *input);
void HTTP_CB_Logo(uint32_t socket, uint8_t *input);
void HTTP_CB_Icon(uint32_t socket, uint8_t *input);
void HTTP_CB_Scan(uint32_t socket, uint8_t *input);
void HTTP_CB_Provision(uint32_t socket, uint8_t *input);
    
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* HTTP_H */

