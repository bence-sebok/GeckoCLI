################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp_stk_buttons.c \
../BSP/bsp_stk_leds.c 

OBJS += \
./BSP/bsp_stk_buttons.o \
./BSP/bsp_stk_leds.o 

C_DEPS += \
./BSP/bsp_stk_buttons.d \
./BSP/bsp_stk_leds.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/bsp_stk_buttons.o: ../BSP/bsp_stk_buttons.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DGCC_ARMCM3=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/Users/sebokbence/SimplicityStudio/v4_workspace_2/GeckoCLI/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//app/mcu_example/EFM32GG_STK3700/freertos_blink" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/common/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ezradiodrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/gpiointerrupt/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/sleep/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/bsp" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//util/third_party/freertos/Source/include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//util/third_party/freertos/Demo/Common/include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"BSP/bsp_stk_buttons.d" -MT"BSP/bsp_stk_buttons.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp_stk_leds.o: ../BSP/bsp_stk_leds.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DGCC_ARMCM3=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DDEBUG=1' -I"C:/Users/sebokbence/SimplicityStudio/v4_workspace_2/GeckoCLI/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//app/mcu_example/EFM32GG_STK3700/freertos_blink" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/common/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ezradiodrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/config" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/gpiointerrupt/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/sleep/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/inc" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/bsp" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//util/third_party/freertos/Source/include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//util/third_party/freertos/Demo/Common/include" -I"F:/dev/Simplicity/developer/sdks/gecko_sdk_suite/v1.1//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"BSP/bsp_stk_leds.d" -MT"BSP/bsp_stk_leds.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


