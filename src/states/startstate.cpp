
#include "helpers.h"
#include "startstate.h"
#include "game.h"

State* StartState::HandleKeyPressed (const sf::Event& event,
                                     Game& game) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        game.window->close();
    }
    
    return nullptr;
    
}

State* StartState::HandleTextEntered (const sf::Event& event,
                                      Game& game) {
    
    // Avoid CtrlC
    return &Game::play;
    
}

void StartState::Enter ( Game& game ) {
    
    skipEvents = true;
    
    game.window->clear(sf::Color::Blue);
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& title_font = game.font_holder.Get("Monofett-Regular");
    auto& menu_font = game.font_holder.Get("JetBrainsMono-Light");
    
    text.setFont(title_font); 
    text.setString("Louis' Work");
    text.setCharacterSize(96); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    game.window->draw(text);
    
    text.setFont(menu_font); 
    text.setString("Press Any Key to Start");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 80.0f));
    
    game.window->draw(text);
    
    text.setString("Press Ctrl-C to Quit");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 120.0f));
    
    game.window->draw(text);
    
    game.window->display();
    
}

State * StartState::Update ( Game& game ) {
    skipEvents = false;
    return nullptr;
}

