CC = g++
CFLAGS = -g -Wall -std=c++14
EXEC = cs3421_emul
OBJECTS = main.o cpu.o clock.o memory.o emulator.o instruction_memory.o

${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} -o ${EXEC}

memory.o : memory.cpp memory.h
	${CC} ${CFLAGS} -c memory.cpp

cpu.o : cpu.cpp cpu.h
	${CC} ${CFLAGS} -c cpu.cpp

clock.o : clock.cpp clock.h
	${CC} ${CFLAGS} -c clock.cpp

emulator.o : emulator.cpp emulator.h
	${CC} ${CFLAGS} -c emulator.cpp

main.o : main.cpp
	${CC} ${CFLAGS} -c main.cpp




clean:
	rm -f ${EXEC} ${OBJECTS}
