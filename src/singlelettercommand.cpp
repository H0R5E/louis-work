
#include "singlelettercommand.h"
#include "helpers.h"
#include "game.h"

SingleLetterCommand::SingleLetterCommand() {
    font = GetFont("JetBrainsMono-Light.ttf");
}

void SingleLetterCommand::execute ( const sf::Event& event, Game& game ) {
    
    char letter;
    
    if (event.text.unicode < 128) {
        letter = static_cast<char>(event.text.unicode);
    } else {
        return;
    }
    
    game.window.clear(sf::Color::Blue);
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    text.setFont(font); 
    text.setString(letter);
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    game.window.clear(sf::Color::Black);
    game.window.draw(text);
    game.window.display();
    
}

