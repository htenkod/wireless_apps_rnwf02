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
    
    RNWF_NET_SOCKET_t *socket = (RNWF_NET_SOCKET_t*)(input);        
    RNWF_RESULT_t result = RNWF_FAIL; 
    switch(request)
    {
        case RNWF_NET_SOCK_TCP_OPEN:                        
            if(RNWF_CMD_RSP_Send(RNWF_SOCK_OPEN_RESP, socket->sock_master, RNWF_SOCK_OPEN_TCP) == RNWF_PASS)
            {
                switch(socket->bind_type)
                {
                    case RNWF_BIND_LOCAL:
                        result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_BIND_LOCAL, socket->sock_master, socket->sock_port);                        
                        break;
                    case RNWF_BIND_REMOTE:
                        result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_BIND_REMOTE, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;
                    case RNWF_BIND_MCAST:
                        result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_BIND_MCAST, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;   
                    default:
                        break;
                }               
            }                                    
            break;
            
        case RNWF_NET_SOCK_UDP_OPEN:            
            if(RNWF_CMD_RSP_Send(RNWF_SOCK_OPEN_RESP, socket->sock_master, RNWF_SOCK_OPEN_UDP) == RNWF_PASS)
            {
                switch(socket->bind_type)
                {
                    case RNWF_BIND_LOCAL:
                        result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_BIND_LOCAL, socket->sock_master, socket->sock_port);                        
                        break;
                    case RNWF_BIND_REMOTE:
                        result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_BIND_REMOTE, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;
                    case RNWF_BIND_MCAST:
                        result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_BIND_MCAST, socket->sock_master, socket->sock_addr, socket->sock_port);
                        break;   
                    default:
                        break;
                }               
            }             
            break;
            
        case RNWF_NET_SOCK_LISTEN_CLOSE:
            result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_CLOSE, socket->sock_master);            
            break;
        
        case RNWF_NET_SOCK_CLIENT_CLOSE:
            result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_CLOSE, socket->sock_client);            
            break;
                    
        case RNWF_NET_SOCK_CONFIG:
            
            break;
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

RNWF_RESULT_t RNWF_NET_SOCK_Write( RNWF_NET_SOCKET_t *socket, uint16_t length, uint8_t *input)  {
    
    RNWF_RESULT_t result = RNWF_FAIL;
    
    if(length)
    {
        if(socket->sock_type == RNWF_SOCK_TCP)
        {             
            result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_WRITE_TCP, socket->sock_client, length, length, input);           
        }
        else
        {
            result = RNWF_CMD_RSP_Send(NULL, NULL, RNWF_SOCK_WRITE_UDP, socket->sock_client, socket->sock_addr, socket->sock_port, length, input);            

        }   
    }
    
    return result;
}

RNWF_RESULT_t RNWF_NET_SOCK_Read( RNWF_NET_SOCKET_t *socket, uint16_t length, uint8_t *buffer, RNWF_SOCK_MODE_t read_mode)  {                
    RNWF_RESULT_t result = RNWF_FAIL;
    
    switch(read_mode)
    {
        case RNWF_BINARY_MODE:
            result = RNWF_CMD_RSP_Send("#", buffer, RNWF_SOCK_READ, socket->sock_client, read_mode, length);            
            break;
        case RNWF_ASCII_MODE:            
            break;
        default:
            break;
    };        
    
    return result;
}


/* *****************************************************************************
 End of File
 */
