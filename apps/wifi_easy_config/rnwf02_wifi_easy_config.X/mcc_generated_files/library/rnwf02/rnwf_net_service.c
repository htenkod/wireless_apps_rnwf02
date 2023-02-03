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

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdio.h>
#include <string.h>

#include "../../timer/delay.h"

#include "rnwf_interface.h"
#include "rnwf_net_service.h"

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
RNWF_NET_SOCK_CALLBACK_t gSocket_CallBack_Handler;


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
    RNWF_WIFI_RESULT_t RNWF_NET_SysCtrl( RNWF_WIFI_SERVICE_t request, void *input) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
RNWF_RESULT_t RNWF_NET_SOCK_SrvCtrl( RNWF_NET_SOCK_SERVICE_t request, void *input)  {
         
    RNWF_RESULT_t result = RNWF_FAIL; 
    switch(request)
    {
        case RNWF_NET_DHCP_SERVER_ENABLE:
        {
            if(input == NULL)
                break;
            
            const char **dhcps_cfg_list = input;                        
            if(dhcps_cfg_list[0] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_NETIF_SET_IP, dhcps_cfg_list[0]);            
            if(dhcps_cfg_list[1] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_DHCPS_SET_POOL, dhcps_cfg_list[1]);
            if(dhcps_cfg_list[2] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_DHCPS_SET_GW, dhcps_cfg_list[2]); 
            
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_DHCPS_ENABLE);
            
            break;
        }
        case RNWF_NET_DHCP_SERVER_DISABLE:
        {
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_DHCPS_DISABLE);   
            break;
        }
        case RNWF_NET_SOCK_TCP_OPEN: 
        {
            RNWF_NET_SOCKET_t *socket = (RNWF_NET_SOCKET_t*)(input);       
            if(RNWF_CMD_SEND_OK_WAIT(RNWF_SOCK_OPEN_RESP, socket->sock_master, RNWF_SOCK_OPEN_TCP) == RNWF_PASS)
            {
                RNWF_RESPONSE_Trim(socket->sock_master);
                switch(socket->bind_type)
                {
                    case RNWF_BIND_LOCAL:
                        result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BIND_LOCAL, socket->sock_master, socket->sock_port);                        
                        break;
                    case RNWF_BIND_REMOTE:
                        result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BIND_REMOTE, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;
                    case RNWF_BIND_MCAST:
                        result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BIND_MCAST, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;   
                    default:
                        break;
                }               
            }                                    
            break;
        }
            
        case RNWF_NET_SOCK_UDP_OPEN:   
        {
            RNWF_NET_SOCKET_t *socket = (RNWF_NET_SOCKET_t*)(input);               
            if(RNWF_CMD_SEND_OK_WAIT(RNWF_SOCK_OPEN_RESP, socket->sock_master, RNWF_SOCK_OPEN_UDP) == RNWF_PASS)
            {
                switch(socket->bind_type)
                {
                    case RNWF_BIND_LOCAL:
                        result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BIND_LOCAL, socket->sock_master, socket->sock_port);                        
                        break;
                    case RNWF_BIND_REMOTE:
                        result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BIND_REMOTE, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;
                    case RNWF_BIND_MCAST:
                        result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BIND_MCAST, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;   
                    default:
                        break;
                }               
            }             
            break;
        }
            
        case RNWF_NET_SOCK_CLOSE:
        {
            uint32_t socket = *((uint32_t *)input);
            if(socket)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_CLOSE, socket);            
            break;
        }
        case RNWF_NET_SOCK_CONFIG:
        {
            RNWF_NET_SOCKET_CONFIG_t *sock_cfg = (RNWF_NET_SOCKET_CONFIG_t *)input;
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_CONFIG_NODELAY, sock_cfg->sock_id, sock_cfg->sock_nodelay);            
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_CONFIG_KEEPALIVE, sock_cfg->sock_id, sock_cfg->sock_keepalive);              
            break;
        }
        case RNWF_NET_TLS_CONFIG:
        {
            char **tls_cfg_list = input;            
            if(tls_cfg_list[RNWF_NET_TLS_CA_CERT] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_TLS_SET_CA_NAME, tls_cfg_list[RNWF_NET_TLS_CA_CERT]);     
            if(tls_cfg_list[RNWF_NET_TLS_CERT_NAME] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_TLS_SET_CERT_NAME, tls_cfg_list[RNWF_NET_TLS_CERT_NAME]);     
            if(tls_cfg_list[RNWF_NET_TLS_KEY_NAME] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_TLS_SET_KEY_NAME, tls_cfg_list[RNWF_NET_TLS_KEY_NAME]);     
            if(tls_cfg_list[RNWF_NET_TLS_KEY_PWD] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_TLS_SET_KEY_PWD, tls_cfg_list[RNWF_NET_TLS_KEY_PWD]);     
            if(tls_cfg_list[RNWF_NET_TLS_SERVER_NAME] != NULL)
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_TLS_SERVER_NAME, tls_cfg_list[RNWF_NET_TLS_SERVER_NAME]);                 
            
            break;
        }
        case RNWF_NET_SOCK_SET_CALLBACK:
            if(input != NULL)
            {
                gSocket_CallBack_Handler = (RNWF_NET_SOCK_CALLBACK_t)(input);            
                result = RNWF_PASS;
            }
            break;
            
        default:
            break;
    }        
    return result;
}

RNWF_RESULT_t RNWF_NET_SOCK_Write( uint32_t socket, uint16_t length, uint8_t *input, RNWF_SOCK_RW_MODE_t wr_mode)  {
    
    RNWF_RESULT_t result = RNWF_FAIL;
    
    switch(wr_mode)
    {        
        case RNWF_BINARY_MODE:
        {
            //if(socket->sock_type == RNWF_SOCK_TCP)
            if(1)
            {          
                
                if((result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BINARY_WRITE_TCP, socket, length)) == RNWF_PASS)     
                {                                        
                    //RNWF_CMD_SEND_OK_WAIT(NULL, NULL, "%.*s", length, input);
                    RNWF_RAW_Write(input, length);                                                            
                }
               
            }
            else
            {
                //if((result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_BINARY_WRITE_UDP, socket, socket->sock_addr, socket->sock_port, length)) == RNWF_PASS)          
                //    RNWF_RAW_Write(input, length);

            }
            break;
        }
#if 0            
        case RNWF_ASCII_MODE:
            //RNWF_PROCESS_Ascii();  
            if(socket->sock_type == RNWF_SOCK_TCP)
            {             
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_ASCII_WRITE_TCP, socket->sock_client, length, length, input);           
            }
            else
            {
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_ASCII_WRITE_UDP, socket->sock_client, socket->sock_addr, socket->sock_port, length, input);            

            }
            break;   
#endif            
        default:
            break;
    }
    
    return result;
}

RNWF_RESULT_t RNWF_NET_SOCK_Read( uint32_t socket, uint16_t length, uint8_t *buffer, RNWF_SOCK_RW_MODE_t rd_mode)  {                
    RNWF_RESULT_t result = RNWF_FAIL;
    
    switch(rd_mode)
    {
        case RNWF_BINARY_MODE: 
            buffer[0] = '\0';
            while(length > strlen((char *)buffer))
            {                                
                if((result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_SOCK_READ, socket, RNWF_BINARY_MODE, length-strlen((char *)buffer))) == RNWF_PASS)
                {                                    
                    RNWF_CMD_SEND_OK_WAIT(NULL, buffer, NULL); 
                }
                
            }
            break;
        case RNWF_ASCII_MODE:    
            result = RNWF_CMD_SEND_OK_WAIT(RNWF_SOCK_READ_RESP, buffer, RNWF_SOCK_READ, socket, rd_mode, length);    
            //RNWF_PROCESS_Ascii();            
            break;
        default:
            break;
    };        
    
    return result;
}


/* *****************************************************************************
 End of File
 */
