
#include "helpers.h"
#include "playstate.h"
#include "singlelettercommand.h"
#include "game.h"

State* PlayState::HandleTextEntered (const sf::Event& event,
                                         Game& game) {
    
    // Using Ctrl + C to change state
    if (CtrlC()) {
        return &Game::start;
    }
    
    if (event.text.unicode < 128) {
        if (!game.command) {
            game.command = std::make_unique<SingleLetterCommand>();
        }
        game.command->Execute(event, game);
        return &Game::draw;
    }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

State* PlayState::HandleKeyReleased (const sf::Event& event,
                                         Game& game) {
    return nullptr;
}

State* PlayState::Update (Game& game) {
    return nullptr;
}

void PlayState::Enter (Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.display();
    
}
