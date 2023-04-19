#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/system/src/config_bits.c mcc_generated_files/system/src/protected_io.S mcc_generated_files/system/src/interrupt.c mcc_generated_files/system/src/pins.c mcc_generated_files/system/src/system.c mcc_generated_files/system/src/clock.c mcc_generated_files/timer/src/delay.c mcc_generated_files/uart/src/usart3.c mcc_generated_files/uart/src/usart2.c main.c mcc_generated_files/library/rnwf02/rnwf_ota_service.c mcc_generated_files/library/rnwf02/rnwf_wifi_service.c mcc_generated_files/library/rnwf02/rnwf_interface.c mcc_generated_files/library/rnwf02/rnwf_net_service.c mcc_generated_files/library/rnwf02/rnwf_system_service.c mcc_generated_files/library/rnwf02/rnwf_mqtt_service.c mcc_generated_files/library/rnwf02/rnwf_provision_service.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o ${OBJECTDIR}/mcc_generated_files/system/src/system.o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o ${OBJECTDIR}/mcc_generated_files/system/src/system.o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o

# Source Files
SOURCEFILES=mcc_generated_files/system/src/config_bits.c mcc_generated_files/system/src/protected_io.S mcc_generated_files/system/src/interrupt.c mcc_generated_files/system/src/pins.c mcc_generated_files/system/src/system.c mcc_generated_files/system/src/clock.c mcc_generated_files/timer/src/delay.c mcc_generated_files/uart/src/usart3.c mcc_generated_files/uart/src/usart2.c main.c mcc_generated_files/library/rnwf02/rnwf_ota_service.c mcc_generated_files/library/rnwf02/rnwf_wifi_service.c mcc_generated_files/library/rnwf02/rnwf_interface.c mcc_generated_files/library/rnwf02/rnwf_net_service.c mcc_generated_files/library/rnwf02/rnwf_system_service.c mcc_generated_files/library/rnwf02/rnwf_mqtt_service.c mcc_generated_files/library/rnwf02/rnwf_provision_service.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=AVR128DB48
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o: mcc_generated_files/system/src/config_bits.c  .generated_files/flags/default/95d6114148770909033453155b456f68ebe843b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o -o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o mcc_generated_files/system/src/config_bits.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o: mcc_generated_files/system/src/interrupt.c  .generated_files/flags/default/6b2ae26a9b8b313c7f0c782cf7f03fe328259b30 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o -o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o mcc_generated_files/system/src/interrupt.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/pins.o: mcc_generated_files/system/src/pins.c  .generated_files/flags/default/8b1b175ed03cb00326644b2270839d3afefaa86a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/pins.o -o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o mcc_generated_files/system/src/pins.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/system.o: mcc_generated_files/system/src/system.c  .generated_files/flags/default/1866d876014d2cdb5acf83e446f41d49ae7083c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/system.o -o ${OBJECTDIR}/mcc_generated_files/system/src/system.o mcc_generated_files/system/src/system.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/clock.o: mcc_generated_files/system/src/clock.c  .generated_files/flags/default/6446718cc583234163df288b22007c8876d13e63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/clock.o -o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o mcc_generated_files/system/src/clock.c 
	
${OBJECTDIR}/mcc_generated_files/timer/src/delay.o: mcc_generated_files/timer/src/delay.c  .generated_files/flags/default/713d4b1ecd570b8ff7262a6dd25db9c42516cd3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d" -MT "${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d" -MT ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o -o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o mcc_generated_files/timer/src/delay.c 
	
${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o: mcc_generated_files/uart/src/usart3.c  .generated_files/flags/default/1b747685063b14e8052041c7772bae7d4476bed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d" -MT "${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d" -MT ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o -o ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o mcc_generated_files/uart/src/usart3.c 
	
${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o: mcc_generated_files/uart/src/usart2.c  .generated_files/flags/default/4644631bfb9b3db0e25b28a7a5d4c90e15687612 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d" -MT "${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d" -MT ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o -o ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o mcc_generated_files/uart/src/usart2.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/a4f973458a85f2cfb3c6bf5cdd2de640f4636256 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o: mcc_generated_files/library/rnwf02/rnwf_ota_service.c  .generated_files/flags/default/ffcc6cf36efeb5feaa8ca0e39b6a76f3b6634204 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o mcc_generated_files/library/rnwf02/rnwf_ota_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o: mcc_generated_files/library/rnwf02/rnwf_wifi_service.c  .generated_files/flags/default/5184a07da5e1c0b7e796acd0f524bec7bbb6a8e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o mcc_generated_files/library/rnwf02/rnwf_wifi_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o: mcc_generated_files/library/rnwf02/rnwf_interface.c  .generated_files/flags/default/d17be77446ce33466c66b3a54cdc2012c547fbe9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o mcc_generated_files/library/rnwf02/rnwf_interface.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o: mcc_generated_files/library/rnwf02/rnwf_net_service.c  .generated_files/flags/default/f2e60b47e912670ac6fe00c38ec15324e557ea15 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o mcc_generated_files/library/rnwf02/rnwf_net_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o: mcc_generated_files/library/rnwf02/rnwf_system_service.c  .generated_files/flags/default/b240d65bbe710dd2ba5f7fe4d4ef483294e0ff76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o mcc_generated_files/library/rnwf02/rnwf_system_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o: mcc_generated_files/library/rnwf02/rnwf_mqtt_service.c  .generated_files/flags/default/72ab9e94795bd293743f252d96963976b42d04c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o mcc_generated_files/library/rnwf02/rnwf_mqtt_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o: mcc_generated_files/library/rnwf02/rnwf_provision_service.c  .generated_files/flags/default/44c43f232f2eddd19ffe5899f9f330d01cefe24f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o mcc_generated_files/library/rnwf02/rnwf_provision_service.c 
	
else
${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o: mcc_generated_files/system/src/config_bits.c  .generated_files/flags/default/b170032cada09362bc3716b744b7448b7acbbf28 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o -o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o mcc_generated_files/system/src/config_bits.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o: mcc_generated_files/system/src/interrupt.c  .generated_files/flags/default/9d728a642d7246c0e192eb673bc1699e8e5df7eb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o -o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o mcc_generated_files/system/src/interrupt.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/pins.o: mcc_generated_files/system/src/pins.c  .generated_files/flags/default/25655f26699543fd2efec6d176c9fa36d488f932 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/pins.o -o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o mcc_generated_files/system/src/pins.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/system.o: mcc_generated_files/system/src/system.c  .generated_files/flags/default/c9d2fb5cb68fcb7ac963170d5e47e0cd28bec5a7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/system.o -o ${OBJECTDIR}/mcc_generated_files/system/src/system.o mcc_generated_files/system/src/system.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/clock.o: mcc_generated_files/system/src/clock.c  .generated_files/flags/default/e12cb5e7f315739c0c429578451591f5f401f6b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/clock.o -o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o mcc_generated_files/system/src/clock.c 
	
${OBJECTDIR}/mcc_generated_files/timer/src/delay.o: mcc_generated_files/timer/src/delay.c  .generated_files/flags/default/f62a3d983fd8d31ecba05f78469ed6b58137891b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d" -MT "${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d" -MT ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o -o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o mcc_generated_files/timer/src/delay.c 
	
${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o: mcc_generated_files/uart/src/usart3.c  .generated_files/flags/default/53f8ab384e6c30cec39d294d5f8d131bab103f92 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d" -MT "${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o.d" -MT ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o -o ${OBJECTDIR}/mcc_generated_files/uart/src/usart3.o mcc_generated_files/uart/src/usart3.c 
	
${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o: mcc_generated_files/uart/src/usart2.c  .generated_files/flags/default/307200371a525ad73386662b935547a158cb1cbd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d" -MT "${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o.d" -MT ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o -o ${OBJECTDIR}/mcc_generated_files/uart/src/usart2.o mcc_generated_files/uart/src/usart2.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/55c560d844ea2cea1abc4c6190602dcde0ebefad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o: mcc_generated_files/library/rnwf02/rnwf_ota_service.c  .generated_files/flags/default/2acf5d0db7f75ab2824ea8c56af3bb5fe4f2d9b1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_ota_service.o mcc_generated_files/library/rnwf02/rnwf_ota_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o: mcc_generated_files/library/rnwf02/rnwf_wifi_service.c  .generated_files/flags/default/20fc6bb04fb53d576e6e2ce3e2524e26e84b8703 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_wifi_service.o mcc_generated_files/library/rnwf02/rnwf_wifi_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o: mcc_generated_files/library/rnwf02/rnwf_interface.c  .generated_files/flags/default/a0b7a7f5459a63013b73eb44b7715597d59b6c52 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_interface.o mcc_generated_files/library/rnwf02/rnwf_interface.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o: mcc_generated_files/library/rnwf02/rnwf_net_service.c  .generated_files/flags/default/f30c5a5fca856ebdd1adf6f22981af8b2909c8dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_net_service.o mcc_generated_files/library/rnwf02/rnwf_net_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o: mcc_generated_files/library/rnwf02/rnwf_system_service.c  .generated_files/flags/default/f94cd251d31537b25c1a148d9f31761383b740b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_system_service.o mcc_generated_files/library/rnwf02/rnwf_system_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o: mcc_generated_files/library/rnwf02/rnwf_mqtt_service.c  .generated_files/flags/default/c1a091bf5e8068cb33b1431b861df0259e03bd57 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_mqtt_service.o mcc_generated_files/library/rnwf02/rnwf_mqtt_service.c 
	
${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o: mcc_generated_files/library/rnwf02/rnwf_provision_service.c  .generated_files/flags/default/b12c02b99fa76ab02c3d4f851f73bd344b5392d0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/library/rnwf02" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d" -MT "${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o.d" -MT ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o -o ${OBJECTDIR}/mcc_generated_files/library/rnwf02/rnwf_provision_service.o mcc_generated_files/library/rnwf02/rnwf_provision_service.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o: mcc_generated_files/system/src/protected_io.S  .generated_files/flags/default/6b0e7ecb8938b5f2c47d1e2fa5c43a43eb7a434c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o 
	${MP_CC} -c $(MP_EXTRA_AS_PRE) -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x assembler-with-cpp -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1   -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o -o ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o  mcc_generated_files/system/src/protected_io.S 
	
else
${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o: mcc_generated_files/system/src/protected_io.S  .generated_files/flags/default/c0942e9ff16ce37bf9a7246b69babf04f40b160d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o 
	${MP_CC} -c $(MP_EXTRA_AS_PRE) -mcpu=$(MP_PROCESSOR_OPTION)  -x assembler-with-cpp -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem -Wa,--defsym=__MPLAB_BUILD=1   -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o -o ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o  mcc_generated_files/system/src/protected_io.S 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/rnwf02_tcp_client.X.${IMAGE_TYPE}.hex"
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
