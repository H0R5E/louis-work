
#include <filesystem>
#include <stdexcept>

#include "pathconfig.h"
#include "startstate.h"

namespace fs = std::filesystem;

StartState::StartState() {
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    fs::path dir (ASSETS_DIR);
    fs::path file ("Monofett-Regular.ttf");
    fs::path full_path = dir / file;
    
    if (!font.loadFromFile(full_path)) {
        throw std::runtime_error("Fonts failed to load");
    }
    
    // select the font
    text.setFont(font); // font is a sf::Font
    
    // set the string to display
    text.setString("Louis' Work");
    
    // set the character size
    text.setCharacterSize(96); // in pixels, not points!
    
    // set the color
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
}

std::unique_ptr<WindowState> StartState::handleKeyPressed ( 
                                    const sf::Event& event,
                                    sf::RenderWindow& window ) {
    
    // Using Ctrl + C to exit
    if(event.key.control && event.key.code == sf::Keyboard::C)
        window.close();
    
    // Just return null for now as not yet transitioning states
    return std::unique_ptr<WindowState> {};
    
}

void StartState::update (sf::RenderWindow& window) {
    window.clear(sf::Color::Blue);
    window.draw(text);
    window.display();
}
