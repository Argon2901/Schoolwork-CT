CC       = c++
FLAGS    = -no-pie
CFLAGS   = -g -O2 -Wno-write-strings -Wno-cpp
DFLAGS   = -DPACKAGE=\"threadsystem\" -DVERSION=\"1.0\" -DPTHREAD=1 -DUNIX_MSG_Q=1 -DSTDC_HEADERS=1
IFLAGS   = -I/local/eit-linux/apps/ThreadMentor/include
TMLIB    = /local/eit-linux/apps/ThreadMentor/Visual/libthreadclass.a
TMLIB_NV    = /local/eit-linux/apps/ThreadMentor/NoVisual/libthreadclass.a

all: thread main support shared
	${CC} ${FLAGS} -o proj4 thread-main.o thread.o thread-support.o shared.o ${TMLIB_NV} -lpthread
thread: thread.cpp thread.h
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c thread.cpp
main:
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c thread-main.cpp
support: thread-support.cpp thread.h
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c thread-support.cpp
shared:
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c shared.cpp
clean:
	 rm proj4 *.o
debug: thread.cpp thread-main.cpp thread-support.cpp
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} ${FLAGS} -Wall -g -o proj3 thread.cpp thread-main.cpp thread-support.cpp shared.cpp
submission:
	zip proj4.zip Makefile *.cpp *.h README
noVisual: thread main support shared 
	${CC} ${FLAGS} -o proj4 thread-main.o thread.o thread-support.o shared.o ${TMLIB_NV} -lpthread