#include <cadmium/core/simulation/root_coordinator.hpp>
#include <cadmium/core/logger/csv.hpp>
#include <cadmium/core/logger/rt.hpp>
#include <limits>
#include "blinkySystem.hpp"
#include "../mbed.h"

using namespace cadmium::blinkySystem;

int main(int argc, char *argv[]) {
	// First, we parse the arguments
	std::ifstream file;

	printf("starting simulation ...\n");
//	cout << "starting simulation ..." << endl;

	auto model = std::make_shared<blinkySystem>("blinkySystem");
	auto rootCoordinator = cadmium::RootCoordinator(model);

#ifdef RT_ARM_MBED
	auto logger = std::make_shared<cadmium::RTLogger>(";");
#else
	auto logger = std::make_shared<cadmium::CSVLogger>("hola.csv", ";");
#endif
	rootCoordinator.setLogger(logger);

	rootCoordinator.start();
	rootCoordinator.simulate(std::numeric_limits<double>::infinity());
	rootCoordinator.stop();
	return 0;
}
// to make this model in RT use
// mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json --flash
