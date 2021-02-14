
#include "playstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"
#include "window.h"

#include <iostream>

State* PlayState::HandleKeyPressed (const sf::Event& event,
                                    polyComponentVector& scenes,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    auto& scene = *(scenes[0]);
    
    if (scene.restartKey(event.key)) {
        return &StateHolder::special;
    }
    
    return nullptr;
    
}

State* PlayState::HandleTextEntered (const sf::Event& event,
                                     polyComponentVector& scenes,
                                     Service& service) {
    
    std::cout << "PlayState::HandleTextEntered" << std::endl;
    
    if (event.text.unicode < 128) {
        
        auto& scene = *(scenes[0]);
        
        scene.setActiveEvent(event, service);
        auto convert = static_cast<char>(event.text.unicode);
        service.storeLetter(convert);
        
        auto word = service.getWord();
        return &StateHolder::draw;
        
     }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::Enter (polyComponentVector& scenes,
                       Service& service) {
    
    std::cout << "PlayState::Enter" << std::endl;
    std::cout << "Letters stored: " << service.getWord().size() << std::endl;
    
    (*scenes[0])(service);
    service.getWindow().display();
    
    return;
    
}
