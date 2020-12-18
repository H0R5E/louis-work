
#include "helpers.h"
#include "playstate.h"
#include "game.h"
#include "singlelettercommand.h"

PlayState::PlayState() {
    command = std::make_unique<SingleLetterCommand>();
}

GameState* PlayState::handleTextEntered (const sf::Event& event, Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    command->execute(event, game);
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::enter (Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.display();
    
}
