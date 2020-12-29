
#include "waitstate.h"
#include "game.h"

State* WaitState::HandleKeyPressed (const sf::Event& event,
                                     Game& game) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &Game::start;
    }
    
    return nullptr;
    
}

State* WaitState::Update (Game& game) {
    
    if (game.command->Stop()) {
        return &Game::play;
    } else {
        game.command->Update(game);
    }
    
    return nullptr;
    
}
