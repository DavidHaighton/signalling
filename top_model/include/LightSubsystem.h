#pragma once

#include <cadmium/core/modeling/coupled.hpp>
#include <queue>
#include "LightMultiplexer.h"
#include "LightSubsystem.h"
#include "LightController.h"
#include "MockLight.h"
#include "CommandMessage.h"
namespace sim {
    struct LightSubsystem: public cadmium::Coupled {
        cadmium::Port<CommandPacket> input;
        LightSubsystem(): Coupled("Light Signal Subsystem") {
            input = addInPort<CommandPacket>("InPort");
            auto frontLeftController = addComponent<LightController>("FRONT_LEFT_CONTROLLER"),
                    frontRightController = addComponent<LightController>("FRONT_RIGHT_CONTROLLER"),
                    backLeftController = addComponent<LightController>("BACK_LEFT_CONTROLLER"),
                    backRightController = addComponent<LightController>("BACK_RIGHT_CONTROLLER");
            auto frontLeft = addComponent<MockLight>("FL LED"),
                    frontRight = addComponent<MockLight>("FR LED"),
                    backLeft = addComponent<MockLight>("BL LED"),
                    backRight = addComponent<MockLight>("BR LED");
            auto mux = addComponent<LightMux>();
            addCoupling(input, mux->in);
            addCoupling(mux->frontLeftPort, frontLeftController->in);
            addCoupling(frontLeftController->out, frontLeft->in);
            addCoupling(mux->frontRightPort, frontRightController->in);
            addCoupling(frontRightController->out, frontRight->in);

            addCoupling(mux->backLeftPort, backLeftController->in);
            addCoupling(backLeftController->out, backLeft->in);

            //addCoupling(mux->backRightPort, backRightController->in);
            //addCoupling(backRightController->out, backRight->in);
        }
    };
}
