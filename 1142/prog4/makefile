CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
LDFLAGS = 
EXEC = prog4
OBJECTS = prog4.o main.o

${EXEC}: ${OBJECTS}
	${CC} ${LDFLAGS} ${OBJECTS} -o ${EXEC}

prog4.o : prog4.c prog4.h
	${CC} ${CFLAGS} -c prog4.c

main.o : main.c
	${CC} ${CFLAGS} -c main.c

clean: 
	rm -f ${EXEC} ${OBJECTS}
