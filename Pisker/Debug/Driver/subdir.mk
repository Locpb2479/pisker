################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/drv_btn.c \
../Driver/drv_dfplayer.c \
../Driver/drv_matrix_led.c \
../Driver/drv_rtc.c \
../Driver/drv_uart_mn_rec_data.c \
../Driver/fft_handle.c \
../Driver/uart_respond_fsm.c 

OBJS += \
./Driver/drv_btn.o \
./Driver/drv_dfplayer.o \
./Driver/drv_matrix_led.o \
./Driver/drv_rtc.o \
./Driver/drv_uart_mn_rec_data.o \
./Driver/fft_handle.o \
./Driver/uart_respond_fsm.o 

C_DEPS += \
./Driver/drv_btn.d \
./Driver/drv_dfplayer.d \
./Driver/drv_matrix_led.d \
./Driver/drv_rtc.d \
./Driver/drv_uart_mn_rec_data.d \
./Driver/fft_handle.d \
./Driver/uart_respond_fsm.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/%.o Driver/%.su Driver/%.cyclo: ../Driver/%.c Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/BSP" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Driver" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/System" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middlewares" -I"D:/HK232/Thuc tap ngoai truon/ITR VN/Project/Pisker/Middleware" -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver

clean-Driver:
	-$(RM) ./Driver/drv_btn.cyclo ./Driver/drv_btn.d ./Driver/drv_btn.o ./Driver/drv_btn.su ./Driver/drv_dfplayer.cyclo ./Driver/drv_dfplayer.d ./Driver/drv_dfplayer.o ./Driver/drv_dfplayer.su ./Driver/drv_matrix_led.cyclo ./Driver/drv_matrix_led.d ./Driver/drv_matrix_led.o ./Driver/drv_matrix_led.su ./Driver/drv_rtc.cyclo ./Driver/drv_rtc.d ./Driver/drv_rtc.o ./Driver/drv_rtc.su ./Driver/drv_uart_mn_rec_data.cyclo ./Driver/drv_uart_mn_rec_data.d ./Driver/drv_uart_mn_rec_data.o ./Driver/drv_uart_mn_rec_data.su ./Driver/fft_handle.cyclo ./Driver/fft_handle.d ./Driver/fft_handle.o ./Driver/fft_handle.su ./Driver/uart_respond_fsm.cyclo ./Driver/uart_respond_fsm.d ./Driver/uart_respond_fsm.o ./Driver/uart_respond_fsm.su

.PHONY: clean-Driver

