
#include "helpers.h"
#include "drawstate.h"
#include "game.h"

State* DrawState::HandleKeyPressed (const sf::Event& event,
                                    Game& game) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &Game::start;
    }
    
    return nullptr;
    
}

State* DrawState::HandleKeyReleased ( const sf::Event& event, Game& game ) {
    
    if (game.command->IsCompleted()) {
        return &Game::play;
    } else {
        return &Game::wait;
    }
    
}
