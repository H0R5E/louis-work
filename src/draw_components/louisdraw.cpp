
#include "louisdraw.h"
#include "service.h"
#include "window.h"

#include <iostream>

bool LouisDraw::update() {
    
    auto elapsed = clock.getElapsedTime();
    
    std::cout << "elapsed: " << elapsed.asSeconds() << std::endl;
    
    if (elapsed.asSeconds() < 0.5f) {
        return false;
    } else if (!draw_it) {
        draw_it = true;
        return true;
    }
    
    return false;
    
}

bool LouisDraw::isCompleted () {
    
    std::cout << "LouisDraw::isCompleted" << std::endl;
    
    if (aborted) {
        return true;
    }
    
    auto elapsed = clock.getElapsedTime();
    
    std::cout << "elapsed: " << elapsed.asSeconds() << std::endl;
    
    if (elapsed.asSeconds() < 5.0f)
        return false;
    
    return true;
    
}

void LouisDraw::abort () {
    aborted = true;
}

void LouisDraw::operator() (Service& service) {
    
    std::cout << "LouisDraw::operator()" << std::endl;
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!draw_it) {
        return;
    }
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& letter_font = service.getFont("JetBrainsMono-Light");
    
    text.setFont(letter_font); 
    text.setString("LOUIS");
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    auto& window = service.getWindow();
    window.draw(text);
    
    clock.restart();
    
}
