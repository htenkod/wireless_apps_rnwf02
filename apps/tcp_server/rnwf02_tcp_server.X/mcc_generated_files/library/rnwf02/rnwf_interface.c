/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "rnwf_interface.h"
#include "rnwf_wifi_service.h"
#include "rnwf_net_service.h"
/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

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
RNWF_INTERFACE_STATE_t   g_interface_state = RNWF_INTERFACE_FREE;

uint8_t g_if_buffer[RNWF_INTERFACE_LEN_MAX];


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

RNWF_RESULT_t RNWF_IF_SW_Reset(void)
{    
    return RNWF_CMD_RSP_Send(NULL, NULL, "\r\n", NULL);    
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

RNWF_RESULT_t RNWF_IF_ASYNC_Handler(uint8_t *p_msg)
{    
    uint16_t arg_len = 0;
    RNWF_RESULT_t result = RNWF_COTN;
    uint8_t *p_arg = (uint8_t *)(strstr((char *)p_msg, RNWF_ARG_DELIMETER) + 1);
    while(p_arg[arg_len] != '\0')
    {
        (p_arg[arg_len] == ',') ? p_arg[arg_len++] = ' ':arg_len++;        
    }
    
#ifdef RNWF_INTERFACE_DEBUG     
    //printf("Async Arguments-> %s\n", p_arg);
#endif
    
    if(strstr((char *)p_msg, RNWF_EVENT_SOCK_CONNECTED))
    {                 
        if(gSocket_CallBack_Handler)
            gSocket_CallBack_Handler(RNWF_NET_SOCK_EVENT_CONNECTED, p_arg);
            
    }
    
    if(strstr((char *)p_msg, RNWF_EVENT_SOCK_TCP_RECV))
    {
        uint16_t rx_len = 0;                   
        sscanf((char *)p_arg, "%*d %d", &rx_len); 
        if(gSocket_CallBack_Handler)
            gSocket_CallBack_Handler(RNWF_NET_SOCK_EVENT_READ, (uint8_t *)&rx_len);                
    }    
    
    if(strstr((char *)p_msg, RNWF_EVENT_AUTO_IP))
    {                        
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_DHCP_DONE, p_arg);        
    }
    
    if(strstr((char *)p_msg, RNWF_EVENT_LINK_LOSS))
    {
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_DISCONNECTED, p_arg); 
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_LINK_UP))
    {
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_CONNECTED, p_arg);                     
    }
    if(strstr((char *)p_msg, RNWF_EVENT_ERROR))
    {
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_CONNECT_FAILED, p_arg);   
    }
    if(strstr((char *)p_msg, RNWF_EVENT_SCAN_IND))
    {
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_SCAN_INDICATION, p_arg);   
    }
    if(strstr((char *)p_msg, RNWF_EVENT_SCAN_DONE))
    {     
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_SCAN_DONE, p_arg);  
        result = RNWF_PASS;
    }
    
    return result;
}



/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
RNWF_RESULT_t RNWF_CMD_RSP_Send(const char *delimeter, uint8_t *response, const char *format, ...)
{
    uint8_t *p_frame = g_if_buffer;
    RNWF_RESULT_t result = RNWF_FAIL;
    size_t cmd_len, rsp_len = 0;
    va_list args = {0};   
    //memset(g_interface_send_buffer, 0, RNWF_INTERFACE_LEN_MAX);
    /* Get the variable arguments in va_list */
    
    if(format != NULL)
    {
        RNWF_IS_INTERFACE_BUSY();

        va_start( args, format );                  
        cmd_len = vsnprintf((char *)g_if_buffer, RNWF_INTERFACE_LEN_MAX, format, args);        
        va_end(args); 
#ifdef RNWF_INTERFACE_DEBUG        
        printf("DBG:cmd[%d] -> %s", cmd_len, p_frame);
#endif /* RNWF_INTERFACE_DEBUG */        

        while(*p_frame != '\0')
        {
            if(UART0.IsTxReady()) 
            {
                UART0.Write(*p_frame++); 
                while(!UART0.IsTxDone());
            }
        }
        memset(g_if_buffer, 0, cmd_len);
    }
    
        
    while(RNWF_INTERFACE_TIMEOUT) //later make it timeout
    {        
        if(UART0.IsRxReady())
        {              
            if(strstr((char *)g_if_buffer, "\r\n"))
            {           
#ifdef RNWF_INTERFACE_DEBUG       
                printf("DBG:rsp[%d] <- %.*s", rsp_len, rsp_len, g_if_buffer);
#endif /* RNWF_INTERFACE_DEBUG */                     
                g_if_buffer[rsp_len-2] = '\0';  
                g_if_buffer[rsp_len-1] = '\0';  
                if(strstr((char *)g_if_buffer, "\r+"))
                {    
                    RNWF_SET_INTERFACE_FREE();
                    if((result = RNWF_IF_ASYNC_Handler(g_if_buffer)) == RNWF_PASS)
                    {                       
                        break;
                    }
                    RNWF_SET_INTERFACE_BUSY();                    
                }                 
                else if(delimeter != NULL && strstr((char *)g_if_buffer, delimeter))
                {
                    if(response != NULL)
                    {                    
                        strcpy((char *)response, (char *)g_if_buffer+strlen(delimeter));
                    }
                }
                else if(strstr((char *)g_if_buffer, RNWF_AT_ERROR))
                {
                    if(response != NULL)
                    {                    
                        strcpy((char *)response, (char *)g_if_buffer+strlen(RNWF_AT_ERROR));
                    }
                    result = RNWF_FAIL;
                    break;
                }
                else if((format != NULL) && strstr((char *)g_if_buffer, RNWF_AT_DONE))
                {
                    result = RNWF_PASS;
                    break;                    
                }                                
                rsp_len = 0;
            }            
            else 
            {                
                if(rsp_len < RNWF_INTERFACE_LEN_MAX)
                {
                    g_if_buffer[rsp_len++] = UART0.Read();                  
                }
                else
                {
                    //truncate the buffer till '\r\n'            
                    g_if_buffer[rsp_len-2] = g_if_buffer[rsp_len-1];
                    rsp_len = rsp_len-1;    //
                }
            }            
        }
    }                
    
    RNWF_SET_INTERFACE_FREE();
    
    return result;
    
    
}

/* *****************************************************************************
 End of File
 */
