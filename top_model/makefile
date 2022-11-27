embedded:
	mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json --flash
#	mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium2.json --flash
#	mbed compile --target NUCLEO_F103RB --toolchain GCC_ARM --profile ../cadmium.json
#	mbed compile --target NUCLEO_F103RB --toolchain GCC_ARM --profile ../cadmium.json --flash
#	mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json
#	mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json --stats-depth 100
#	mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile develop --profile ../cadmium.json

clean-embedded:
	rm -r ../BUILD/

all: main.o
	g++ -g -o Blinky main.o 

main.o: main_rt_model.cpp
	g++ -g -c -std=c++17 -I ../../cadmium_v2/include -I include main_rt_model.cpp -o main.o

clean:
	rm *.o
	rm *.csv

