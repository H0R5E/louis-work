
#include "drawstate.h"

#include "command.h"
#include "stateholder.h"

State* DrawState::HandleKeyPressed (const sf::Event& event,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* DrawState::HandleKeyReleased (const sf::Event& event,
                                     Service& service ) {
    
    auto command = service.getCommandPtr();
    
    if (command->Stop()) {
        return &StateHolder::play;
    } else {
        return &StateHolder::wait;
    }
    
}

State* DrawState::Update (Service& service) {
    
    auto command = service.getCommandPtr();
    command->Update(service);
    return nullptr;
    
}
