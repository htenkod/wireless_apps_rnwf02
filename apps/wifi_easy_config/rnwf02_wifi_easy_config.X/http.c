/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    http.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdio.h>
#include <string.h>

#include "mcc_generated_files/timer/delay.h"

#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"

#include "http.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */


uint8_t http_buffer[HTTP_BUFFER_LEN];

uint32_t g_scan_socket = 0;

extern const char main_htm[];
extern unsigned int main_htm_len;
extern const char mchp_gif[];
extern unsigned int mchp_gif_len;
extern const char favicon_ico[];
extern unsigned int favicon_ico_len;

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */

WEB_PAGES_t g_web_pages[] = {
    {HTTP_CB_Index, "/"},
    {HTTP_CB_Scan, "/scan"},            
    {HTTP_CB_Provision, "/provision"},  
    {HTTP_CB_Logo, "/mchp.gif"},    
    //{HTTP_CB_Icon, "/favicon.ico"},   
    {NULL, NULL}
};


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */

void HTTP_CB_Index(uint32_t socket, uint8_t *input)
{
    HTTP_RESP_Send(socket, HTTP_RESPONSE_HDR, main_htm, "text/html", main_htm_len);
}

void HTTP_CB_Scan(uint32_t socket, uint8_t *input)
{
    printf("Trigger Scan\n");    
    RNWF_WIFI_SrvCtrl(RNWF_WIFI_ACTIVE_SCAN, NULL);    
    g_scan_socket = socket;    
    http_buffer[HTTP_HDR_OFFSET] = '\0';    
}


void HTTP_CB_Provision(uint32_t socket, uint8_t *input)
{
    if(input != NULL)
    {
        
        uint8_t *ssid = NULL, *passphrase = NULL, *security = NULL;
        printf("FORM Data = %s\n", input);
        if((passphrase = (uint8_t *)strstr((char *)input, "pwd:")) != NULL)
        {            
            *passphrase = '\0';
            passphrase += 4;
        }
        else        
            return; 
        if((security = (uint8_t *)strstr((char *)input, "security:")) != NULL)
        {
            *security = '\0';
            security += 9;                        
        }
        else        
            return;
        if((ssid = (uint8_t *)strstr((char *)input, "ssid:")) != NULL)
        {
            *ssid = '\0';
            ssid += 5;
        }
        else        
            return;
                               
    
        HTTP_RESP_Send(socket, HTTP_RESPONSE_HDR, "Provision Success!", "text/html", strlen("Provision Success!"));
        
        /* Wi-Fii Connectivity */
        RNWF_WIFI_PARAM_t wifi_sta_cfg = {RNWF_WIFI_MODE_STA, ssid, passphrase, *security-'0', 1};

        RNWF_WIFI_SrvCtrl(RNWF_SET_WIFI_PARAMS, &wifi_sta_cfg);
    }
   
}

void HTTP_CB_Icon(uint32_t socket, uint8_t *input)
{
    HTTP_RESP_Send(socket, HTTP_RESPONSE_HDR, favicon_ico, "image/ico", favicon_ico_len);
    
}

void HTTP_CB_Logo(uint32_t socket, uint8_t *input)
{
    HTTP_RESP_Send(socket, HTTP_RESPONSE_HDR, mchp_gif, "image/gif", mchp_gif_len);
    
}

void HTTP_RESPONSE_Error(uint32_t socket, uint8_t *input)
{          
    HTTP_RESP_Send(socket, HTTP_RESPONSE_NOT_FOUND, NULL, NULL, 0);
}

void HTTP_REQ_Parser(uint32_t socket, uint16_t rx_len) {
   
    uint8_t *request = NULL, *end_str, *content = NULL;    
    uint8_t page_idx = 0;
    
    if(RNWF_NET_SOCK_Read(socket, rx_len, (uint8_t *)http_buffer, RNWF_BINARY_MODE) == RNWF_PASS)
    {
        request = (uint8_t *)strchr((char *)http_buffer, ' ') + 1;   
        end_str = (uint8_t *)strchr((char *)request, ' ');        
        content = (uint8_t *)strstr((char *)http_buffer, "\r\n\r\n");
        if(request != NULL && (end_str != NULL))
        {            
            http_buffer[end_str - http_buffer] = '\0';
            printf("[%d]Req -> %s [%d]URL -> %s\n", strlen((char *)request), request, strlen(g_web_pages[page_idx].url), g_web_pages[page_idx].url);
            while(g_web_pages[page_idx].url != NULL)
            {
                printf("page idx = %d\n", page_idx);                
                if(strlen((char *)request) == strlen(g_web_pages[page_idx].url))
                {
                    for(int idx = 0; idx < strlen((char *)request); idx++)
                    {
                        if(request[idx] != g_web_pages[page_idx].url[idx])
                        {       
                            page_idx++;
                            continue;
                        }
                    }
                    if(g_web_pages[page_idx].handler != NULL)
                    {                        
                        g_web_pages[page_idx].handler(socket, content);
                        return;
                    }
                } 
                page_idx++;
            }            
        }
        HTTP_RESPONSE_Error(socket, NULL);
    }        
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */

uint16_t HTTP_RESP_Send(uint32_t socket, const char * resp_hdr, const char *webpage, const char *page_type, uint16_t page_len) {
   
    uint16_t page_offset = 0;                        
    
    sprintf((char *)http_buffer, resp_hdr, page_type, page_len);            
    RNWF_NET_SOCK_Write(socket, strlen((char *)http_buffer), (uint8_t *)http_buffer, RNWF_BINARY_MODE);
    while(page_len > 0)
    {                       
        if(page_len > HTTP_BUFFER_LEN)
        {                                
            memcpy(http_buffer, &webpage[page_offset], HTTP_BUFFER_LEN);
            RNWF_NET_SOCK_Write(socket, HTTP_BUFFER_LEN, (uint8_t *)http_buffer, RNWF_BINARY_MODE);                    
            page_offset += HTTP_BUFFER_LEN; 
            page_len -= HTTP_BUFFER_LEN;
        }
        else
        {            
            memcpy(http_buffer, &webpage[page_offset], page_len);                     
            RNWF_NET_SOCK_Write(socket, page_len, (uint8_t *)http_buffer, RNWF_BINARY_MODE);
            page_len = 0;
        }
    }
                
    return 0;    
}

/* *****************************************************************************
 End of File
 */
