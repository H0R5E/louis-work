
#include "helpers.h"
#include "game.h"
#include "waitstate.h"

GameState* WaitState::HandleTextEntered (const sf::Event& event, Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    return nullptr;
    
}

GameState* WaitState::HandleKeyReleased (const sf::Event& event, Game& game) {
    return nullptr;
}

GameState * WaitState::Update (Game& game) {
    
    if (game.command->IsCompleted())
        return &Game::play;
    
    return nullptr;
    
}
