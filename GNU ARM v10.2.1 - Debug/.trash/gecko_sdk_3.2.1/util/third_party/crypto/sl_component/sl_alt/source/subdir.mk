################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_entropy.c \
../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_mbedtls.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_entropy.o \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_mbedtls.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_entropy.d \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_mbedtls.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_entropy.o: ../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_entropy.c .trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_entropy.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_mbedtls.o: ../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_mbedtls.c .trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_alt/source/sl_mbedtls.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


