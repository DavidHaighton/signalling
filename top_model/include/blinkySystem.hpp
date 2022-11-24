#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <cadmium/core/modeling/coupled.hpp>
#include <cadmium/core/real_time/arm_mbed/io/digitalOutput.hpp>
#include <cadmium/core/real_time/arm_mbed/io/digitalInput.hpp>
// #include <cadmium/core/real_time/arm_mbed/io/interruptInput.hpp>
#include "blinky.hpp"
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
		
			// NUCLEO F103RB	
			auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", LED1); // PC_13); // LED1); // D3);
			auto digitalInput  = addComponent<DigitalInput>("digital", PC_13); // PB_14); // PC_13); // D11);
			// BLUE PILL
			// auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", PC_13); // LED1); // D3);
			// auto digitalInput  = addComponent<DigitalInput>("digital", PB_14); // PC_13); // D11);
			auto blinky = addComponent<Blinky>("blinky");
			
			addCoupling(digitalInput->out, blinky->in);
			addCoupling(blinky->out, digitalOutput->in);
			// addCoupling(digitalInput->out, digitalOutput->in);

		}
	};
}  //namespace cadmium::example::covidSupervisorySystem

#endif //CADMIUM_EXAMPLE_BLINKY_HPP_
