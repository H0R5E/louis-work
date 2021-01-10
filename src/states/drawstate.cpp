
#include "drawstate.h"

#include "service.h"
#include "scene.h"
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
    
    auto scene = service.getScenePtr();
    scene->Modify(service);
    
    if (scene->Ready()) {
        return &StateHolder::play;
    } else {
        return &StateHolder::wait;
    }
    
}

State* DrawState::Update (Service& service) {
    
    auto scene = service.getScenePtr();
    scene->Update(service);
    return nullptr;
    
}
