
#include "waitstate.h"

#include "command.h"
#include "service.h"
#include "stateholder.h"

State* WaitState::HandleKeyPressed (const sf::Event& event,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* WaitState::Update (Service& service) {
    
    auto command = service.getCommandPtr();
    
    if (command->Stop()) {
        return &StateHolder::play;
    } else {
        command->Update(service);
    }
    
    return nullptr;
    
}
