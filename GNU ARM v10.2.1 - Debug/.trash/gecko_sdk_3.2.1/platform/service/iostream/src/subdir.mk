################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream.c \
../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_retarget_stdio.c \
../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_stdlib_config.c \
../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_uart.c \
../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_usart.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream.o \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_retarget_stdio.o \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_stdlib_config.o \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_uart.o \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_usart.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream.d \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_retarget_stdio.d \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_stdlib_config.d \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_uart.d \
./.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_usart.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream.o: ../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream.c .trash/gecko_sdk_3.2.1/platform/service/iostream/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_retarget_stdio.o: ../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_retarget_stdio.c .trash/gecko_sdk_3.2.1/platform/service/iostream/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_retarget_stdio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_stdlib_config.o: ../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_stdlib_config.c .trash/gecko_sdk_3.2.1/platform/service/iostream/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_stdlib_config.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_uart.o: ../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_uart.c .trash/gecko_sdk_3.2.1/platform/service/iostream/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_uart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_usart.o: ../.trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_usart.c .trash/gecko_sdk_3.2.1/platform/service/iostream/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/platform/service/iostream/src/sl_iostream_usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


