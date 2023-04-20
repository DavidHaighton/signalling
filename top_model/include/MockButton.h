#pragma once

#include <cadmium/core/modeling/atomic.hpp>
#include <cadmium/core/modeling/port.hpp>
#include <queue>
#include <limits>
#include "CommandMessage.h"
namespace sim{
    struct ButtonState{
        bool isPressed = false;
        std::queue<std::pair<double, bool>> changeTimes;
        explicit ButtonState(const std::queue<std::pair<double, bool>>& changeTimes){
            this->changeTimes = changeTimes;
            isPressed = false;
        }
    };
    std::ostream& operator<<(std::ostream& out, const ButtonState& s) {
        out << (s.isPressed?"Pressed":"Not Pressed");
        return out;
    }
    struct MockButton: public cadmium::Atomic<ButtonState>{
        cadmium::Port<bool> out;
        MockButton(const std::string& id, const std::queue<std::pair<double, bool>>& changeTimes): Atomic<ButtonState>(id, ButtonState(changeTimes))
        {
            out = addOutPort<bool>("out");
        }
        void internalTransition(ButtonState& s) const override {
            if(s.changeTimes.empty()) return;

            s.isPressed = s.changeTimes.front().second;
            s.changeTimes.pop();
        }
        void externalTransition(ButtonState &s, double e) const override {}
        void output(const ButtonState& s) const override {
            if(s.changeTimes.empty()){
                return;
            }
            out->addMessage(s.changeTimes.front().second);
        }
        [[nodiscard]] double timeAdvance(const ButtonState& s) const override {
            if(s.changeTimes.empty()){
                return std::numeric_limits<double>::infinity();
            }
            return s.changeTimes.front().first;
        }
    };
}


