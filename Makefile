# Задаем имя проекта, в результате получатся файлы test.hex test.bin
TARG=test
 
CC = avr-g++
OBJCOPY = avr-objcopy

SRCSDIR = src
 
# Задаем из каких файлов собирать проект, можно указать несколько файлов
SRCS = $(SRCSDIR)/GPIO.cpp $(SRCSDIR)/HD44780.cpp $(SRCSDIR)/AnalogToDigital.cpp $(SRCSDIR)/Timer16.cpp $(SRCSDIR)/Timer8_0.cpp $(SRCSDIR)/Timer8_2.cpp main.cpp

 
OBJS = $(SRCS:.c=.o)
 
# Задаем для какого микроконтроллера будем компилировать (atmega8)
MCU=atmega328p
 
# Флаги компилятора, при помощи F_CPU определяем частоту на которой будет работать контроллер,
CFLAGS = -mmcu=$(MCU) -Wall  -Os -Werror -lm  -mcall-prologues -DF_CPU=16000000UL -I./inc -std=c++11 -fno-threadsafe-statics
LDFLAGS = -mmcu=$(MCU)  -Wall  -Os  -Werror -DF_CPU=16000000UL -I./inc -std=c++11 -fno-threadsafe-statics

PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt
 
all: $(TARG)
 
$(TARG): $(OBJS)
	$(CC) $(LDFLAGS) $(PRINTF_LIB_FLOAT) -o $@.elf  $(OBJS) -lm
	$(OBJCOPY) -O binary -R .eeprom -R .nwram  $@.elf $@.bin
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram  $@.elf $@.hex
 
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $&lt;
 
clean:
	rm -f *.elf *.bin *.hex  $(OBJS) *.map
