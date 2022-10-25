################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o: ../.trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c .trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


