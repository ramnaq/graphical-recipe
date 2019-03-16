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

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) tmp/$(OBJS) $(LDFLAGS)

main.o: teste.cpp
	$(CC) -c $(CCFLAGS) teste.cpp $(GTKLIB) -o tmp/main.o

clean:
	rm -f tmp/*.o $(TARGET)
