#pragma once
#include <ostream>
#include <sstream>
#include <memory>
namespace sim{
    enum class CommandPacketType{
        LEFT_TURN,
        RIGHT_TURN,
        BRAKE,
        NONE
    };

    std::ostream& operator<<(std::ostream& out, const CommandPacketType& type){
        std::string s;
        switch(type){
            case CommandPacketType::LEFT_TURN:
                s = "LEFT_TURN";
                break;
            case CommandPacketType::RIGHT_TURN:
                s = "RIGHT_TURN";
                break;
            case CommandPacketType::BRAKE:
                s = "BRAKE";
                break;
            default:
                s = "NONE";
        }
        out<<s;
        return out;
    }

    struct CommandPacket{
        CommandPacketType type;
        bool state;
        explicit CommandPacket(CommandPacketType type, bool state){
          this->type = type;
          this->state = state;
        }
        CommandPacket(const CommandPacket& p) = default;
        CommandPacket(CommandPacket& p) = default;
        CommandPacket() = default;

        explicit CommandPacket(const std::shared_ptr<const CommandPacket>* p){
            this->state = p->get()->state;
            this->type = p->get()->type;
        }
        explicit CommandPacket(const std::shared_ptr<const CommandPacket> p){
            this->state = p->state;
            this->type = p->type;
        }
    };
    std::ostream& operator<<(std::ostream& out, const CommandPacket& obj) {
        std::stringstream ss;
        ss <<"{ Type:"<<obj.type<<", State"<<(obj.state?"On":"Off")<<"}";
        out << ss.str();
        return out;
    }
}