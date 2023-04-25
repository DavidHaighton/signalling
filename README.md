# Car front and tail lights simulation
By David Haighton

This project is to demo how DEVS can be used for V&V in realtime systems by first simulating the project and testing it, then flashing the project on a board

## Compiling and Running
You are required to have the branch of RT cadmium one directory above this one.

To run the project in simulation mode, CD to top_model and run `make all`

To run the project in embedded mode, connect the NUCLEO_H743ZI2 board to one of the USB ports of your computer and do the same thing, but do `make` instead of make all

## Testing
all tests were done in 1 test suite which is the main
the signalLog.csv will show all possible nodes and transitions of the entire application.
