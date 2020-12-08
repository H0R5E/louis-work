
#include "game.h"

StartState Game::start {};
PlayState Game::play {};

Game::Game() {
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    window.create(sf::VideoMode(width, height),
                  "Louis' Work",
                  sf::Style::Fullscreen);
    
    current_state = &Game::start;
    
}

void Game::EventLoop() {
    
    GameState* check_state;
    
    while ( this->window.isOpen() ) {
        
        sf::Event event;
        
        // while there are pending events...
        while (this->window.pollEvent(event)) {
        
            // check the type of the event...
            switch (event.type) {
                
                // window closed
                case sf::Event::Closed:
                    this->window.close();
                    break;
                
                // catch 
                case sf::Event::KeyPressed:
                    
                    check_state = this->current_state->handleKeyPressed(event,
                                                                        *this);
                    
                    if (check_state) {
                        this->current_state = check_state;
                    }
                    
                    break;
                
                // we don't process other types of events
                default:
                    break;
                
            }
            
        }
        
        this->current_state->update(*this);
        
    }
    
}
