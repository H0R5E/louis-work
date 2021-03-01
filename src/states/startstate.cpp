
#include <spdlog/spdlog.h>

#include "startstate.h"

#include "service.h"
#include "stateholder.h"
#include "window.h"

State* StartState::HandleKeyPressed (const sf::Event& event,
                                     polyComponentVector& scenes,
                                     Service& service) {
    
    spdlog::get("main_logger")->debug("StartState::HandleKeyPressed");
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        auto& window = service.getWindow();
        window.close();
    }
    
    return nullptr;
    
}

State* StartState::HandleTextEntered (const sf::Event& event,
                                      polyComponentVector& scenes,
                                      Service& service) {
    
    spdlog::get("main_logger")->debug("StartState::HandleTextEntered");
    
    auto& scene = *(scenes[0]);
    scene.abort();
    
    auto new_scene = service.makeScenePValue();
    scenes.push_back(std::move(new_scene));
    service.clearLetters();
    return &StateHolder::play;
    
}

State* StartState::Update (polyComponentVector& scenes,
                           Service& service) {
    skipEvents = false;
    return nullptr;
}

void StartState::Enter (polyComponentVector& scenes,
                        Service& service) {
    
    skipEvents = true;
    
    auto& window = service.getWindow();
    window.clear(sf::Color::Blue);
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& title_font = service.getFont("Monofett-Regular");
    auto& menu_font = service.getFont("JetBrainsMono-Light");
    
    text.setFont(title_font); 
    text.setString("Louis' Work");
    text.setCharacterSize(96); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    window.draw(text);
    
    text.setFont(menu_font); 
    text.setString("Press Any Key to Start");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 80.0f));
    
    window.draw(text);
    
    text.setString("Press Ctrl-C to Quit");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 120.0f));
    
    window.draw(text);
    window.display();
    
    spdlog::get("main_logger")->info("Entering StartState");
    
    return;
    
}
