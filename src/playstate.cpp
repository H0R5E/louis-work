
#include "helpers.h"
#include "playstate.h"
#include "game.h"

GameState* PlayState::HandleTextEntered (const sf::Event& event,
                                         Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    if (event.text.unicode < 128) {
        game.command->Execute(event, game);
        return &Game::draw;
    }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

GameState* PlayState::HandleKeyReleased (const sf::Event& event,
                                         Game& game) {
    return nullptr;
}

GameState* PlayState::Update (Game& game) {
    return nullptr;
}

void PlayState::Enter (Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.display();
    
}
