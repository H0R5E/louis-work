
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "windowstate.h"
#include "startstate.h"

int main() {
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    std::unique_ptr<WindowState> state = std::make_unique<StartState>();
    
    sf::RenderWindow window (sf::VideoMode(width, height),
                             "Louis' Work",
                             sf::Style::Fullscreen);
    
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
                case sf::Event::KeyPressed:
                    
                    try {
                        state->handleKeyPressed(event, window);
                    } catch (const std::runtime_error& e) {
                         std::cout << "Caught " << e.what();
                         return 1;
                    }
                    
                    break;
                
                // we don't process other types of events
                default:
                    break;
                
            }
            
        }
        
        state->update(window);
        
    }
    
    return 0;
    
}
