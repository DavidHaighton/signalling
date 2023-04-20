#pragma once

#include <cadmium/core/modeling/coupled.hpp>
#include "InputSubSystem.h"
#include "LightSubsystem.h"
namespace sim {
    struct CarSim: public cadmium::Coupled {
        CarSim(): Coupled("Car Signal Subsystem") {
            auto input = addComponent<InputSubSystem>();
            auto output = addComponent<LightSubsystem>();
            addCoupling(input->output, output->input);
        }
    };
}
