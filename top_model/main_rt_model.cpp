#ifndef NO_LOGGING
	#ifdef RT_ARM_MBED
		#include <cadmium/core/logger/rt.hpp>
	#else
		#include <cadmium/core/logger/csv.hpp> // new
	#endif
#endif
#include <cadmium/core/simulation/root_coordinator.hpp>
#include <limits>
#include "blinkySystem.hpp"
#ifdef RT_ARM_MBED
	#include "../mbed.h"
#endif

using namespace cadmium::blinkySystem;

int main(int argc, char *argv[]) {

	auto model = std::make_shared<blinkySystem>("blinkySystem");
	auto rootCoordinator = cadmium::RootCoordinator(model);

#ifndef NO_LOGGING
	printf("[simulation] welcome to rt-cadmium v2!\n"); // printing to serial port

	#ifdef RT_ARM_MBED
		auto logger = std::make_shared<cadmium::RTLogger>(";");
	# else
		auto logger = std::make_shared<cadmium::CSVLogger>("blinkyLog.csv",";"); // new
	#endif

	rootCoordinator.setLogger(logger);
#endif

	rootCoordinator.start();
// 	rootCoordinator.simulate(std::numeric_limits<double>::infinity());
	rootCoordinator.simulate(1000.0);
	rootCoordinator.stop();
	return 0;
}
// to make this model in RT use
// mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json --flash
