
#include "game.h"

StartState Game::start {};
PlayState Game::play {};
DrawState Game::draw {};
WaitState Game::wait {};

Game::Game() {
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    // Load resources
    font_holder.Load("Monofett-Regular");
    font_holder.Load("JetBrainsMono-Light");
    buffer_holder.Load("Alarm_or_siren");
    
    window.create(sf::VideoMode(width, height),
                  "Louis' Work",
                  sf::Style::Fullscreen);
    
    current_state = &Game::start;
    current_state->Enter(*this);
    
}

void Game::EventLoop() {
    
    State* check_state;
    constexpr float fps = 1.f / 60.f;
    
    while ( window.isOpen() ) {
        
        sf::Event event;
        
        // while there are pending events...
        while (window.pollEvent(event)) {
        
            // check the type of the event...
            switch (event.type) {
                
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
