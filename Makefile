CC = gcc
CFLAGS = -Wall
SOURCE_PATH = source/
ELEVATOR = elevator
ELEVATOR_SYSTEM = elevator_system
PROGRAM = main

all:
	${CC} ${CFLAGS} ${SOURCE_PATH}${ELEVATOR}.c ${SOURCE_PATH}${ELEVATOR_SYSTEM}.c ${SOURCE_PATH}${PROGRAM}.c -o ${PROGRAM}
	${PROGRAM}.exe
	make clean

clean:
	rm ${PROGRAM}.exe
