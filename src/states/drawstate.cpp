
#include <spdlog/spdlog.h>

#include "drawstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"
#include "window.h"

State* DrawState::HandleKeyPressed (const sf::Event& event,
                                    polyComponentVector& scenes,
                                    Service& service) {
    
    auto& scene = *(scenes[0]);
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        scene.abort();
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* DrawState::HandleKeyReleased (const sf::Event& event,
                                     polyComponentVector& scenes,
                                     Service& service ) {
    
    spdlog::debug("DrawState::HandleKeyReleased");
    
    auto& scene = *(scenes[0]);
    scene.setActiveEvent(service);
    
    if (scene.isCompleted()) {
        
        if (service.triggerSpecial()) {
            return &StateHolder::special;
        } else if (scene.restartService(service)) {
            return &StateHolder::restart;
        } else {
            return &StateHolder::play;
        }
        
    } else {
        return &StateHolder::wait;
    }
    
}

State* DrawState::Update (polyComponentVector& scenes, Service& service) {
    
    spdlog::debug("DrawState::Update");
    
    auto& scene = *(scenes[0]);
    
    if (scene.update()) {
        scene(service);
        service.getWindow().display();
    }
    
    return nullptr;
}

void DrawState::Enter (polyComponentVector& scenes,
                       Service& service) {
    
    spdlog::info("Entering DrawState");
    
    return;
    
}
