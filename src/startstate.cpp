
#include "helpers.h"
#include "startstate.h"
#include "game.h"

StartState::StartState() {
    titleFont = GetFont("Monofett-Regular.ttf");
    msgFont = GetFont("JetBrainsMono-Light.ttf");
}

GameState* StartState::HandleTextEntered (const sf::Event& event,
                                          Game& game) {
    
    // Using Ctrl + C to exit
    if (CtrlC()) {
        game.window.close();
    } else {
        return &Game::play;
    }
    
    return nullptr;
    
}

GameState* StartState::HandleKeyReleased (const sf::Event& event,
                                           Game& game ) {
    return nullptr;
}

GameState* StartState::Update (Game& game) {
    return nullptr;
}

void StartState::Enter ( Game& game ) {
    
    game.window.clear(sf::Color::Blue);
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
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
    
    game.window.draw(text);
    
    text.setFont(msgFont); 
    text.setString("Press Any Key to Start");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 80.0f));
    
    game.window.draw(text);
    
    text.setFont(msgFont); 
    text.setString("Press Ctrl-C to Quit");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 120.0f));
    
    game.window.draw(text);
    
    game.window.display();
    
}
