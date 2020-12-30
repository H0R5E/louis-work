
#include "command.h"

void Command::Execute ( const sf::Event& event, Service& service ) {
    
    if (sound_component) {
        sound_component->start(event, service);
    }
    
    draw_component->start(event, service);
    
}

void Command::Update ( Service& service ) {
    
    draw_component->update(service);
    
    if (sound_component) {
        sound_component->update(service);
    }
    
}

bool Command::Stop () {
    
    auto is_completed = draw_component->isCompleted();
    
    if (sound_component && is_completed) {
        sound_component->stop();
    }
    
    return is_completed;
    
}
