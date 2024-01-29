TARGET := ardusdl
VPATH = ../2048-Arduboy:
CPPFLAGS :=  -D_REENTRANT -I/usr/include/SDL2 
LDLIBS := -lSDL2 

all: $(TARGET)

$(TARGET) : $(TARGET).o EEPROM.o 
	$(CXX) -ggdb -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	@$(RM) $(TARGET)
	@$(RM) EEPROM.o
