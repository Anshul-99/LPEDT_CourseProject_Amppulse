################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_assert.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_cmu.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_core.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_crypto.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_emu.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_gpio.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_i2c.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_letimer.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_msc.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_prs.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_rtcc.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_system.c \
../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_usart.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_assert.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_cmu.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_core.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_crypto.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_emu.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_gpio.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_i2c.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_letimer.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_msc.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_prs.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_rtcc.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_system.o \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_usart.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_assert.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_cmu.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_core.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_crypto.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_emu.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_gpio.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_i2c.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_letimer.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_msc.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_prs.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_rtcc.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_system.d \
./.trash/gecko_sdk_3.2.1/platform/emlib/src/em_usart.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/emlib/src/em_assert.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_assert.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_assert.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_cmu.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_cmu.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_cmu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_core.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_core.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_core.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_crypto.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_crypto.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_crypto.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_emu.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_emu.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_emu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_gpio.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_gpio.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_i2c.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_i2c.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_i2c.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_letimer.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_letimer.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_letimer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_msc.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_msc.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_msc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_prs.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_prs.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_prs.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_rtcc.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_rtcc.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_rtcc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_system.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_system.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_system.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/emlib/src/em_usart.o: ../.trash/gecko_sdk_3.2.1/platform/emlib/src/em_usart.c .trash/gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/emlib/src/em_usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


