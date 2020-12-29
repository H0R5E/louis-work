
#include "command.h"

void Command::Execute ( const sf::Event& event, Game& game ) {
    
    if (sound_component) {
        sound_component->start(event, *this, game);
    }
    
    draw_component->start(event, *this, game);
    
}

void Command::Update ( Game& game ) {
    
    draw_component->update(*this, game);
    
    if (sound_component) {
        sound_component->update(*this, game);
    }
    
}

bool Command::Stop () {
    
    auto is_completed = draw_component->isCompleted();
    
    if (sound_component && is_completed) {
        sound_component->stop(*this);
    }
    
    return is_completed;
    
}
