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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ADC.o ${OBJECTDIR}/sigCmpx.o ${OBJECTDIR}/twiddleFactors.o ${OBJECTDIR}/newmain.o ${OBJECTDIR}/uatr2.o ${OBJECTDIR}/I2c.o ${OBJECTDIR}/_ext/1662749207/OpenI2C.o ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o ${OBJECTDIR}/_ext/1662749207/StartI2C.o ${OBJECTDIR}/_ext/1662749207/StopI2C.o ${OBJECTDIR}/_ext/1662749207/AckI2C.o ${OBJECTDIR}/_ext/1662749207/CloseI2C.o ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o ${OBJECTDIR}/_ext/1662749207/IdleI2C.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ADC.o.d ${OBJECTDIR}/sigCmpx.o.d ${OBJECTDIR}/twiddleFactors.o.d ${OBJECTDIR}/newmain.o.d ${OBJECTDIR}/uatr2.o.d ${OBJECTDIR}/I2c.o.d ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d ${OBJECTDIR}/_ext/1662749207/StartI2C.o.d ${OBJECTDIR}/_ext/1662749207/StopI2C.o.d ${OBJECTDIR}/_ext/1662749207/AckI2C.o.d ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ADC.o ${OBJECTDIR}/sigCmpx.o ${OBJECTDIR}/twiddleFactors.o ${OBJECTDIR}/newmain.o ${OBJECTDIR}/uatr2.o ${OBJECTDIR}/I2c.o ${OBJECTDIR}/_ext/1662749207/OpenI2C.o ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o ${OBJECTDIR}/_ext/1662749207/StartI2C.o ${OBJECTDIR}/_ext/1662749207/StopI2C.o ${OBJECTDIR}/_ext/1662749207/AckI2C.o ${OBJECTDIR}/_ext/1662749207/CloseI2C.o ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o ${OBJECTDIR}/_ext/1662749207/IdleI2C.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4011
MP_LINKER_FILE_OPTION=,--script="linkerscript.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ADC.o: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o.ok ${OBJECTDIR}/ADC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ADC.o.d" -o ${OBJECTDIR}/ADC.o ADC.c    
	
${OBJECTDIR}/sigCmpx.o: sigCmpx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sigCmpx.o.d 
	@${RM} ${OBJECTDIR}/sigCmpx.o.ok ${OBJECTDIR}/sigCmpx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/sigCmpx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sigCmpx.o.d" -o ${OBJECTDIR}/sigCmpx.o sigCmpx.c    
	
${OBJECTDIR}/twiddleFactors.o: twiddleFactors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/twiddleFactors.o.d 
	@${RM} ${OBJECTDIR}/twiddleFactors.o.ok ${OBJECTDIR}/twiddleFactors.o.err 
	@${FIXDEPS} "${OBJECTDIR}/twiddleFactors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/twiddleFactors.o.d" -o ${OBJECTDIR}/twiddleFactors.o twiddleFactors.c    
	
${OBJECTDIR}/newmain.o: newmain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o.ok ${OBJECTDIR}/newmain.o.err 
	@${FIXDEPS} "${OBJECTDIR}/newmain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/newmain.o.d" -o ${OBJECTDIR}/newmain.o newmain.c    
	
${OBJECTDIR}/uatr2.o: uatr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uatr2.o.d 
	@${RM} ${OBJECTDIR}/uatr2.o.ok ${OBJECTDIR}/uatr2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/uatr2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uatr2.o.d" -o ${OBJECTDIR}/uatr2.o uatr2.c    
	
${OBJECTDIR}/I2c.o: I2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/I2c.o.d 
	@${RM} ${OBJECTDIR}/I2c.o.ok ${OBJECTDIR}/I2c.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2c.o.d" -o ${OBJECTDIR}/I2c.o I2c.c    
	
${OBJECTDIR}/_ext/1662749207/OpenI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/OpenI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.ok ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/OpenI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/OpenI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlavegetsI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.ok ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlavegetsI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveputsI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.ok ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveputsI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveReadI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.ok ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveReadI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/StartI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StartI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StartI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StartI2C.o.ok ${OBJECTDIR}/_ext/1662749207/StartI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/StartI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/StartI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/StartI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StartI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/StopI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StopI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StopI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StopI2C.o.ok ${OBJECTDIR}/_ext/1662749207/StopI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/StopI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/StopI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/StopI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StopI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/AckI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/AckI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/AckI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/AckI2C.o.ok ${OBJECTDIR}/_ext/1662749207/AckI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/AckI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/AckI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/AckI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/AckI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/CloseI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/CloseI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.ok ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/CloseI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/CloseI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/ConfigIntI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.ok ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/ConfigIntI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/DataRdyI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.ok ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/DataRdyI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/IdleI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/IdleI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.ok ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/IdleI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/IdleI2C.c"    
	
else
${OBJECTDIR}/ADC.o: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o.ok ${OBJECTDIR}/ADC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ADC.o.d" -o ${OBJECTDIR}/ADC.o ADC.c    
	
${OBJECTDIR}/sigCmpx.o: sigCmpx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sigCmpx.o.d 
	@${RM} ${OBJECTDIR}/sigCmpx.o.ok ${OBJECTDIR}/sigCmpx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/sigCmpx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sigCmpx.o.d" -o ${OBJECTDIR}/sigCmpx.o sigCmpx.c    
	
${OBJECTDIR}/twiddleFactors.o: twiddleFactors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/twiddleFactors.o.d 
	@${RM} ${OBJECTDIR}/twiddleFactors.o.ok ${OBJECTDIR}/twiddleFactors.o.err 
	@${FIXDEPS} "${OBJECTDIR}/twiddleFactors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/twiddleFactors.o.d" -o ${OBJECTDIR}/twiddleFactors.o twiddleFactors.c    
	
${OBJECTDIR}/newmain.o: newmain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o.ok ${OBJECTDIR}/newmain.o.err 
	@${FIXDEPS} "${OBJECTDIR}/newmain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/newmain.o.d" -o ${OBJECTDIR}/newmain.o newmain.c    
	
${OBJECTDIR}/uatr2.o: uatr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uatr2.o.d 
	@${RM} ${OBJECTDIR}/uatr2.o.ok ${OBJECTDIR}/uatr2.o.err 
	@${FIXDEPS} "${OBJECTDIR}/uatr2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/uatr2.o.d" -o ${OBJECTDIR}/uatr2.o uatr2.c    
	
${OBJECTDIR}/I2c.o: I2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/I2c.o.d 
	@${RM} ${OBJECTDIR}/I2c.o.ok ${OBJECTDIR}/I2c.o.err 
	@${FIXDEPS} "${OBJECTDIR}/I2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/I2c.o.d" -o ${OBJECTDIR}/I2c.o I2c.c    
	
${OBJECTDIR}/_ext/1662749207/OpenI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/OpenI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.ok ${OBJECTDIR}/_ext/1662749207/OpenI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/OpenI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/OpenI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/OpenI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlavegetsI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.ok ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/SlavegetsI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlavegetsI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveputsI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.ok ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/SlaveputsI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveputsI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveReadI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.ok ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/SlaveReadI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/SlaveReadI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/StartI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StartI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StartI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StartI2C.o.ok ${OBJECTDIR}/_ext/1662749207/StartI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/StartI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/StartI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/StartI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StartI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/StopI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StopI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StopI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/StopI2C.o.ok ${OBJECTDIR}/_ext/1662749207/StopI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/StopI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/StopI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/StopI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/StopI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/AckI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/AckI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/AckI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/AckI2C.o.ok ${OBJECTDIR}/_ext/1662749207/AckI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/AckI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/AckI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/AckI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/AckI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/CloseI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/CloseI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.ok ${OBJECTDIR}/_ext/1662749207/CloseI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/CloseI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/CloseI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/CloseI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/ConfigIntI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.ok ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/ConfigIntI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/ConfigIntI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/DataRdyI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.ok ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/DataRdyI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/DataRdyI2C.c"    
	
${OBJECTDIR}/_ext/1662749207/IdleI2C.o: ../../Program\ Files/Microchip/MPLABX/MPLAB\ C30/src/peripheral_30F_24H_33F/src/pmc/i2c/IdleI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1662749207 
	@${RM} ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.ok ${OBJECTDIR}/_ext/1662749207/IdleI2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1662749207/IdleI2C.o.d" -o ${OBJECTDIR}/_ext/1662749207/IdleI2C.o "../../Program Files/Microchip/MPLABX/MPLAB C30/src/peripheral_30F_24H_33F/src/pmc/i2c/IdleI2C.c"    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    linkerscript.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG  -o dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   linkerscript.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/fftdevtry.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
