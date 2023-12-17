CXX=gcc
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET = main

OBJS = fileHandler.o \
		set.o \
		get.o \
		main.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

set.o: fileHandler.h
main.o: set.h \
		get.h

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

.c.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
