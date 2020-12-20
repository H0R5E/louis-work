
#include "helpers.h"
#include "game.h"
#include "drawstate.h"

GameState* DrawState::HandleTextEntered (const sf::Event& event, Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

GameState* DrawState::HandleKeyReleased ( const sf::Event& event, Game& game ) {
    
    if (game.command->IsCompleted()) {
        return &Game::play;
    } else {
        return &Game::wait;
    }
    
}

GameState * DrawState::Update (Game& game) {
    return nullptr;
}

