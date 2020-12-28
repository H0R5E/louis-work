
#include "command.h"

void Command::Execute ( const sf::Event& event, Game& game ) {
    
    if (sound_component) {
        sound_component->start(event, *this, game);
    }
    
    draw_component->start(event, *this, game);
    
}

bool Command::Update ( Game& game ) {
    
    bool still_alive = draw_component->update(*this, game);
    
    if (sound_component) {
        if (still_alive) {
            sound_component->update(*this, game);
        } else {
            sound_component->stop(*this);
        }
    }
    
    return still_alive;
    
}
