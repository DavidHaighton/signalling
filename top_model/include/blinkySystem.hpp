#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <cadmium/core/modeling/coupled.hpp>

#ifdef RT_ARM_MBED
	#include <cadmium/core/real_time/arm_mbed/io/digitalOutput.hpp>
	#include <cadmium/core/real_time/arm_mbed/io/digitalInput.hpp>
#endif


#ifdef RT_ARM_MBED
	#include "../mbed.h"
	#include "PinNames.h"
#else
	#include "generator.hpp"
#endif

namespace cadmium::blinkySystem {

	struct blinkySystem : public Coupled {

		/**
		 * Constructor function for the blinkySystem model.
		 * @param id ID of the blinkySystem model.
		 */
		blinkySystem(const std::string& id) : Coupled(id) {
#ifdef RT_ARM_MBED
			// NUCLEO F401RE
			auto digitalOutput = addComponent<DigitalOutput>("digitalOutput", PA_3);
			auto digitalInput  = addComponent<DigitalInput>("digitalInput", PD_7);
			// BLUE PILL
			// auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", PC_13);
			// auto digitalInput  = addComponent<DigitalInput>("digitalInput", PB_14);
			addCoupling(digitalInput->out, digitalOutput->in);
#else
			auto generator = addComponent<Generator>("generator");
#endif
		}
	};
}  //namespace cadmium::blinkySystem

#endif //CADMIUM_EXAMPLE_BLINKY_HPP_
