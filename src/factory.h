
#pragma once

#include <memory>

#include "command.h"


using fPtrType = std::unique_ptr<Command> (*) ();

// Forward declaration
std::unique_ptr<Command> makeSingleLetterSiren ();
std::unique_ptr<Command> makeSingleLetterSpoken ();

class CommandFactory {
public:
    CommandFactory () = default;
    CommandFactory (std::unique_ptr<Command>&& command) :
        force_command(std::move(command)) {}
    std::unique_ptr<Command> makeCommand () {
        if (force_command) {
            return std::move(force_command);
        }
        auto newCommand = myCommand();
        return newCommand;
    }
private:
    std::unique_ptr<Command> force_command;
    fPtrType myCommand {&makeSingleLetterSpoken};
};
