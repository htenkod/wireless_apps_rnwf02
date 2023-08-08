## Device Firmware Udpate (DFU)

The RNWF02 modules are secured parts and all treditional programming interfaces are disabled. These modules can only execute the firmwares which are signed by Microchip's signer. 

As all the programming interfaces are disabled, the RNWF02 module's enable a special mode called DFU mode to perform the Firmware update. 


In order to place the device in DFU mode a unique pattern('MCHP') needs to be triggered on the following pins:-

| RNWF02 Module      |  Description                   |
|--------------------|------------------------------- |
|MCLR_N (Pin#4)      | Master clear reset, active-low |
|PB0/DFU_Rx (Pin#26) | DFU pattern clock / UART Rx    |
|PB1/DFU_Tx (Pin#10) | DFU pattern data / UART Tx     |


Following is the screenshot of the DFU mode pattern. 

<p align="center"><img width="700" src="../../assets/dfu_pattern.png">
      </p>



On successful entry of DFU mode, the PB0/DFU_Rx (Pin#26) and PB1/DFU_Tx (Pin#10) pins are reconfigured as UART lines with the ***230400 8 NONE 1*** configuration. 



In DFU mode, the RNWF02 module runs a program executive(PE) firmware which can support following operations. 
- PE Version read
<!---	
	The PE Version read command frame is as following:- 

	|READ   | byte 0 | CMD   | byte 2|
	|-------|--------|-------|-------|
	| 0x01  | 0x00   | 0x07  | 0x01  |

	The response to the command would be 4 bytes in the following format:-

	|PE Version | byte 1 | CMD   | byte 3    |
	|-----------|--------|-------|-----------|
	| 0x01      | 0x00   | 0x07  | 0x00      |
--->
- Device ID Read
<!---
	The Device ID read command frame is as following:- 

	|READ   | byte0 | byte 1| byte 2|
	|-------|-------|-------|-------|
	| 0x01  | 0x00  | 0x00  | 0x01  |

	The response to the command would be 8 bytes in the following format:-

	| byte 0| byte 1 | CMD   | byte 3   | ID Byte 0 | ID Byte 0 | ID Byte 0 | ID Byte 0 |
	|-------|--------|-------|----------|-----------|-----------|-----------|-----------|
	| 0x00  | 0x00   | 0x0A  | 0x00     | 0x53      | 0x00      |   0xC7    |  0x29     |  
--->
- Flash Erase

- Flash Write

These PE operations are triggered using a 4 bytes command frame and response length depends on the requested operation. 

The successful entry of the DFU mode is verified by reading the PE version and Device ID.
Once the device is in DFU mode, the device's secured flash can be erased and Firmware binary can can be writen over the UART interface.

The OTA service layer implements these functionality to ease the development of Host Assisted OTA. 

We also support a PC based python tool to perform the DFU on RNWF02 modules. Please refer the Tools->Device Programming section for more details.


**_NOTE:-_** 

- For the Host assisted DFU, the Host side pins should be able to drive the pattern and also reconfigure the same pins as UART lines using the pin multiplexing options. We recommend to use Microchip's Microcontrollers as host which can support this feature by default

- The RNWF02 AddOn Board has the interconnected UART1_Tx to PB1/DFU_Tx and UART1_Rx with PB0_Rx to enable both Mission Mode and DFU operation over the single UART interface.

 



