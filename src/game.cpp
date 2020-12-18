
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
    current_state->enter(*this);
    
}

void Game::EventLoop() {
    
    GameState* check_state;
    
    while ( window.isOpen() ) {
        
        sf::Event event;
        
        // while there are pending events...
        while (window.pollEvent(event)) {
        
            // check the type of the event...
            switch (event.type) {
                
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                
                // catch 
                case sf::Event::TextEntered:
                    
                    check_state = current_state->handleTextEntered(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->enter(*this);
                    }
                    
                    break;
                
                // we don't process other types of events
                default:
                    break;
                
            }
            
        }
        
        float fps = 1.f / 60.f;
        sf::sleep(sf::seconds(fps));
        
    }
    
}
