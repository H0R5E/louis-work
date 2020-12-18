
#include "helpers.h"
#include "playstate.h"
#include "game.h"

GameState* PlayState::handleTextEntered (const sf::Event& event, Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::enter (Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.display();
    
}
