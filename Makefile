# change application name here (executable output name)
TARGET=teste.exe

# compiler
CC=g++

# debug
DEBUG=-ggdb

# warnings
WARN=-Wall

CCFLAGS=$(DEBUG) $(WARN)

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=g++
LDFLAGS=$(GTKLIB) -rdynamic

OBJS=main.o c_handlers.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: src/control/%.cpp
	$(CC) -c $(CCFLAGS) $< $(GTKLIB) -o $@

clean:
	rm -f *.o $(TARGET)
