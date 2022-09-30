#include <cadmium/core/simulation/root_coordinator.hpp>
#include <limits>
#include "blinkySystem.hpp"
#include "../mbed.h"

using namespace cadmium::blinkySystem;

int main(int argc, char *argv[]) {
	// First, we parse the arguments
	std::ifstream file;

	auto model = std::make_shared<blinkySystem>("blinkySystem");
	auto rootCoordinator = cadmium::RootCoordinator(model);
	rootCoordinator.start();
	rootCoordinator.simulate(std::numeric_limits<double>::infinity());
	rootCoordinator.stop();
	return 0;
}
// to make this model in RT use
// mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM --profile ../cadmium.json --flash
