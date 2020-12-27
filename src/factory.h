
#pragma once

#include <memory>

#include "command.h"
#include "singlelettercommand.h"

class CommandFactoryBase {
public:
    virtual std::unique_ptr<Command> makeCommand () = 0;
    virtual ~CommandFactoryBase () = default;
};

template <typename T>
class CommandFactory : public CommandFactoryBase {
public:
    std::unique_ptr<Command> makeCommand () override {
        auto newCommand = std::make_unique<SingleLetterCommand>(
                                                        std::make_unique<T>());
        return newCommand;
    }
};

