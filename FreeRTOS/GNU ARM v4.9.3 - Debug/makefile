################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include FreeRTOS/efm32gg/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include BSP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: GeckoCLI.axf

# Tool invocations
GeckoCLI.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "GeckoCLI.ld" -Xlinker --gc-sections -Xlinker -Map="GeckoCLI.map" --specs=nano.specs -o GeckoCLI.axf "./BSP/bsp_stk_buttons.o" "./BSP/bsp_stk_leds.o" "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./Drivers/retargetio.o" "./Drivers/retargetserial.o" "./Drivers/udelay.o" "./FreeRTOS/efm32gg/event_groups.o" "./FreeRTOS/efm32gg/heap_2.o" "./FreeRTOS/efm32gg/list.o" "./FreeRTOS/efm32gg/port_gcc.o" "./FreeRTOS/efm32gg/queue.o" "./FreeRTOS/efm32gg/tasks.o" "./FreeRTOS/efm32gg/timers.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_lcd.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./emlib/segmentlcd.o" "./src/gpio.o" "./src/main.o" "./src/message.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: GeckoCLI.hex'
	arm-none-eabi-objcopy -O ihex "GeckoCLI.axf" "GeckoCLI.hex"
	@echo ' '

	@echo 'Building bin file: GeckoCLI.bin'
	arm-none-eabi-objcopy -O binary "GeckoCLI.axf" "GeckoCLI.bin"
	@echo ' '

	@echo 'Building s37 file: GeckoCLI.s37'
	arm-none-eabi-objcopy -O srec "GeckoCLI.axf" "GeckoCLI.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "GeckoCLI.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) GeckoCLI.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
