#ifndef ELEVATOR__H
#define ELEVATOR__H

#include <stdint.h>

typedef uint8_t id;
typedef int8_t floor;
typedef int8_t direction;

typedef struct {

    id ID;
    floor current_floor;
    floor target_floor;

} Elevator;

typedef struct {

    id elevator_ID;
    floor current_floor;
    floor target_floor;

} StatusTuple;

// Elevator functions
Elevator* elevator_init(id elevator_ID);
void elevator_update(Elevator* elevator, floor current_floor, floor target_floor);
void elevator_step(Elevator* elevator);
StatusTuple* elevator_status(Elevator* elevator);
void elevator_free_memory(Elevator* elevator);

#endif
