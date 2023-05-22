#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int8_t floor;

typedef struct {
    int ID;
    floor current_floor;
    floor target_floor;
} Elevator;

Elevator* elevator_init(int elevator_ID) {

    Elevator* elevator = malloc(sizeof(Elevator));

    elevator -> ID = elevator_ID;
    elevator -> current_floor = 0;
    elevator -> target_floor = 0;

    return elevator;
}

void pickup(int floor, bool direction) {
    ;
}

void update(Elevator* elevator, int current_floor, int target_floor) {
    elevator -> current_floor = current_floor;
    elevator -> target_floor = target_floor;
}

void step() {
    ;
}

void status(Elevator* elevator) {
    printf("ID: %d, Current floor: %d, Target floor: %d\n", elevator -> ID, elevator -> current_floor, elevator -> target_floor);
}

int main() {

    Elevator* elevator1 = elevator_init(1);
    status(elevator1);

    return 0;
}