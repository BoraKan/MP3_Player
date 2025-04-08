################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../functions.c \
../main.c \
../mp3_player.c 

C_DEPS += \
./functions.d \
./main.d \
./mp3_player.d 

OBJS += \
./functions.o \
./main.o \
./mp3_player.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/opt/homebrew/Cellar/harfbuzz/10.1.0/include/harfbuzz -I/opt/homebrew/opt/freetype/include/freetype2 -I/opt/homebrew/opt/libpng/include/libpng16 -I/opt/homebrew/Cellar/graphite2/1.3.14/include -I/opt/homebrew/Cellar/gtk+3/3.24.43/include/gtk-3.0 -I/opt/homebrew/Cellar/glib/2.82.4/include/glib-2.0 -I/opt/homebrew/Cellar/glib/2.82.4/lib/glib-2.0/include -I/opt/homebrew/Cellar/pango/1.55.5/include/pango-1.0 -I/opt/homebrew/Cellar/atk/2.54.0/include/atk-1.0 -I/opt/homebrew/Cellar/cairo/1.18.2/include/cairo -I/opt/homebrew/Cellar/gdk-pixbuf/2.42.12/include/gdk-pixbuf-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./functions.d ./functions.o ./main.d ./main.o ./mp3_player.d ./mp3_player.o

.PHONY: clean--2e-

