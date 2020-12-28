
#include "playstate.h"
#include "game.h"

State* PlayState::HandleKeyPressed (const sf::Event& event,
                                    Game& game) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &Game::start;
    }
    
    return nullptr;
    
}

State* PlayState::HandleTextEntered (const sf::Event& event,
                                     Game& game) {
    
     if (event.text.unicode < 128) {
         game.command->Execute(event, game);
         return &Game::draw;
     }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::Enter (Game& game) {
    
    game.window->clear(sf::Color::Black);
    game.window->display();
    
}
