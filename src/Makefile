CC=gcc
CFLAGS=-I.
SOURCES= rbm.c mnist_parse.c twister.c
DEPS= mnist_parse.h rbm.h
OBJECTS=rbm.o mnist_parse.o
EXECUTABLE=rbm

all:
	$(CC) -o $(EXECUTABLE) $(SOURCES)

run:
	./rbm

clean:
	rm $(EXECUTABLE)
