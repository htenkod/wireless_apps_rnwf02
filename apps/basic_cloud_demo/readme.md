Azure Cloud Demo

The Azure Cloud Application demonstrates the Azure Plug and Play connection with the Azure IoT Central. The RNWF02 board acts as a MQTT client using the inbuilt MQTT AT Command sets. The demo uses the x.509 certificate based group enrollment to ease the connection of multiple devices to the Azure cloud.

The RNWF02 module ships with a built-in X.509 root certificates to authenticate Azure MQTT server which simplifies the TLS handshake protocol with Microsoft Azure.

The user can upload the device certificates into the RNWF02 for the TLS client authentication. Using this application, most users can connect their Microchip RNWF02 to Azure Cloud/Azure IoT Hub in a few minutes.

## Running the Application

1. Create a Root of Trust Chain for RNWF Devices

	The demo applicaiton includes a set of tools in "../apps/azure_cloud/tools" folder. It enables easy creation of certificate infrastructure and individual device certificates with very minimal user inputs.




>| :exclamation:    Note| 
>|-----------------------------------------|
>|On Windows Operating Systems, make sure the [GitBash](https://git-scm.com/download/win) is installed to run these tools. |
>|These scripts are based on the Azure's Create and Upload Certificates for Testing tutorial.|



1. 1.  Right click and open the GitBash in the tools folder
<p align="center"><img width="700" src="../../assets/git_bash_prompt.png"></p>


1. 2 Run the create_initial_setup.sh as shown in the following screenshot. It will request the user to provide the domain suffix and common name for Root CA.
<p align="center"><img width="700" src="../../assets/init_cert_infra.png"></p>


Up on successful execution of above command, following 3 new folders will be created!
<p align="center"><img width="700" src="../../assets/cert_infra_folders.png"></p>


Device Certificate

1.3) Run the create_device_certificate.sh to create individual device certificate. It requests the user to provide Subordinate/Intermediate CA folder name and a unique device id (Common Name).
<p align="center"><img width="700" src="../../assets/dev_cert_cmd.png"></p>


Note:- In order to modify the default subject identifier information, open the create_device_certificate.sh and update the following macros.
<p align="center"><img width="700" src="../../assets/dev_cert_sub_info.png"></p>


On successful execution of device certificate, a new folder is created inside the ../tools/devcerts folder as shown in following screenshot
<p align="center"><img width="700" src="../../assets/dev_cert_files.png"></p>


The <device id>.pem and * <device id>.key* files highlighted/marked above should be programmed into the RNWF device using the AT commands or through the cert key flash tools
Create a Microsoft Azure Account and Azure IoT Central Application

2. 1 Create a new Azure Account if you don't already have one.
<p align="center"><img width="700" src="../../assets/git_bash_prompt.png"></p>


2. 2 Log into the [Azure Portal](https://azure.microsoft.com/en-us/free) using the new/existing account

2. 3 Create an IoT Central Applicaiton at Create a resource -> Internet of Things
<p align="center"><img width="700" src="../../assets/azure_iot_central_resource.png"></p>

2. 4 Under Subscription create a new group (say RNWF) to manage it's resources and cost

2. 5 Provide the resource name and Application URL to view/manage the IoT Central devices
<p align="center"><img width="700" src="../../assets/azure_iot_central_app.png"></p>

2. 6 Open the [Azure Central Applicaiton](https://apps.azureiotcentral.com/build) and build a new App
<p align="center"><img width="700" src="../../assets/apps_portal_build.png"></p>


2. 7 Select the application and navigate to 'Permision->Device connection groups'

2. 8 Node down the ID scope and click '+ New' to create a enrollment group

<p align="center"><img width="700" src="../../assets/apps_portal_enrollment.png"></p>




2.9

Mount AVR128DB48 Curiosity Nano and RNWF02 Add On Board on Curiosity Nano base for click boards at respective headers. For more details about the boards placement in the Curiosity Nano base, see Figure 6-1.

Connect the debugger USB port on the AVR128DB48 Curiosity Nano board to computer using a micro USB cable

Open the project and launch MCC with Melody Content Manager Tool

Configure Home-AP credentials for STA Mode

Update the Azure Cloud configuration details with the ID Scope noted in the above 2.1 step

Regenerate, build and program the code to the hardware using IDEA

As the board boots up, application will list available certificates and keys on RNWF02 board. The board will connect to Home-AP configured. After this, the demo will attempt to connect to Azure IoT Hub (using link configured) and start performing telemetry. User can modify device properties from Azure Cloud with the help of configured Azure IoT central app as shown below

Wi-Fi and MQTT Connection, Telemetry LED ON-OFF

Telemetry image 2

Change Device Parameters/ How to manipulate: Cloud to Device(C2D) Parameters

