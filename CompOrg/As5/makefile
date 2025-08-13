CC = g++
CFLAGS = -g -Wall -std=c++14
EXEC = cs3421_emul
OBJECTS = main.o cpu.o clock.o memory.o emulator.o instruction_memory.o cache.o io_device.o

${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} -o ${EXEC}

cache.o : cache.cpp cache.h
	${CC} ${CFLAGS} -c cache.cpp

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

io_device.o : io_device.cpp	
	${CC} ${CFLAGS} -c io_device.cpp


clean:
	rm -f ${EXEC} ${OBJECTS}
