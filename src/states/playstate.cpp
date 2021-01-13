
#include "playstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"

State* PlayState::HandleKeyPressed (const sf::Event& event,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* PlayState::HandleTextEntered (const sf::Event& event,
                                     Service& service) {
    
     if (event.text.unicode < 128) {
         auto& scene = service.getScene();
         scene.Modify(event, service);
         return &StateHolder::draw;
     }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::Enter (Service& service) {
    
    auto& window = service.getWindow();
    window.clear(sf::Color::Black);
    
}
