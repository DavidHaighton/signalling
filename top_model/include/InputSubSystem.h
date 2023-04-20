#pragma once

#include <cadmium/core/modeling/coupled.hpp>
#include <queue>
#include "InputDemux.h"
#include "CommandMessage.h"
#include "MockButton.h"
namespace sim {
    struct InputSubSystem: public cadmium::Coupled {
        cadmium::Port<CommandPacket> output;
        InputSubSystem(): Coupled("Button Signal Subsystem") {
            auto brakeQ = std::queue<std::pair<double,bool>>();
            brakeQ.emplace(1, true);
            brakeQ.emplace(10,false);
            auto leftQ= std::queue<std::pair<double,bool>>();
            leftQ.emplace(1, true);
            leftQ.emplace(30, false);
            auto brakes = addComponent<MockButton>("Brake Button", brakeQ);
            auto left = addComponent<MockButton>("Left Turn Button", leftQ);
            auto right = addComponent<MockButton>("Right Turn Button", std::queue<std::pair<double,bool>>());
            auto controller = addComponent<InputDemux>();

            output = addOutPort<CommandPacket>("Output");

            addCoupling(brakes->out, controller->brakePort);
            addCoupling(left->out, controller->leftPort);
            addCoupling(right->out, controller->rightPort);
            addCoupling(controller->out, output);

        }
    };
}
