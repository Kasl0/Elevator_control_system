#ifndef ELEVATOR_SYSTEM_H
#define ELEVATOR_SYSTEM_H

#include "elevator.h"

typedef struct {

    uint8_t no_floors;
    uint8_t no_elevators;
    Elevator** elevators;

} ElevatorSystem;

// ElevatorSystem functions
void init(ElevatorSystem* elevator_system, uint8_t no_floors, uint8_t no_elevators);                        // inits provided ElevatorSystem and all elevators with current_floor = 0
Elevator* get_elevator_with_id(ElevatorSystem* elevator_system, id elevator_ID);                            // returns pointer to Elevator with given ID in ElevatorSystem or null if Elevator with given ID does not exist
void pickup(ElevatorSystem* elevator_system, floor pickup_floor, direction direction);                      // calculates FSs, selects an Elevator and adds pickup_floor to it's planned route
int8_t update(ElevatorSystem* elevator_system, id elevator_ID, floor target_floor);                         // adds target_floor to Elevator's planned route
void step(ElevatorSystem* elevator_system);                                                                 // performs a simulation step
StatusTuple** status(ElevatorSystem* elevator_system);                                                      // returns array of StatusTuple with information about all Elevators in ElevatorSystem
void print_status(ElevatorSystem* elevator_system);                                                         // prints information about all Elevators in ElevatorSystem
void free_memory(ElevatorSystem* elevator_system);                                                          // frees each Elevator's memory and ElevatorSystem memory

#endif
