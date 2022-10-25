################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.c 

OBJS += \
./gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.o 

C_DEPS += \
./gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.o: ../gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.c gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFR32BG13P632F512GM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CLIENT=1' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\config" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\autogen" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\app\common\util\app_assert" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\app\common\util\app_log" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\common\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\protocol\bluetooth\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\hardware\board\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\bootloader" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\bootloader\api" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\CMSIS\Include" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\device_init\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\emdrv\dmadrv\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\middleware\glib\dmd" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\middleware\glib" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\emdrv\common\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\emlib\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\middleware\glib\glib" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\driver\i2cspm\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\iostream\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\hardware\driver\memlcd\src\ls013b7dh03" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\mbedtls\include" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\sl_component\sl_mbedtls_support\config" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\mbedtls\library" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\sl_component\sl_alt\include" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\sl_component\sl_mbedtls_support\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\hardware\driver\memlcd\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\hardware\driver\memlcd\inc\memlcd_usart" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\mpu\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\hardware\driver\mx25_flash_shutdown\inc\sl_mx25_flash_shutdown_usart" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\app\bluetooth\common\ota_dfu" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\power_manager\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\sl_component\sl_psa_driver\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\common" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\protocol\ble" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\protocol\zwave" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\plugin\pa-conversions" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\plugin\pa-conversions\efr32xg1x" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\radio\rail_lib\plugin\rail_util_pti" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\silicon_labs\silabs_core\memory_manager" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\common\toolchain\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\system\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\sleeptimer\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\util\third_party\crypto\sl_component\sl_protocol_crypto\src" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\emdrv\spidrv\inc" -I"C:\Users\anshu\SimplicityStudio\v5_workspace\ecen5823-assignment7-Anshul-99\gecko_sdk_3.2.3\platform\service\udelay\inc" -O0 -Wall -Wextra -fno-builtin -fomit-frame-pointer -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_3.2.3/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


