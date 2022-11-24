#ifndef _BLINKY_HPP__
#define _BLINKY_HPP__

#include <cadmium/core/modeling/atomic.hpp>
#ifndef NO_LOGGING
	#include <iostream>
#endif

namespace cadmium::blinkySystem {
	//! Class for representing the Processor DEVS model state.struct BlinkyState {
	struct BlinkyState {
		double sigma;
		bool lightOn;
		bool fastToggle;
		//! Processor state constructor. By default, the processor is idling.
		BlinkyState(): sigma(0), lightOn(false), fastToggle(false)  {}
	};
#ifndef NO_LOGGING
	/**
	 * Insertion operator for ProcessorState objects. It only displays the value of sigma.
	 * @param out output stream.
	 * @param s state to be represented in the output stream.
	 * @return output stream with sigma already inserted.
	 */
	std::ostream& operator<<(std::ostream &out, const BlinkyState& state) {
		out << "Status:, " << state.lightOn;
		return out;
	}
#endif

	//! Atomic DEVS model of a Job processor.
	class Blinky : public Atomic<BlinkyState> {
	 private:
		
	 public:
		Port<bool> out;  
		Port<bool> in;  
		double slowToggleTime;  
		double fastToggleTime;

		/**
		 * Constructor function.
		 * @param id ID of the new Processor model object.
		 */
		Blinky(const std::string& id): Atomic<BlinkyState>(id, BlinkyState()) {
			out = addOutPort<bool>("out");
			in  = addInPort<bool>("in");
			slowToggleTime = 0.75;  
			fastToggleTime = 0.25;
			state.sigma = fastToggleTime;
			printf("[blinky] init function\n");
		}

		/**
		 * It updates the ProcessorState::clock, clears the ProcessorState::Job being processed, and passivates.
		 * @param state reference to the current state of the model.
		 */
		void internalTransition(BlinkyState& state) const override {
			state.lightOn = !state.lightOn;
		}

		/**
		 * Updates ProcessorState::clock and ProcessorState::sigma.
		 * If it is idling and gets a new Job via the Processor::inGenerated port, it starts processing it.
		 * @param state reference to the current model state.
		 * @param e time elapsed since the last state transition function was triggered.
		 * @param x reference to the model input port set.
		 */
		void externalTransition(BlinkyState& state, double e) const override {

			if(!in->empty()){
				for( const auto x : in->getBag()){
					state.fastToggle = (x==0);
				}

				if(state.fastToggle)
					state.sigma = fastToggleTime;
				else
					state.sigma = slowToggleTime;
			}
		}

		/**
		 * It outputs the already processed ProcessorState::Job via the Processor::outProcessed port.
		 * @param state reference to the current model state.
		 * @param y reference to the atomic model output port set.
		 */
		void output(const BlinkyState& state) const override {	
			// bool out;
			// out = (state.lightOn ? 1 : 0);
			out->addMessage(state.lightOn);	
		}

		/**
		 * It returns the value of ProcessorState::sigma.
		 * @param state reference to the current model state.
		 * @return the sigma value.
		 */
		[[nodiscard]] double timeAdvance(const BlinkyState& state) const override {
			return state.sigma;
		}
	};
}  //namespace cadmium::example::covidSupervisorySystem

#endif //_BLINKY_HPP__
