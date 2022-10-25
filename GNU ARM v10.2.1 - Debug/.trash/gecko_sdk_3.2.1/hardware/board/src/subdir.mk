################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.c \
../.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_init.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.o \
./.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_init.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.d \
./.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_init.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.o: ../.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.c .trash/gecko_sdk_3.2.1/hardware/board/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_init.o: ../.trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_init.c .trash/gecko_sdk_3.2.1/hardware/board/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/hardware/board/src/sl_board_init.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


