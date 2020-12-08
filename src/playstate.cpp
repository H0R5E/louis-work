
#include "playstate.h"
#include "game.h"

GameState* PlayState::handleKeyPressed ( const sf::Event& event, Game& game ) {
    
    // Using Ctrl + C to change state
    if(event.key.control && event.key.code == sf::Keyboard::C)
        return &Game::start;
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::update (Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.display();
    
}
