################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.c 

S_UPPER_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay_armv6m_gcc.S 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.o \
./.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay_armv6m_gcc.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.o: ../.trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.c .trash/gecko_sdk_3.2.1/platform/service/udelay/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/udelay/src/%.o: ../.trash/gecko_sdk_3.2.1/platform/service/udelay/src/%.S .trash/gecko_sdk_3.2.1/platform/service/udelay/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -x assembler-with-cpp -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


