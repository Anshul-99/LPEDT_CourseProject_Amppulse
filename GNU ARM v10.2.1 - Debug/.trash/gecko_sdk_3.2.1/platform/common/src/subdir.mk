################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/common/src/sl_slist.c \
../.trash/gecko_sdk_3.2.1/platform/common/src/sl_status.c \
../.trash/gecko_sdk_3.2.1/platform/common/src/sl_string.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/common/src/sl_slist.o \
./.trash/gecko_sdk_3.2.1/platform/common/src/sl_status.o \
./.trash/gecko_sdk_3.2.1/platform/common/src/sl_string.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/common/src/sl_slist.d \
./.trash/gecko_sdk_3.2.1/platform/common/src/sl_status.d \
./.trash/gecko_sdk_3.2.1/platform/common/src/sl_string.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/common/src/sl_slist.o: ../.trash/gecko_sdk_3.2.1/platform/common/src/sl_slist.c .trash/gecko_sdk_3.2.1/platform/common/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/common/src/sl_slist.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/common/src/sl_status.o: ../.trash/gecko_sdk_3.2.1/platform/common/src/sl_status.c .trash/gecko_sdk_3.2.1/platform/common/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/common/src/sl_status.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/common/src/sl_string.o: ../.trash/gecko_sdk_3.2.1/platform/common/src/sl_string.c .trash/gecko_sdk_3.2.1/platform/common/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/common/src/sl_string.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


