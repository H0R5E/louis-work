
#include "playstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"
#include "window.h"

#include <iostream>

State* PlayState::HandleKeyPressed (const sf::Event& event,
                                    Component& scene,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* PlayState::HandleTextEntered (const sf::Event& event,
                                     Component& scene,
                                     Service& service) {
    
    std::cout << "PlayState::HandleTextEntered" << std::endl;
    
     if (event.text.unicode < 128) {
         scene.setActiveEvent(event, service);
         auto convert = static_cast<char>(event.text.unicode);
         service.storeLetter(convert);
         return &StateHolder::draw;
     }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

std::unique_ptr<Component> PlayState::Enter (Component* scene,
                                             Service& service) {
    
    std::cout << "PlayState::Enter" << std::endl;
    std::cout << service.getLetters().size() << std::endl;
    
    std::unique_ptr<Component> new_scene {nullptr};
    
    if (!scene) {
        new_scene = service.makeScenePtr();
        (*new_scene)(service);
    } else {
        (*scene)(service);
    }
   
    service.getWindow().display();
    
    return new_scene;
    
}
