# Elevator control system

## Description
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
  - **pickup <pickup_floor_number> <direction>**
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
