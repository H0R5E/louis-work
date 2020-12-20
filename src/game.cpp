
#include "game.h"
#include "singlelettercommand.h"

StartState Game::start {};
PlayState Game::play {};
DrawState Game::draw {};
WaitState Game::wait {};

Game::Game() {
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    window.create(sf::VideoMode(width, height),
                  "Louis' Work",
                  sf::Style::Fullscreen);
    
    command = std::make_unique<SingleLetterCommand>();
    
    current_state = &Game::start;
    current_state->Enter(*this);
    
}

void Game::EventLoop() {
    
    GameState* check_state;
    constexpr float fps = 1.f / 60.f;
    
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
                    
                    check_state = current_state->HandleTextEntered(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
                    }
                    
                    break;
                
                case sf::Event::KeyReleased:
                    
                    check_state = current_state->HandleKeyReleased(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
                    }
                
                // we don't process other types of events
                default:
                    break;
                
            }
            
        }
        
        check_state = current_state->Update(*this);
        
        if (check_state) {
            current_state = check_state;
            current_state->Enter(*this);
        }
        
        sf::sleep(sf::seconds(fps));
        
    }
    
}
