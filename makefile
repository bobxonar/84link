CFLAGS = -I./include -O2

84link.exe : ./src/main.c ./src/file.c ./include/file.h
	gcc -o 84link.exe ./src/main.c ./src/file.c $(CFLAGS)