
#include "typewriterdraw.h"
#include "service.h"
#include "window.h"

#include <iostream>

void TypeWriterDraw::init ( Service& service ) {
    
    std::cout << "TypeWriterDraw::init" << std::endl;
    auto& letter_font = service.getFont("JetBrainsMono-Light");
    text.setFont(letter_font);
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
}

void TypeWriterDraw::setActiveEvent (const sf::Event& event,
                                     Service& service) {
    
    std::cout << "TypeWriterDraw::setActiveEvent" << std::endl;
    auto convert = static_cast<char>(event.text.unicode);
    active_letter = std::make_unique<char>(convert);
    force_draw = true;
    
}

void TypeWriterDraw::setActiveEvent(Service& service) {
    active_letter = nullptr;
}

bool TypeWriterDraw::update() {
    
    std::cout << "TypeWriterDraw::update" << std::endl;
    
    // no active letter
    if (!active_letter) {
        return false;
    }
    
    char letter_copy {*active_letter};
    
    // new letter added
    if (force_draw) {
        add_letter(letter_copy);
        force_draw = false;
        return true;
    }
    
    // Add letter after time
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return false;
    
    add_letter(letter_copy);
    
    return true;
}

bool TypeWriterDraw::isCompleted () {
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return false;
    
    return true;
    
}

void TypeWriterDraw::operator() ( Service& service ) {
    
    std::cout << "TypeWriterDraw::draw" << std::endl;
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    std::cout << "Letters drawn: " << draw_letters.size() << std::endl;
    
    if (draw_letters.size() == 0) {
        return;
    }
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    text.setString(draw_letters);
    
    // center text
    sf::FloatRect textRect = text.getLocalBounds();
    
    if (!yorigin || reset_yorigin) {
        yorigin = std::make_unique<float>(textRect.top +
                                                        textRect.height / 2.0f);
        reset_yorigin = false;
    }
    
    text.setOrigin(textRect.left + textRect.width / 2.0f, *yorigin);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    auto& window = service.getWindow();
    window.draw(text);
    std::cout << "Drawing: " <<
        static_cast<std::string>(text.getString()) << std::endl;
    
}

void TypeWriterDraw::add_letter(const char& letter) {
    
    std::cout << "TypeWriterDraw::add_letter" << std::endl;
    
    auto width = sf::VideoMode::getDesktopMode().width;
    
    auto check_sentence = draw_letters + letter;
    text.setString(check_sentence);
    
    sf::FloatRect textRect = text.getLocalBounds();
    
    if (textRect.width > width) {
        draw_letters += "\n";
        reset_yorigin = true;
    }
    
    draw_letters += letter;
    
}
