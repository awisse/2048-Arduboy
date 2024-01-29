TARGET := Desktop
VPATH = ../2048-Arduboy:
CPPFLAGS := -std=c++14 -D_REENTRANT -I/usr/include/SDL2 
LDLIBS := -lSDL2 

all: $(TARGET)

$(TARGET) : EEPROM.o test.o

EEPROM.o : EEPROM.cpp EEPROM.h 
	g++ -o $@ $<

test.o : test.cpp test.h Platform.h
	g++ -o $@ $<

.PHONY: clean
clean:
	@$(RM) $(TARGET)
	@$(RM) EEPROM.o test.o
