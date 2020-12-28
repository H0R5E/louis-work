
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

template <typename T>
class CommandFactory : public CommandFactoryBase {
public:
    std::unique_ptr<Command> makeCommand () override {
        auto newCommand = myCommand();
        return newCommand;
    }
private:
    fPtrType myCommand {&makeSingleLetterSiren<T>};
};

template <typename T>
std::unique_ptr<Command> makeSingleLetterSiren () {
    auto newCommand = std::make_unique<Command>(
                            std::make_unique<T>(),
                            std::make_unique<SingleLetterDraw>(),
                            std::make_unique<SirenSound>());
    return newCommand;
};
