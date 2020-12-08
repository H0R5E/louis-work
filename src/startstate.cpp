
#include "helpers.h"
#include "startstate.h"
#include "game.h"

StartState::StartState() {
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    titleFont = GetFont("Monofett-Regular.ttf");
    msgFont = GetFont("JetBrainsMono-Light.ttf");
    
    sf::Text text;
    text.setFont(titleFont); 
    text.setString("Louis' Work");
    text.setCharacterSize(96); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    phrases.push_back(text);
    
    text.setFont(msgFont); 
    text.setString("Ctrl-C to Quit");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 60.0f));
    
    phrases.push_back(text);
    
    text.setFont(msgFont); 
    text.setString("Press Any Key to Start");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 120.0f));
    
    phrases.push_back(std::move(text));
    
}

GameState* StartState::handleKeyPressed (const sf::Event& event,
                                         Game& game) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        game.window.close();
    } else if (!(event.key.code == sf::Keyboard::LControl ||
                 event.key.code == sf::Keyboard::RControl)) {
        return &Game::play;
    }
    
    return nullptr;
    
}

void StartState::update ( Game& game ) {
    
    game.window.clear(sf::Color::Blue);
    
    for (sf::Text text : phrases) {
        game.window.draw(text);
    }
    
    game.window.display();
    
}
