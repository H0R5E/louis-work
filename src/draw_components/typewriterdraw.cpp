
#include <sstream>

#include "typewriterdraw.h"

void TypeWriterDraw::set_active_event (const sf::Event& event,
                                       Service& service) {
    
    auto convert = static_cast<char>(event.text.unicode);
    active_letter = std::make_unique<char>(convert);
    force_draw = true;
    
}

void TypeWriterDraw::set_active_event(Service& service) {
    active_letter = nullptr;
}

void TypeWriterDraw::draw ( Service& service ) {
    
    if (draw_letters.size() == 0) {
        return;
    }
    
    std::ostringstream sentence;
    for (auto const& cptr: draw_letters) {
        sentence << cptr;
    }
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& letter_font = service.getFont("JetBrainsMono-Light");
    
    text.setFont(letter_font); 
    text.setString(sentence.str());
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
    
}

bool TypeWriterDraw::redraw() {
    
    // no active letter
    if (!active_letter) {
        return false;
    }
    
    // new letter added
    if (force_draw) {
        char letter_copy = *active_letter;
        draw_letters.push_back(letter_copy);
        force_draw = false;
        return true;
    }
    
    // Add letter after time
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return false;
    
    char letter_copy = *active_letter;
    draw_letters.push_back(letter_copy);
    
    return true;
}

bool TypeWriterDraw::isCompleted () {
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return false;
    
    return true;
    
}
