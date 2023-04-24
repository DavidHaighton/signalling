#pragma once
#include <limits>
#include <queue>
#include <cadmium/core/modeling/atomic.hpp>
#include <cadmium/core/modeling/port.hpp>
#include "CommandMessage.h"
#include "LightController.h"
namespace sim{
    enum class Turning {RIGHT, LEFT, NONE};
    struct LightMultiplexState{
        Turning direction = Turning::NONE;
        bool isBraking = false;
        bool intTransition = false;
    };

    std::ostream& operator<<(std::ostream& out, const LightMultiplexState& s) {
       out << "{ isBraking:"<<(s.isBraking?"True":"False")<<" Left: "<<(s.direction==Turning::LEFT?"T":"F");
       out << " Right: " << (s.direction==Turning::RIGHT?"T":"F");
        return out;
    }
    struct LightMux: public cadmium::Atomic<LightMultiplexState>{
        cadmium::Port<Mode> frontLeftPort, frontRightPort, backLeftPort, backRightPort;
        cadmium::Port<CommandPacket> in;
        LightMux(): Atomic<LightMultiplexState>("Light Mux", LightMultiplexState()){
            in = addInPort<CommandPacket>("IN PORT");
            frontLeftPort = addOutPort<Mode>("FRONT LEFT OUT");
            frontRightPort= addOutPort<Mode>("FRONT RIGHT OUT");
            backLeftPort= addOutPort<Mode>("BACK LEFT OUT");
            backRightPort = addOutPort<Mode>("BACK RIGHT OUT");
        }

        void internalTransition(LightMultiplexState& s) const override {
            s.intTransition = true;
        }

        void externalTransition(LightMultiplexState &s, double e) const override {
            auto message = in->getBag().front();
            s.intTransition = false;
            if(message.type == CommandPacketType::RIGHT_TURN){
                s.direction = message.state?Turning::RIGHT:Turning::NONE;
            }
            else if(message.type == CommandPacketType::LEFT_TURN){
                s.direction = message.state?Turning::LEFT:Turning::NONE;
            }else if(message.type == CommandPacketType::BRAKE){
                s.isBraking = message.state;
            }
        }

        void output(const LightMultiplexState& s) const override {
            if(s.isBraking){
                switch(s.direction){
                    case Turning::LEFT:
                        frontLeftPort->addMessage(Mode::BLINKING);
                        frontRightPort->addMessage(Mode::OFF);
                        backLeftPort->addMessage(Mode::ON);
                        backRightPort->addMessage(Mode::ON);
                        break;
                    case Turning::RIGHT:
                        frontLeftPort->addMessage(Mode::OFF);
                        frontRightPort->addMessage(Mode::BLINKING);
                        backLeftPort->addMessage(Mode::ON);
                        backRightPort->addMessage(Mode::ON);
                        break;
                    default:
                        frontLeftPort->addMessage(Mode::OFF);
                        frontRightPort->addMessage(Mode::OFF);
                        backLeftPort->addMessage(Mode::ON);
                        backRightPort->addMessage(Mode::ON);
                        break;
                }
            } else {
                switch(s.direction){
                    case Turning::LEFT:
                        frontLeftPort->addMessage(Mode::BLINKING);
                        frontRightPort->addMessage(Mode::OFF);
                        backLeftPort->addMessage(Mode::BLINKING);
                        backRightPort->addMessage(Mode::OFF);
                        break;
                    case Turning::RIGHT:
                        frontLeftPort->addMessage(Mode::OFF);
                        frontRightPort->addMessage(Mode::BLINKING);
                        backLeftPort->addMessage(Mode::OFF);
                        backRightPort->addMessage(Mode::BLINKING);
                        break;
                    default:
                        frontLeftPort->addMessage(Mode::OFF);
                        frontRightPort->addMessage(Mode::OFF);
                        backLeftPort->addMessage(Mode::OFF);
                        backRightPort->addMessage(Mode::OFF);
                        break;
                }
            }
        }

        [[nodiscard]] double timeAdvance(const LightMultiplexState& s) const override {
            return s.intTransition?std::numeric_limits<double>::infinity():0.01;
        }

    };
}
