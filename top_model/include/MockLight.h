#pragma once

#include <cadmium/core/modeling/atomic.hpp>
#include <cadmium/core/modeling/port.hpp>
#include <queue>
#include <limits>
#include "CommandMessage.h"
namespace sim{
    struct LightState{
        bool isOn = false;
    };
    std::ostream& operator<<(std::ostream& out, const LightState& s) {
        out << (s.isOn?"ON":"OFF");
        return out;
    }
    struct MockLight: public cadmium::Atomic<LightState>{
        cadmium::Port<bool> in;
        explicit MockLight(const std::string& id): Atomic<LightState>(id, LightState())
        {
            in = addInPort<bool>("Pin In");
        }
        void internalTransition(LightState& s) const override {}
        void externalTransition(LightState &s, double e) const override {
            s.isOn = in->getBag()[0];
        }
        void output(const LightState& s) const override {}
        [[nodiscard]] double timeAdvance(const LightState& s) const override {
            return std::numeric_limits<double>::infinity();
        }
    };
}
