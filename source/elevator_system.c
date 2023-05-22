#include "elevator_system.h"
#include <stdint.h>
#include <stdlib.h>

void init(ElevatorSystem* elevator_system, uint8_t no_elevators) {

    elevator_system -> elevators = malloc(sizeof(Elevator*) * no_elevators);


    for (int i=0; i<no_elevators; i++) {
        elevator_system -> elevators[i] = elevator_init(i);
    }

    elevator_system -> no_elevators = no_elevators;
}

Elevator* get_elevator_with_id(ElevatorSystem* elevator_system, id elevator_ID) {

    for (int i=0; i<elevator_system->no_elevators; i++) {
        if (elevator_system -> elevators[i] -> ID == elevator_ID) {
            return elevator_system -> elevators[i];
        }
    }

    // elevator not found
    return NULL;
}


void pickup(ElevatorSystem* elevator_system, floor pickup_floor, int8_t direction) {
    ;
}

int update(ElevatorSystem* elevator_system, id elevator_ID, floor current_floor, floor target_floor) {

    Elevator* elevator = get_elevator_with_id(elevator_system, elevator_ID);

    if (elevator) {
        elevator_update(elevator, current_floor, target_floor);
        return 0;
    }
    else return -1;
}

void step(ElevatorSystem* elevator_system) {
    ;
}

StatusTuple** status(ElevatorSystem* elevator_system) {

    StatusTuple** tuple_colection = malloc(sizeof(StatusTuple*) * elevator_system->no_elevators);

    for (int i=0; i<elevator_system->no_elevators; i++) {
        tuple_colection[i] = elevator_status(elevator_system -> elevators[i]);
    }

    return tuple_colection;
}
