################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface.c \
../.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface_storage.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface.o \
./.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface_storage.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface.d \
./.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface_storage.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface.o: ../.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface.c .trash/gecko_sdk_3.2.1/platform/bootloader/api/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface_storage.o: ../.trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface_storage.c .trash/gecko_sdk_3.2.1/platform/bootloader/api/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/bootloader/api/btl_interface_storage.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


