
#include "helpers.h"
#include "game.h"
#include "drawstate.h"

State* DrawState::HandleTextEntered (const sf::Event& event, Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

State* DrawState::HandleKeyReleased ( const sf::Event& event, Game& game ) {
    
    if (game.command->IsCompleted()) {
        return &Game::play;
    } else {
        return &Game::wait;
    }
    
}

State * DrawState::Update (Game& game) {
    return nullptr;
}
