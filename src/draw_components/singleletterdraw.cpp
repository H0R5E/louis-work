
#include "singleletterdraw.h"
#include "command.h"
#include "game.h"

void SingleLetterDraw::start (const sf::Event& event,
                              Command& command,
                              Game& game ) {
    
    char letter {static_cast<char>(event.text.unicode)};
        
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& letter_font = game.font_holder.Get("JetBrainsMono-Light");
    
    text.setFont(letter_font); 
    text.setString(letter);
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    game.window->clear(sf::Color::Black);
    game.window->draw(text);
    game.window->display();
    
    clock.restart();
    
}

bool SingleLetterDraw::update (Command& command, Game& game) {
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return true;
        
    return false;
    
}


