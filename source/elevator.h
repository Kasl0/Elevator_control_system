#ifndef ELEVATOR__H
#define ELEVATOR__H

#include <stdint.h>

typedef uint8_t id;
typedef int8_t floor;
typedef int8_t direction;

typedef struct {

    id ID;
    floor current_floor;
    uint8_t no_target_floors;
    floor* target_floors;

} Elevator;

typedef struct {

    id elevator_ID;
    floor current_floor;
    uint8_t no_target_floors;
    floor* target_floors;

} StatusTuple;

// Elevator functions
Elevator* elevator_init(id elevator_ID);
uint8_t elevator_calculate_FS(Elevator* elevator, uint8_t no_floors, floor pickup_floor, direction direction);
void elevator_add_target(Elevator* elevator, floor target_floor, direction direction);
void elevator_step(Elevator* elevator);
StatusTuple* elevator_status(Elevator* elevator);
void elevator_free_memory(Elevator* elevator);

#endif
