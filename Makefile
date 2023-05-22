CC = gcc
CFLAGS = -Wall
SOURCE_PATH = source/
ELEVATOR = elevator
ELEVATOR_SYSTEM = elevator_system
PROGRAM = main

NO_ELEVATORS = 2

all:
	${CC} ${CFLAGS} ${SOURCE_PATH}${ELEVATOR}.c ${SOURCE_PATH}${ELEVATOR_SYSTEM}.c ${SOURCE_PATH}${PROGRAM}.c -o ${PROGRAM}
	${PROGRAM}.exe ${NO_ELEVATORS}
	make clean

clean:
	rm ${PROGRAM}.exe
