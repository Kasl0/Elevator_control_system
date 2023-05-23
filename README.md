# Elevator control system

## Algorithm description
The elevator selection algorithm used in this case, with each new call, calculates the figure of suitability (FS) for each elevator, and then selects the elevator with the highest FS. This is how we select an elevator that will realize pickup operation.
I took the formulas for calculating FS from section *2.1. EGC with Conventional Nearest Car Algorithm* of the website: https://www.mdpi.com/1996-1073/13/23/6161.

Once we've selected the elevator that will fulfill the call, we need to plan its route - or, in fact, modify an already existing route by adding an additional stop along the way. Elevator struct, instead of storing a single target floor number, will store an array of floor numbers. The elevator will move and execute orders according to the order in this array. This will be its route.

In order to modify the route, we will have to add floors somewhere inside the array, and remove those already visited (on first array index). For this, we will use dynamically allocated memory with realloc() function.

It remains to find a way to calculate the index number of the array into which we want to insert a new floor number. Here I used my own algorithm that, based on the direction of the elevator, the direction of travel and the floor number, inserts the floor number into the appropriate place on the route.

This way we achieve the most optimal algorithm for elevator system control.

## Implementation description
I decided to write the Elevator control system in pure C, in order to easily port the application to an embedded platform.
The project consists of files (located in source folder):
- elevator.h / elevator.c
  - responsible for single elevator functions
- elevator_system.h / elevator_system.c
  - responsible for elevator system functions
- main.c
  - inits ElevatorSystem, implements REPL interface for reading user commands

## To start the program
- Execute Makefile in the project's root directory in order to compile and run the project
  - You need to have gcc compiler and make tool
  - Enter Elevator_control_system folder
    - **cd ./Elevator_control_system**
  - Run make
    - **make**
  - The project is being compiled and the program is about to start :))
  - To run the program with different number of elevators edit Makefile file and "make" it again (edit NO_ELEVATORS variable)

## Program interaction
- The project implements REPL interface to interact with the control system through commands typed in stdio by the user
- If there is a need to port the project to an embeeded platform, we can simply assign functions declared in elevator_system.h to appropriate triggers
  - For example, an interrupt caused by clicking a physical button can call pickup() function with current floor and direction arguments
### Allowed commands in the REPL:
  - **pickup <pickup_floor_number> <direction\>**
    - calculates FSs, selects an Elevator and adds pickup_floor to it's planned route
    - imitates calling an elevator (we choose the direction of travel)
    - negative direction value means going down, positive means going up
    - e.g. "pickup 3 -1"
  - **update <elevator_id> <target_floor_number>**
    - adds target_floor to Elevator's planned route
    - imitates selection of the target floor inside the elevator
    - e.g. "update 0 10"
  - **step**
    - performs a simulation step
  - **status**
    - prints information about all Elevators in ElevatorSystem
  - **exit**
    - frees each Elevator's memory and ElevatorSystem memory and exits the program
#### Each command have to be ended with an end-of-line character (enter must be pressed)
#### Other commands (or misspelled commands) will not be recognized
