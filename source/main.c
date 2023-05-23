#include "elevator_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STREAM stdin
#define MAX_COMMAND_LEN 20

int main(int argc, char* argv[]) {

    ElevatorSystem* elevator_system = malloc(sizeof(ElevatorSystem*));
    init(elevator_system, (uint8_t) atoi(argv[1]), (uint8_t) atoi(argv[2]));

    char command[MAX_COMMAND_LEN];

    while(1) {

        printf("> ");
        if (fgets(command, MAX_COMMAND_LEN, STREAM) == NULL) break;

        char *word = strtok(command, " ");

        if(strcmp(word, "pickup") == 0) {

            word = strtok(NULL, " ");
            floor pickup_floor = (floor) atoi(word);

            word = strtok(NULL, "\n");
            direction dir = (direction) atoi(word);

            pickup(elevator_system, pickup_floor, dir);
        }

        else if(strcmp(word, "update") == 0) {

            word = strtok(NULL, " ");
            id elevator_id = (id) atoi(word);

            word = strtok(NULL, "\n");
            floor target_floor = (floor) atoi(word);
            
            update(elevator_system, elevator_id, target_floor);
        }

        else if(strcmp(word, "step\n") == 0) {
            step(elevator_system);
        }

        else if(strcmp(word, "status\n") == 0) {
            print_status(elevator_system);
        }

        else if(strcmp(word, "exit\n") == 0) {
            free_memory(elevator_system);
            break;
        }

        else if(strcmp(word, "\n") == 0) {
            continue;
        }
        
        else {
            printf("Unknown command: %s\n", command);
        }
    }
    
    return 0;
}
