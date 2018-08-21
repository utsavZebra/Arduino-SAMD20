################################################################################
# Automatically-generated file. Do not edit!
################################################################################
include .local/config.mk

USER_OBJS :=

LIBS := 
PROJ := 

CMSIS_DIR := $(SDK_PATH)/devicePack/arm/cmsis/5.0.1/CMSIS/Include
ATMEL_DFP := $(SDK_PATH)/devicePack/atmel/SAMD20_DFP/1.2.91/samd20/include
TOOLCHAIN_PATH := $(SDK_PATH)/toolchain/bin

PROJ_DIR = $(PWD)
BUILD_DIR := build

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
QUOTE := 
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
$(PROJ_DIR)/ \
$(PROJ_DIR)/include/ \
$(PROJ_DIR)/include/core/ \
$(PROJ_DIR)/include/core/avr/ \
$(PROJ_DIR)/include/core/samd20/ \
$(PROJ_DIR)/include/core/samd20/include/ \
$(PROJ_DIR)/include/core/samd20/include/component/ \
$(PROJ_DIR)/include/core/samd20/include/instance/ \
$(PROJ_DIR)/include/core/samd20/include/pio/ \
$(PROJ_DIR)/include/libraries/ \
$(PROJ_DIR)/include/libraries/spi/ \
$(PROJ_DIR)/include/variants/ \
$(PROJ_DIR)/src/ \
$(PROJ_DIR)/src/core/ \
$(PROJ_DIR)/src/core/avr/ \
$(PROJ_DIR)/src/core/PreprocessingAssembly/ \
$(PROJ_DIR)/src/libraries/ \
$(PROJ_DIR)/src/libraries/spi/ \
$(PROJ_DIR)/src/variants/ \


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
$(PROJ_DIR)/src/core/abi.cpp \
$(PROJ_DIR)/src/core/avr/dtostrf.c \
$(PROJ_DIR)/src/core/clocks.c \
$(PROJ_DIR)/src/core/cortex_handlers.c \
$(PROJ_DIR)/src/core/delay.c \
$(PROJ_DIR)/src/core/EEPROM.cpp \
$(PROJ_DIR)/src/core/hooks.c \
$(PROJ_DIR)/src/core/IPAddress.cpp \
$(PROJ_DIR)/src/core/itoa.c \
$(PROJ_DIR)/src/core/main.cpp \
$(PROJ_DIR)/src/core/micros.c \
$(PROJ_DIR)/src/core/new.cpp \
$(PROJ_DIR)/src/core/NVM.c \
$(PROJ_DIR)/src/core/Print.cpp \
$(PROJ_DIR)/src/core/pulse.c \
$(PROJ_DIR)/src/core/PWM.cpp \
$(PROJ_DIR)/src/core/Reset.cpp \
$(PROJ_DIR)/src/core/RTC.c \
$(PROJ_DIR)/src/core/SERCOM.cpp \
$(PROJ_DIR)/src/core/sleep.c \
$(PROJ_DIR)/src/core/startup.c \
$(PROJ_DIR)/src/core/Stream.cpp \
$(PROJ_DIR)/src/core/TimerCounter.cpp \
$(PROJ_DIR)/src/core/Tone.cpp \
$(PROJ_DIR)/src/core/Uart.cpp \
$(PROJ_DIR)/src/core/WDT.c \
$(PROJ_DIR)/src/core/WInterrupts.c \
$(PROJ_DIR)/src/core/wiring_analog.c \
$(PROJ_DIR)/src/core/wiring_digital.c \
$(PROJ_DIR)/src/core/wiring_private.c \
$(PROJ_DIR)/src/core/wiring_shift.c \
$(PROJ_DIR)/src/core/WMath.cpp \
$(PROJ_DIR)/src/core/WString.cpp \
$(PROJ_DIR)/src/libraries/spi/SPI.cpp \
$(PROJ_DIR)/src/variants/variant.cpp


PREPROCESSING_SRCS +=  \
$(PROJ_DIR)/src/core/PreprocessingAssembly/pulse_asm.S \
$(PROJ_DIR)/src/core/pulse_asm.S


ASM_SRCS += 


OBJS +=  \
$(BUILD_DIR)/abi.o \
$(BUILD_DIR)/dtostrf.o \
$(BUILD_DIR)/clocks.o \
$(BUILD_DIR)/cortex_handlers.o \
$(BUILD_DIR)/delay.o \
$(BUILD_DIR)/EEPROM.o \
$(BUILD_DIR)/hooks.o \
$(BUILD_DIR)/IPAddress.o \
$(BUILD_DIR)/itoa.o \
$(BUILD_DIR)/main.o \
$(BUILD_DIR)/micros.o \
$(BUILD_DIR)/new.o \
$(BUILD_DIR)/NVM.o \
$(BUILD_DIR)/pulse_asm.o \
$(BUILD_DIR)/Print.o \
$(BUILD_DIR)/pulse.o \
$(BUILD_DIR)/pulse_asm.o \
$(BUILD_DIR)/PWM.o \
$(BUILD_DIR)/Reset.o \
$(BUILD_DIR)/RTC.o \
$(BUILD_DIR)/SERCOM.o \
$(BUILD_DIR)/sleep.o \
$(BUILD_DIR)/startup.o \
$(BUILD_DIR)/Stream.o \
$(BUILD_DIR)/TimerCounter.o \
$(BUILD_DIR)/Tone.o \
$(BUILD_DIR)/Uart.o \
$(BUILD_DIR)/WDT.o \
$(BUILD_DIR)/WInterrupts.o \
$(BUILD_DIR)/wiring_analog.o \
$(BUILD_DIR)/wiring_digital.o \
$(BUILD_DIR)/wiring_private.o \
$(BUILD_DIR)/wiring_shift.o \
$(BUILD_DIR)/WMath.o \
$(BUILD_DIR)/WString.o \
$(BUILD_DIR)/SPI.o \
$(BUILD_DIR)/variant.o

OBJS_AS_ARGS +=  \
$(BUILD_DIR)/abi.o \
$(BUILD_DIR)/dtostrf.o \
$(BUILD_DIR)/clocks.o \
$(BUILD_DIR)/cortex_handlers.o \
$(BUILD_DIR)/delay.o \
$(BUILD_DIR)/EEPROM.o \
$(BUILD_DIR)/hooks.o \
$(BUILD_DIR)/IPAddress.o \
$(BUILD_DIR)/itoa.o \
$(BUILD_DIR)/main.o \
$(BUILD_DIR)/micros.o \
$(BUILD_DIR)/new.o \
$(BUILD_DIR)/NVM.o \
$(BUILD_DIR)/pulse_asm.o \
$(BUILD_DIR)/Print.o \
$(BUILD_DIR)/pulse.o \
$(BUILD_DIR)/pulse_asm.o \
$(BUILD_DIR)/PWM.o \
$(BUILD_DIR)/Reset.o \
$(BUILD_DIR)/RTC.o \
$(BUILD_DIR)/SERCOM.o \
$(BUILD_DIR)/sleep.o \
$(BUILD_DIR)/startup.o \
$(BUILD_DIR)/Stream.o \
$(BUILD_DIR)/TimerCounter.o \
$(BUILD_DIR)/Tone.o \
$(BUILD_DIR)/Uart.o \
$(BUILD_DIR)/WDT.o \
$(BUILD_DIR)/WInterrupts.o \
$(BUILD_DIR)/wiring_analog.o \
$(BUILD_DIR)/wiring_digital.o \
$(BUILD_DIR)/wiring_private.o \
$(BUILD_DIR)/wiring_shift.o \
$(BUILD_DIR)/WMath.o \
$(BUILD_DIR)/WString.o \
$(BUILD_DIR)/SPI.o \
$(BUILD_DIR)/variant.o

C_DEPS +=  \
$(BUILD_DIR)/abi.d \
$(BUILD_DIR)/dtostrf.d \
$(BUILD_DIR)/clocks.d \
$(BUILD_DIR)/cortex_handlers.d \
$(BUILD_DIR)/delay.d \
$(BUILD_DIR)/EEPROM.d \
$(BUILD_DIR)/hooks.d \
$(BUILD_DIR)/IPAddress.d \
$(BUILD_DIR)/itoa.d \
$(BUILD_DIR)/main.d \
$(BUILD_DIR)/micros.d \
$(BUILD_DIR)/new.d \
$(BUILD_DIR)/NVM.d \
$(BUILD_DIR)/pulse_asm.d \
$(BUILD_DIR)/Print.d \
$(BUILD_DIR)/pulse.d \
$(BUILD_DIR)/pulse_asm.d \
$(BUILD_DIR)/PWM.d \
$(BUILD_DIR)/Reset.d \
$(BUILD_DIR)/RTC.d \
$(BUILD_DIR)/SERCOM.d \
$(BUILD_DIR)/sleep.d \
$(BUILD_DIR)/startup.d \
$(BUILD_DIR)/Stream.d \
$(BUILD_DIR)/TimerCounter.d \
$(BUILD_DIR)/Tone.d \
$(BUILD_DIR)/Uart.d \
$(BUILD_DIR)/WDT.d \
$(BUILD_DIR)/WInterrupts.d \
$(BUILD_DIR)/wiring_analog.d \
$(BUILD_DIR)/wiring_digital.d \
$(BUILD_DIR)/wiring_private.d \
$(BUILD_DIR)/wiring_shift.d \
$(BUILD_DIR)/WMath.d \
$(BUILD_DIR)/WString.d \
$(BUILD_DIR)/SPI.d \
$(BUILD_DIR)/variant.d

C_DEPS_AS_ARGS +=  \
$(BUILD_DIR)/abi.d \
$(BUILD_DIR)/dtostrf.d \
$(BUILD_DIR)/clocks.d \
$(BUILD_DIR)/cortex_handlers.d \
$(BUILD_DIR)/delay.d \
$(BUILD_DIR)/EEPROM.d \
$(BUILD_DIR)/hooks.d \
$(BUILD_DIR)/IPAddress.d \
$(BUILD_DIR)/itoa.d \
$(BUILD_DIR)/main.d \
$(BUILD_DIR)/micros.d \
$(BUILD_DIR)/new.d \
$(BUILD_DIR)/NVM.d \
$(BUILD_DIR)/pulse_asm.d \
$(BUILD_DIR)/Print.d \
$(BUILD_DIR)/pulse.d \
$(BUILD_DIR)/pulse_asm.d \
$(BUILD_DIR)/PWM.d \
$(BUILD_DIR)/Reset.d \
$(BUILD_DIR)/RTC.d \
$(BUILD_DIR)/SERCOM.d \
$(BUILD_DIR)/sleep.d \
$(BUILD_DIR)/startup.d \
$(BUILD_DIR)/Stream.d \
$(BUILD_DIR)/TimerCounter.d \
$(BUILD_DIR)/Tone.d \
$(BUILD_DIR)/Uart.d \
$(BUILD_DIR)/WDT.d \
$(BUILD_DIR)/WInterrupts.d \
$(BUILD_DIR)/wiring_analog.d \
$(BUILD_DIR)/wiring_digital.d \
$(BUILD_DIR)/wiring_private.d \
$(BUILD_DIR)/wiring_shift.d \
$(BUILD_DIR)/WMath.d \
$(BUILD_DIR)/WString.d \
$(BUILD_DIR)/SPI.d \
$(BUILD_DIR)/variant.d

OUTPUT_FILE_PATH +=$(BUILD_DIR)/libArduinoCore.a

OUTPUT_FILE_PATH_AS_ARGS +=$(BUILD_DIR)/libArduinoCore.a

ADDITIONAL_DEPENDENCIES:=

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler







































































$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/%.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -x c -mthumb -D__SAMD20E18__ -DDEBUG -DARDUINO_SAMD_E -DARDUINO_ARCH_SAMD -DUSB_VID=0x2341 -DUSB_PID=0x804f -DUSB_PRODUCT="Arduino MKRZero" -DUSB_MANUFACTURER="Arduino LLC" -DSAMD_SERIES -DSAMD20  -I$(CMSIS_DIR) -I$(ATMEL_DFP) -I$(PROJ_DIR)/include/core -I$(PROJ_DIR)/include/core/samd20 -I$(PROJ_DIR)/include/core/samd20/include -I$(PROJ_DIR)/include/core/samd20/include/component -I$(PROJ_DIR)/include/core/samd20/include/instance -I$(PROJ_DIR)/include/core/samd20/include/pio -I$(PROJ_DIR)/include/libraries/spi -I$(PROJ_DIR)/include/variants  -O1 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o)   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/%.cpp
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-g++ -mthumb -D__SAMD20E18__ -DDEBUG -DARDUINO_SAMD_E -DARDUINO_ARCH_SAMD -DUSB_VID=0x2341 -DUSB_PID=0x804f -DUSB_PRODUCT="Arduino MKRZero" -DUSB_MANUFACTURER="Arduino LLC" -DSAMD_SERIES -DSAMD20  -I$(CMSIS_DIR) -I$(ATMEL_DFP) -I$(PROJ_DIR)/include/variants -I$(PROJ_DIR)/include/core -I$(PROJ_DIR)/include/core/samd20 -I$(PROJ_DIR)/include/core/samd20/include -I$(PROJ_DIR)/include/core/samd20/include/component -I$(PROJ_DIR)/include/core/samd20/include/instance -I$(PROJ_DIR)/include/core/samd20/include/pio -I$(PROJ_DIR)/include/libraries/spi  -O1 -ffunction-sections -fno-rtti -fno-exceptions -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o)   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/avr/%.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -x c -mthumb -D__SAMD20E18__ -DDEBUG -DARDUINO_SAMD_E -DARDUINO_ARCH_SAMD -DUSB_VID=0x2341 -DUSB_PID=0x804f -DUSB_PRODUCT="Arduino MKRZero" -DUSB_MANUFACTURER="Arduino LLC" -DSAMD_SERIES -DSAMD20  -I$(CMSIS_DIR) -I$(ATMEL_DFP) -I$(PROJ_DIR)/include/core -I$(PROJ_DIR)/include/core/samd20 -I$(PROJ_DIR)/include/core/samd20/include -I$(PROJ_DIR)/include/core/samd20/include/component -I$(PROJ_DIR)/include/core/samd20/include/instance -I$(PROJ_DIR)/include/core/samd20/include/pio -I$(PROJ_DIR)/include/libraries/spi -I$(PROJ_DIR)/include/variants  -O1 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o)   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/libraries/spi/%.cpp
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-g++ -mthumb -D__SAMD20E18__ -DDEBUG -DARDUINO_SAMD_E -DARDUINO_ARCH_SAMD -DUSB_VID=0x2341 -DUSB_PID=0x804f -DUSB_PRODUCT="Arduino MKRZero" -DUSB_MANUFACTURER="Arduino LLC" -DSAMD_SERIES -DSAMD20  -I$(CMSIS_DIR) -I$(ATMEL_DFP) -I$(PROJ_DIR)/include/variants -I$(PROJ_DIR)/include/core -I$(PROJ_DIR)/include/core/samd20 -I$(PROJ_DIR)/include/core/samd20/include -I$(PROJ_DIR)/include/core/samd20/include/component -I$(PROJ_DIR)/include/core/samd20/include/instance -I$(PROJ_DIR)/include/core/samd20/include/pio -I$(PROJ_DIR)/include/libraries/spi  -O1 -ffunction-sections -fno-rtti -fno-exceptions -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o)   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/variants/%.cpp
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-g++ -mthumb -D__SAMD20E18__ -DDEBUG -DARDUINO_SAMD_E -DARDUINO_ARCH_SAMD -DUSB_VID=0x2341 -DUSB_PID=0x804f -DUSB_PRODUCT="Arduino MKRZero" -DUSB_MANUFACTURER="Arduino LLC" -DSAMD_SERIES -DSAMD20  -I$(CMSIS_DIR) -I$(ATMEL_DFP) -I$(PROJ_DIR)/include/variants -I$(PROJ_DIR)/include/core -I$(PROJ_DIR)/include/core/samd20 -I$(PROJ_DIR)/include/core/samd20/include -I$(PROJ_DIR)/include/core/samd20/include/component -I$(PROJ_DIR)/include/core/samd20/include/instance -I$(PROJ_DIR)/include/core/samd20/include/pio -I$(PROJ_DIR)/include/libraries/spi  -O1 -ffunction-sections -fno-rtti -fno-exceptions -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o)   -o $@ $< 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/PreprocessingAssembly/%.S
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/PreprocessingAssembly/%.x
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o:: $(PROJ_DIR)/src/core/PreprocessingAssembly/%.X
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o:: $(PROJ_DIR)/src/core/PreprocessingAssembly/%.sx
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/%.S
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/%.x
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/%.X
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	

$(BUILD_DIR)/%.o: $(PROJ_DIR)/src/core/%.sx
	@echo Building file: $<
	@echo Invoking: ARM/GNU Preprocessing Assembler : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-gcc -mthumb -x assembler-with-cpp -c -mcpu=cortex-m0plus -I $(CMSIS_DIR) -I $(ATMEL_DFP)  -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -D__SAMD20E18__ -Wa,-g   -o $@ $< 
	@echo Finished building: $<
	



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 
directories: 
	mkdir build

# All Target
all: directories $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)


$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Archiver : 6.3.1
	$(TOOLCHAIN_PATH)/arm-none-eabi-ar -r -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) 
	@echo Finished building target: $@
	
	




# Other Targets
clean:
	rm -rf build
	