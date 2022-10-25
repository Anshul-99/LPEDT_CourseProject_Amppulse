################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_aes.c \
../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_ecp.c \
../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c \
../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_sha.c 

OBJS += \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_aes.o \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_ecp.o \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_sha.o 

C_DEPS += \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_aes.d \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_ecp.d \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_cmac.d \
./.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_sha.d 


# Each subdirectory must supply rules for building sources it contributes
.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_aes.o: ../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_aes.c .trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_aes.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_ecp.o: ../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_ecp.c .trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/crypto_ecp.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o: ../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c .trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_cmac.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_sha.o: ../.trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_sha.c .trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -O2 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF".trash/gecko_sdk_3.2.1/util/third_party/crypto/sl_component/sl_mbedtls_support/src/mbedtls_sha.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


