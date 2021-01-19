
#include "singleletterdraw.h"
#include "service.h"
#include "window.h"

void SingleLetterDraw::setActiveEvent(const sf::Event& event,
                                      Service& service) {
    
    auto convert = static_cast<char>(event.text.unicode);
    letter = std::make_unique<char>(convert);
    should_draw = true;
    
}

void SingleLetterDraw::setActiveEvent(Service& service) {
    letter = nullptr;
}

bool SingleLetterDraw::update() {
    return should_draw;
}

bool SingleLetterDraw::isCompleted () {
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return false;
    
    return true;
    
}

void SingleLetterDraw::operator() (Service& service) {
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!letter) {
        return;
    }
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& letter_font = service.getFont("JetBrainsMono-Light");
    
    text.setFont(letter_font); 
    text.setString(*letter);
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    auto& window = service.getWindow();
    window.clear(sf::Color::Black);
    window.draw(text);
    
    clock.restart();
    should_draw = false;
    
}
