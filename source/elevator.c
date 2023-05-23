#include "elevator.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Elevator* elevator_init(id elevator_ID) {

    Elevator* elevator = malloc(sizeof(Elevator));

    elevator -> ID = elevator_ID;
    elevator -> current_floor = 0;

    elevator -> no_target_floors = 0;
    elevator -> target_floors = NULL;

    return elevator;
}

uint8_t elevator_calculate_FS(Elevator* elevator, uint8_t no_floors, floor pickup_floor, direction direction) {

    int16_t difference = pickup_floor - elevator->current_floor;

    // 1
    if (elevator -> no_target_floors == 0 || (difference * direction > 0 &&
        ((pickup_floor < elevator->current_floor && elevator->target_floors[0] < elevator->current_floor) ||
        (elevator->current_floor < elevator->target_floors[0] && elevator->current_floor < pickup_floor)))) {
        return no_floors - abs(difference) + 1;
    }

    // 2
    if (elevator -> no_target_floors == 0 || (difference * direction < 0 &&
        ((pickup_floor < elevator->current_floor && elevator->target_floors[0] < elevator->current_floor) ||
        (elevator->current_floor < elevator->target_floors[0] && elevator->current_floor < pickup_floor)))) {
        return no_floors - abs(difference);
    }
    
    // 3
    return 0;
    
}

void elevator_add_target(Elevator* elevator, floor target_floor, direction direction) {

    uint8_t index;
    bool index_assigned = 0;

    // we already plan to stop at this floor with that direction
    if (elevator->no_target_floors >= 1 && elevator -> target_floors[0] == target_floor && direction * (target_floor - elevator->current_floor) >= 0) return;

    else if (elevator->no_target_floors == 1 &&
    ((elevator->current_floor < target_floor && target_floor < elevator->target_floors[0]) || (elevator->current_floor > target_floor && target_floor > elevator->target_floors[0]))
    && direction * (elevator -> target_floors[0] - elevator->current_floor) >= 0) {
        index = 0;
        index_assigned = 1;
    }

    else for (uint8_t i=0; i < elevator->no_target_floors-1; i++) {

        floor floor1 = elevator -> target_floors[i];
        floor floor2 = elevator -> target_floors[i+1];

        // we already plan to stop at this floor with that direction
        if (target_floor == floor2 && direction * (floor2-floor1) >= 0) 
            return;

        if (((floor1 < target_floor && target_floor < floor2) || (floor1 > target_floor && target_floor > floor2)) && direction * (floor2-floor1) >= 0) {
            index = i+1;
            index_assigned = 1;
            break;
        }
    }

    if (index_assigned == 0)
        index = elevator->no_target_floors;

    elevator -> no_target_floors++;

    elevator -> target_floors = realloc(elevator -> target_floors, sizeof(floor) * elevator -> no_target_floors);

    for (uint8_t i = elevator->no_target_floors - 1; i > index; i--) {
        elevator -> target_floors[i] = elevator -> target_floors[i-1];
    }

    elevator -> target_floors[index] = target_floor;
}

void _remove_first_target(Elevator* elevator) {

    elevator -> no_target_floors--;

    for (uint8_t i=0; i < (elevator -> no_target_floors); i++) {
        elevator -> target_floors[i] = elevator -> target_floors[i+1];
    }

    elevator -> target_floors = realloc(elevator -> target_floors, sizeof(floor) * elevator -> no_target_floors);
    
}

void elevator_step(Elevator* elevator) {

    if (elevator -> no_target_floors > 0) {

        if (elevator -> target_floors[0] == elevator -> current_floor) _remove_first_target(elevator);

        else if (elevator -> target_floors[0] - elevator -> current_floor > 0) elevator -> current_floor++;
        else elevator -> current_floor--;

    }
}

StatusTuple* elevator_status(Elevator* elevator) {
    StatusTuple* status_tuple = malloc(sizeof(StatusTuple));

    status_tuple -> elevator_ID = elevator -> ID;
    status_tuple -> current_floor = elevator -> current_floor;
    status_tuple -> no_target_floors = elevator -> no_target_floors;

    if (elevator -> no_target_floors > 0)
        memcpy(status_tuple -> target_floors, elevator -> target_floors, sizeof(sizeof(floor) * elevator -> no_target_floors));
    else
        status_tuple -> target_floors = NULL;

    return status_tuple;
}

void elevator_free_memory(Elevator* elevator) {
    free(elevator->target_floors);
    free(elevator);
}
