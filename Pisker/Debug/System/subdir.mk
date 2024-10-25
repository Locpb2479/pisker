################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/sys_btn.c \
../System/sys_manager.c \
../System/sys_pc_control.c \
../System/sys_sound.c \
../System/system_digital_clock.c \
../System/system_display.c \
../System/system_set_alarm.c \
../System/system_set_time.c 

OBJS += \
./System/sys_btn.o \
./System/sys_manager.o \
./System/sys_pc_control.o \
./System/sys_sound.o \
./System/system_digital_clock.o \
./System/system_display.o \
./System/system_set_alarm.o \
./System/system_set_time.o 

C_DEPS += \
./System/sys_btn.d \
./System/sys_manager.d \
./System/sys_pc_control.d \
./System/sys_sound.d \
./System/system_digital_clock.d \
./System/system_display.d \
./System/system_set_alarm.d \
./System/system_set_time.d 


# Each subdirectory must supply rules for building sources it contributes
System/%.o System/%.su System/%.cyclo: ../System/%.c System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/BSP" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Driver" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/System" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middlewares" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middleware" -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System

clean-System:
	-$(RM) ./System/sys_btn.cyclo ./System/sys_btn.d ./System/sys_btn.o ./System/sys_btn.su ./System/sys_manager.cyclo ./System/sys_manager.d ./System/sys_manager.o ./System/sys_manager.su ./System/sys_pc_control.cyclo ./System/sys_pc_control.d ./System/sys_pc_control.o ./System/sys_pc_control.su ./System/sys_sound.cyclo ./System/sys_sound.d ./System/sys_sound.o ./System/sys_sound.su ./System/system_digital_clock.cyclo ./System/system_digital_clock.d ./System/system_digital_clock.o ./System/system_digital_clock.su ./System/system_display.cyclo ./System/system_display.d ./System/system_display.o ./System/system_display.su ./System/system_set_alarm.cyclo ./System/system_set_alarm.d ./System/system_set_alarm.o ./System/system_set_alarm.su ./System/system_set_time.cyclo ./System/system_set_time.d ./System/system_set_time.o ./System/system_set_time.su

.PHONY: clean-System

