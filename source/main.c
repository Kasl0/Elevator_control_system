#include "elevator_system.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    ElevatorSystem* elevator_system = malloc(sizeof(ElevatorSystem*));
    init(elevator_system, 2);
    
    update(elevator_system, 0, 10, 20);

    StatusTuple** tuple_colection = status(elevator_system);

    for (int i=0; i<elevator_system->no_elevators; i++) {
        printf("ID: %d, Current floor: %d, Target floor: %d\n", tuple_colection[i] -> elevator_ID, tuple_colection[i] -> current_floor, tuple_colection[i] -> target_floor);
    }
    
    return 0;
}
