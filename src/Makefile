CC=gcc
CFLAGS=-I.
SOURCES= rbm.c mnist_parse.c train.c
DEPS= mnist_parse.h rbm.h train.h
OBJECTS=rbm.o mnist_parse.o
EXECUTABLE=rbm

all:
	$(CC) -o $(EXECUTABLE) $(SOURCES) -lm

run:
	./rbm

clean:
	rm $(EXECUTABLE)
