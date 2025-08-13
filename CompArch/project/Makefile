CC = g++
CFLAGS = -Wall -Wextra -pedantic


main: cache main.cpp
	$(CC) $(CFLAGS) cache.o main.cpp -o exec

cache: cache.cpp
	$(CC) $(CFLAGS) -c cache.cpp