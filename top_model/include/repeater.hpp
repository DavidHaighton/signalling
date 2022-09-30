#ifndef _REPEATER_HPP__
#define _REPEATER_HPP__

#include <cadmium/core/modeling/atomic.hpp>
#include <iostream>

namespace cadmium::blinkySystem {
	//! Class for representing the Processor DEVS model state.
	struct RepeaterState {
		bool output;
		bool last;
		double sigma;
		//! Processor state constructor. By default, the processor is idling.
		RepeaterState(): output(true), last(true), sigma(0)  {}
	};

	/**
	 * Insertion operator for ProcessorState objects. It only displays the value of sigma.
	 * @param out output stream.
	 * @param s state to be represented in the output stream.
	 * @return output stream with sigma already inserted.
	 */
	std::ostream& operator<<(std::ostream &out, const RepeaterState& state) {
		out << "Status:, " << state.output;
		return out;
	}

	//! Atomic DEVS model of a Job processor.
	class Repeater : public Atomic<RepeaterState> {
	 private:
		
	 public:
		Port<bool> out;  
		float sleepTime;
  

		/**
		 * Constructor function.
		 * @param id ID of the new Processor model object.
		 */
		Repeater(const std::string& id, float time): Atomic<RepeaterState>(id, RepeaterState()) {
			out = addOutPort<bool>("out");
			sleepTime = time;
		}

		/**
		 * It updates the ProcessorState::clock, clears the ProcessorState::Job being processed, and passivates.
		 * @param state reference to the current state of the model.
		 */
		void internalTransition(RepeaterState& state) const override {
			state.sigma = sleepTime;
			state.output = !state.output;
		}

		/**
		 * Updates ProcessorState::clock and ProcessorState::sigma.
		 * If it is idling and gets a new Job via the Processor::inGenerated port, it starts processing it.
		 * @param state reference to the current model state.
		 * @param e time elapsed since the last state transition function was triggered.
		 * @param x reference to the model input port set.
		 */
		void externalTransition(RepeaterState& state, double e) const override {
		}

		/**
		 * It outputs the already processed ProcessorState::Job via the Processor::outProcessed port.
		 * @param state reference to the current model state.
		 * @param y reference to the atomic model output port set.
		 */
		void output(const RepeaterState& state) const override {	
			out->addMessage(!state.output);	
		}

		/**
		 * It returns the value of ProcessorState::sigma.
		 * @param state reference to the current model state.
		 * @return the sigma value.
		 */
		[[nodiscard]] double timeAdvance(const RepeaterState& state) const override {
			return state.sigma;
		}
	};
}  //namespace cadmium::example::covidSupervisorySystem

#endif //_REPEATER_HPP__
