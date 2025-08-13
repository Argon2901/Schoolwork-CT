CC       = c++
FLAGS    = -no-pie
CFLAGS   = -g -O2 -Wno-write-strings -Wno-cpp
DFLAGS   = -DPACKAGE=\"threadsystem\" -DVERSION=\"1.0\" -DPTHREAD=1 -DUNIX_MSG_Q=1 -DSTDC_HEADERS=1
IFLAGS   = -I/local/eit-linux/apps/ThreadMentor/include
TMLIB    = /local/eit-linux/apps/ThreadMentor/Visual/libthreadclass.a
TMLIB_NV    = /local/eit-linux/apps/ThreadMentor/NoVisual/libthreadclass.a

all: thread main
	${CC} ${FLAGS} -o proj3 thread-main.o thread.o ${TMLIB_NV} -lpthread
thread: thread.cpp thread.h
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c thread.cpp
main:
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c thread-main.cpp
clean:
	 rm proj3 thread.o thread-main.o
debug: main.c hmalloc.c hmalloc.h
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} ${FLAGS} -Wall -g -o proj3 thread.cpp thread-main.cpp
submission:
	zip proj3.zip Makefile thread-main.cpp thread.cpp thread.h README
noVisual: thread main
	${CC} ${FLAGS} -o proj3 thread-main.o thread.o ${TMLIB_NV} -lpthread