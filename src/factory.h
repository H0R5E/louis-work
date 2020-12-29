
#pragma once

#include <memory>

#include "command.h"

#include "singleletterdraw.h"

#include "sirensound.h"

using fPtrType = std::unique_ptr<Command> (*) ();

// Forward declaration
template <typename T>
std::unique_ptr<Command> makeSingleLetterSiren ();

class CommandFactoryBase {
public:
    virtual std::unique_ptr<Command> makeCommand () = 0;
    virtual ~CommandFactoryBase () = default;
};

template <typename T=SoundAdapter>
class CommandFactory : public CommandFactoryBase {
public:
    CommandFactory () = default;
    CommandFactory (std::unique_ptr<Command>&& command) :
        force_command(std::move(command)) {}
    std::unique_ptr<Command> makeCommand () override {
        if (force_command) {
            return std::move(force_command);
        }
        auto newCommand = myCommand();
        return newCommand;
    }
private:
    std::unique_ptr<Command> force_command;
    fPtrType myCommand {&makeSingleLetterSiren<T>};
};

template <typename T>
std::unique_ptr<Command> makeSingleLetterSiren () {
    return std::make_unique<Command>(std::make_unique<T>(),
                                     std::make_unique<SingleLetterDraw>(),
                                     std::make_unique<SirenSound>());
};
