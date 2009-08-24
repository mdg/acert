CC = gcc

all : sample_acert

acert.o : acert.c acert.h
	$(CC) -c acert.c

sample.o : sample.c acert.h
	$(CC) -c sample.c

sample_acert : acert.o sample.o
	$(CC) -o sample_acert acert.o sample.o

