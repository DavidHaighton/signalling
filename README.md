# Car front and tail lights simulation
By David Haighton

This project is to demo how DEVS can be used for V&V in realtime systems by first simulating the project and testing it, then flashing the project on a board

## Compiling and Running

To run the project in simulation mode, CD to top_model and run `make all`

To run the project in embedded mode, connect the NUCLEO_H743ZI2 board to one of the USB ports of your computer and do the same thing, but do `make` instead of make all

Scripts are provided to do both

Make sure you have all required dependencies for cadmium and e-cadmium to run the simulation and flashing the board

## Testing
all tests were done in 1 test suite which is the main
the signalLog.csv will show all possible nodes and transitions of the entire application.
Results of the test can be found in the "Signal Lights"/top_model directory with the name signalLog.csv.

