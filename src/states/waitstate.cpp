
#include "helpers.h"
#include "waitstate.h"
#include "game.h"

State* WaitState::HandleTextEntered (const sf::Event& event, Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    return nullptr;
    
}

State* WaitState::HandleKeyReleased (const sf::Event& event, Game& game) {
    return nullptr;
}

State* WaitState::Update (Game& game) {
    
    if (game.command->IsCompleted())
        return &Game::play;
    
    return nullptr;
    
}
