#ifndef ELEVATOR_SYSTEM_H
#define ELEVATOR_SYSTEM_H

#include "elevator.h"

typedef struct {

    uint8_t no_elevators;
    Elevator** elevators;

} ElevatorSystem;

// ElevatorSystem functions:
void init(ElevatorSystem* elevator_system, uint8_t no_elevators);
Elevator* get_elevator_with_id(ElevatorSystem* elevator_system, id elevator_ID);
void pickup(ElevatorSystem* elevator_system, floor pickup_floor, int8_t direction);
int update(ElevatorSystem* elevator_system, id elevator_id, floor current_floor, floor target_floor);
void step(ElevatorSystem* elevator_system);
StatusTuple** status(ElevatorSystem* elevator_system);

#endif
