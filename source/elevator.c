#include "elevator.h"
#include <stdlib.h>

Elevator* elevator_init(id elevator_ID) {

    Elevator* elevator = malloc(sizeof(Elevator));

    elevator -> ID = elevator_ID;
    elevator -> current_floor = 0;
    elevator -> target_floor = 0;

    return elevator;
}

void elevator_update(Elevator* elevator, floor current_floor, floor target_floor) {
    elevator -> current_floor = current_floor;
    elevator -> target_floor = target_floor;
}

void elevator_step(Elevator* elevator) {

    if (elevator -> current_floor != elevator -> target_floor) {

        if (elevator -> target_floor - elevator -> current_floor > 0) elevator -> current_floor++;
        else elevator -> current_floor--;
    }
}

StatusTuple* elevator_status(Elevator* elevator) {
    StatusTuple* status_tuple = malloc(sizeof(StatusTuple));

    status_tuple -> elevator_ID = elevator -> ID;
    status_tuple -> current_floor = elevator -> current_floor;
    status_tuple -> target_floor = elevator -> target_floor;

    return status_tuple;
}

void elevator_free_memory(Elevator* elevator) {
    free(elevator);
}
