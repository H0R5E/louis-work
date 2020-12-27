
#pragma once

#include <memory>

#include "command.h"
#include "singlelettercommand.h"

template <typename T>
std::unique_ptr<Command> CommandFactory () {
    
    auto newCommand = std::make_unique<SingleLetterCommand>(
                                                    std::make_unique<T>());
    return std::move(newCommand);
    
}

