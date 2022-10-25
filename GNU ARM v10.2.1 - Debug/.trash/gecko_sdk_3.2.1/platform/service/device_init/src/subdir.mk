################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s1.c \
../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s1.c \
../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s1.c \
../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s1.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s1.o \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s1.o \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s1.o \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s1.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s1.d \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s1.d \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s1.d \
./.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s1.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s1.o: ../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s1.c .trash/gecko_sdk_3.2.1/platform/service/device_init/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s1.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s1.o: ../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s1.c .trash/gecko_sdk_3.2.1/platform/service/device_init/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s1.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s1.o: ../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s1.c .trash/gecko_sdk_3.2.1/platform/service/device_init/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s1.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s1.o: ../.trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s1.c .trash/gecko_sdk_3.2.1/platform/service/device_init/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s1.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


