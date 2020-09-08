CFLAGS = -I./include -O2

84link : main.o file.o
	gcc -o 84link main.o file.o

main.o : ./src/main.c ./include/file.h
	gcc -c ./src/main.c $(CFLAGS)

file.o : ./src/file.c ./include/file.h
	gcc -c ./src/file.c $(CFLAGS)