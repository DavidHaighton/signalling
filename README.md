### RT_ARM_MBED INSTALL ###

Clone this repo into an empty folder
Clone https://github.com/SimulationEverywhere/cadmium_v2/tree/dev-rt into the sample folder 

Move the boost_1_70_0.7z from SampleRTModel up one directory. Unpack it and install (Offical instructions found here https://www.boost.org/doc/libs/1_70_0/more/getting_started/unix-variants.html)



## Installing should be just ( I think)
```shell
cd boost_1_70_0 
bootstrap.sh
./b2 install
```

Your folder directory should look like 

![File Directory](https://github.com/jonmenard/SampleRTModel/blob/main/ReadMeFiles/directorySetup.png?raw=true)

To run this model 

## To run this model where NUCLEO_F01RE is replaced with the name of your microcontroller
Plug you microcontroller in
```shell
cd SampleRtModel/top_model 
mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json --flash

```

This mode will take a digital input from pin 13 and relay it to pin 2 using a polling rate of 100ms while the digital inputs from pin 13 will also be relayed to pin 4 using an interupt. The interup signal should be faster than the polling.

Sample video avaible at https://github.com/jonmenard/SampleRTModel/blob/main/ReadMeFiles/AsynchrnousEventTest.mp4

![Sample Video](https://github.com/jonmenard/SampleRTModel/blob/main/ReadMeFiles/directorySetup.png?raw=true)
