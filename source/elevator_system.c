#include "elevator_system.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void init(ElevatorSystem* elevator_system, uint8_t no_floors, uint8_t no_elevators) {

    elevator_system -> no_floors = no_floors;

    elevator_system -> elevators = malloc(sizeof(Elevator*) * no_elevators);


    for (uint8_t i=0; i < no_elevators; i++) {
        elevator_system -> elevators[i] = elevator_init(i);
    }

    elevator_system -> no_elevators = no_elevators;
}

Elevator* get_elevator_with_id(ElevatorSystem* elevator_system, id elevator_ID) {

    for (uint8_t i=0; i < elevator_system->no_elevators; i++) {
        if (elevator_system -> elevators[i] -> ID == elevator_ID) {
            return elevator_system -> elevators[i];
        }
    }

    // elevator not found
    return NULL;
}


void pickup(ElevatorSystem* elevator_system, floor pickup_floor, direction direction) {

    uint8_t highest_FS_value = 0;
    Elevator* highest_FS_elevator;

    for (uint8_t i=0; i < elevator_system->no_elevators; i++) {

        uint8_t FS_value = elevator_calculate_FS(elevator_system->elevators[i], elevator_system->no_floors, pickup_floor, direction);

        if ((FS_value == highest_FS_value &&
            (abs(pickup_floor - elevator_system->elevators[i]->current_floor) < abs(pickup_floor - highest_FS_elevator->current_floor))) ||
            (FS_value > highest_FS_value)) {

            highest_FS_value = FS_value;
            highest_FS_elevator = elevator_system->elevators[i];
        }
    }

    elevator_add_target(highest_FS_elevator, pickup_floor, direction);
}

int8_t update(ElevatorSystem* elevator_system, id elevator_ID, floor target_floor) {

    Elevator* elevator = get_elevator_with_id(elevator_system, elevator_ID);

    if (elevator) {
        elevator_add_target(elevator, target_floor, 0);
        return 0;
    }
    else return -1;
}

void step(ElevatorSystem* elevator_system) {
    for (uint8_t i=0; i < elevator_system->no_elevators; i++) {
        elevator_step(elevator_system->elevators[i]);
    }
}

StatusTuple** status(ElevatorSystem* elevator_system) {

    StatusTuple** tuple_colection = malloc(sizeof(StatusTuple*) * elevator_system->no_elevators);

    for (uint8_t i=0; i < elevator_system->no_elevators; i++) {
        tuple_colection[i] = elevator_status(elevator_system -> elevators[i]);
    }

    return tuple_colection;
}

void print_status(ElevatorSystem* elevator_system) {

    for (uint8_t i=0; i < elevator_system->no_elevators; i++) {

        printf("Elevator ID: %d, Current floor: %d, Number of target floors: %d, Target floors: [", elevator_system->elevators[i]->ID, elevator_system->elevators[i]->current_floor, elevator_system->elevators[i]->no_target_floors);

        for (uint8_t j=0; j < elevator_system->elevators[i]->no_target_floors; j++) {
            if (j == elevator_system->elevators[i]->no_target_floors-1) printf("%d", elevator_system->elevators[i]->target_floors[j]);
            else printf("%d, ", elevator_system->elevators[i]->target_floors[j]);
        }
        printf("]\n");
    }
}

void free_memory(ElevatorSystem* elevator_system) {

    for (uint8_t i=0; i < elevator_system->no_elevators; i++) {
        elevator_free_memory(elevator_system->elevators[i]);
    }

    free(elevator_system->elevators);
    free(elevator_system);
}
