#ifndef ELEVATOR_SYSTEM_H
#define ELEVATOR_SYSTEM_H

#include "elevator.h"

#define STARTING_ORDERS_CAPACITY 10

typedef struct {
    floor pickup_floor;
    direction direction;
} Order;

typedef struct {

    uint8_t no_elevators;
    Elevator** elevators;

    uint8_t no_orders;
    Order** orders;
    uint8_t _orders_capacity; // for dynamic memory relocation

} ElevatorSystem;

// ElevatorSystem functions
void init(ElevatorSystem* elevator_system, uint8_t no_elevators);                                           // inits provided ElevatorSystem and all elevators with current_floor = 0
Elevator* get_elevator_with_id(ElevatorSystem* elevator_system, id elevator_ID);                            // returns pointer to Elevator with given ID in ElevatorSystem or null if Elevator with given ID does not exist
void pickup(ElevatorSystem* elevator_system, floor pickup_floor, direction direction);                      // adds new Order to the ElevatorSystem
int8_t update(ElevatorSystem* elevator_system, id elevator_id, floor current_floor, floor target_floor);    // updates struct fields of Elevator with the given ID in ElevatorSystem
void step(ElevatorSystem* elevator_system);                                                                 // performs a simulation step
StatusTuple** status(ElevatorSystem* elevator_system);                                                      // returns array of StatusTuple with information about all Elevators in ElevatorSystem
void print_status(ElevatorSystem* elevator_system);                                                         // prints information about all Elevators in ElevatorSystem

#endif
