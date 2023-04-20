#pragma once

#include <cadmium/core/modeling/atomic.hpp>
#include <cadmium/core/modeling/port.hpp>
#include <queue>
#include <limits>
#include "CommandMessage.h"
namespace sim{
    enum class Mode {OFF, BLINKING, ON};
    struct ControllerState{
        bool signal = false;
        bool interalTransitionCalled = false;
        Mode current = Mode::OFF;
    };
    std::ostream& operator<<(std::ostream& out, const Mode& m){
        std::string output;
        switch(m){
            case Mode::BLINKING:
                output = "BLINKING";
                break;
            case Mode::ON:
                output = "ON";
                break;
            default:
                output = "OFF";
                break;
        }
        out << output;
        return out;
    }
    std::ostream& operator<<(std::ostream& out, const ControllerState& s) {
        out << "{ Current State:" << s.current <<"}";
        return out;
    }
    struct LightController: public cadmium::Atomic<ControllerState>{
        cadmium::Port<Mode> in;
        cadmium::Port<bool> out;
        explicit LightController(const std::string& id): Atomic<ControllerState>(id, ControllerState())
        {
            in = addInPort<Mode>("Mode Input");
            out = addOutPort<bool>("Signal Out");
        }
        void internalTransition(ControllerState& s) const override {
            if(s.current == Mode::BLINKING){
                s.signal = !s.signal;
            }
            s.interalTransitionCalled = true;
        }
        void externalTransition(ControllerState &s, double e) const override {
            s.current = in->getBag()[0];
            s.signal = s.current == Mode::ON || s.current == Mode::BLINKING;
            s.interalTransitionCalled = false;
        }
        void output(const ControllerState& s) const override {
            out->addMessage(s.signal);
        }
        [[nodiscard]] double timeAdvance(const ControllerState& s) const override {
            if(!s.interalTransitionCalled){ return 0.001; } //trigger internal transition so we get output
            if(s.current == Mode::ON || s.current == Mode::OFF)
                return std::numeric_limits<double>::infinity();
            return 0.5; // blinks every 0.5s
        }
    };
}
