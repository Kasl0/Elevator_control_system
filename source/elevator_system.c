#include "elevator_system.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void init(ElevatorSystem* elevator_system, uint8_t no_elevators) {

    elevator_system -> elevators = malloc(sizeof(Elevator*) * no_elevators);


    for (uint8_t i=0; i<no_elevators; i++) {
        elevator_system -> elevators[i] = elevator_init(i);
    }

    elevator_system -> no_elevators = no_elevators;

    elevator_system -> _orders_capacity = STARTING_ORDERS_CAPACITY;
    elevator_system -> orders = malloc(sizeof(Order*) * elevator_system -> _orders_capacity);
    elevator_system -> no_orders = 0;
}

Elevator* get_elevator_with_id(ElevatorSystem* elevator_system, id elevator_ID) {

    for (uint8_t i=0; i<elevator_system->no_elevators; i++) {
        if (elevator_system -> elevators[i] -> ID == elevator_ID) {
            return elevator_system -> elevators[i];
        }
    }

    // elevator not found
    return NULL;
}


void pickup(ElevatorSystem* elevator_system, floor pickup_floor, direction direction) {

    Order* order = malloc(sizeof(Order));
    order -> pickup_floor = pickup_floor;
    order -> direction = direction;

    // if there is no place for new order, increase _orders_capacity and realloc array
    if (elevator_system -> no_orders == elevator_system ->_orders_capacity) {
        elevator_system ->_orders_capacity *= 2;
        elevator_system -> orders = realloc(elevator_system -> orders, sizeof(Order*) * elevator_system ->_orders_capacity);
    }

    elevator_system -> orders[elevator_system -> no_orders] = order;
    elevator_system -> no_orders++;
    
}

int8_t update(ElevatorSystem* elevator_system, id elevator_ID, floor current_floor, floor target_floor) {

    Elevator* elevator = get_elevator_with_id(elevator_system, elevator_ID);

    if (elevator) {
        elevator_update(elevator, current_floor, target_floor);
        return 0;
    }
    else return -1;
}

void step(ElevatorSystem* elevator_system) {
    for (uint8_t i=0; i<elevator_system->no_elevators; i++) {
        elevator_step(elevator_system->elevators[i]);
    }
}

StatusTuple** status(ElevatorSystem* elevator_system) {

    StatusTuple** tuple_colection = malloc(sizeof(StatusTuple*) * elevator_system->no_elevators);

    for (uint8_t i=0; i<elevator_system->no_elevators; i++) {
        tuple_colection[i] = elevator_status(elevator_system -> elevators[i]);
    }

    return tuple_colection;
}

void print_status(ElevatorSystem* elevator_system) {
    StatusTuple** tuple_colection = status(elevator_system);

    for (uint8_t i=0; i<elevator_system->no_elevators; i++) {
        printf("ID: %d, Current floor: %d, Target floor: %d\n", tuple_colection[i] -> elevator_ID, tuple_colection[i] -> current_floor, tuple_colection[i] -> target_floor);
        free(tuple_colection[i]);
    }
    free(tuple_colection);
}

void free_memory(ElevatorSystem* elevator_system) {
    for (uint8_t i=0; i<elevator_system->no_elevators; i++) {
        elevator_free_memory(elevator_system->elevators[i]);
    }
    free(elevator_system->elevators);
    free(elevator_system);
}
