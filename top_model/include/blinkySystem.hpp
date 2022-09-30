#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <cadmium/core/modeling/coupled.hpp>
#include <cadmium/core/real_time/arm_mbed/io/digitalOutput.hpp>
#include <cadmium/core/real_time/arm_mbed/io/digitalInput.hpp>
#include <cadmium/core/real_time/arm_mbed/io/interruptInput.hpp>
#include "./repeater.hpp"
#include "../mbed.h"
#include "PinNames.h"

namespace cadmium::blinkySystem {
	//! Coupled DEVS model to show how the IEStream atomic model works.
	struct blinkySystem : public Coupled {

		/**
		 * Constructor function for the iestream model.
		 * @param id ID of the iestream model.
		 * @param filePath path to the input file to be read.
		 */
		blinkySystem(const std::string& id) : Coupled(id) {
			
			auto digitalOuput = addComponent<DigitalOutput>("digitalOuput", D4);
			auto digitalOuput1 = addComponent<DigitalOutput>("digitalOuput1", D2);
			auto interrupt = addComponent<InterruptInput>("interrupt", D13);
			auto digitalInput = addComponent<DigitalInput>("digital", D13);
			// auto repeater = addComponent<Repeater>("repeater", 2);
			
			addCoupling(digitalInput->out, digitalOuput1->in);
			addCoupling(interrupt->out, digitalOuput->in);
		

		}
	};
}  //namespace cadmium::example::covidSupervisorySystem

#endif //CADMIUM_EXAMPLE_BLINKY_HPP_