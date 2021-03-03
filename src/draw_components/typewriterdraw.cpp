
#include <sstream>
#include <spdlog/spdlog.h>

#include "typewriterdraw.h"
#include "service.h"
#include "window.h"

TypeWriterDraw::TypeWriterDraw (const TypeWriterDraw& copy) :
            DrawComponent(copy) {
    init_copy(copy);
}

void TypeWriterDraw::init ( Service& service ) {
    
    spdlog::debug("TypeWriterDraw::init");
    auto& letter_font = service.getFont("JetBrainsMono-Light");
    text.setFont(letter_font);
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(foreground);
    
}

void TypeWriterDraw::init_copy ( const TypeWriterDraw& copy ) {
    
    if (copy.active_letter) {
        active_letter = std::make_unique<char>(*copy.active_letter);
    }
    
    if (copy.yorigin) {
        yorigin = std::make_unique<float>(*copy.yorigin);
    }
    
    text = copy.text;
    draw_letters = copy.draw_letters;
    force_draw = copy.force_draw;
    reset_yorigin = copy.reset_yorigin;
    aborted = copy.aborted;
    
}


void TypeWriterDraw::setActiveEvent (const sf::Event& event,
                                     Service& service) {
    
    spdlog::debug("TypeWriterDraw::setActiveEvent");
    auto convert = static_cast<char>(event.text.unicode);
    active_letter = std::make_unique<char>(convert);
    force_draw = true;
    
}

void TypeWriterDraw::setActiveEvent(Service& service) {
    active_letter = nullptr;
}

bool TypeWriterDraw::update() {
    
    spdlog::debug("TypeWriterDraw::update");
    
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
    
    if (aborted) {
        return true;
    }
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.5f)
        return false;
    
    return true;
    
}

void TypeWriterDraw::abort () {
    aborted = true;
}

bool TypeWriterDraw::restartKey ( const sf::Event::KeyEvent& event ) {
    
    if (event.code == sf::Keyboard::Return) {
        return true;
    }
    
    return false;
    
}

void TypeWriterDraw::operator() ( Service& service ) {
    
    spdlog::debug("TypeWriterDraw::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    std::stringstream log_msg;
    log_msg << "TypeWriterDraw::operator() letters drawn: " <<
                                                        draw_letters.size();
    spdlog::debug(log_msg.str());
    
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
    
    log_msg.str("");
    log_msg << "TypeWriterDraw::operator() drawing: " <<
                                    static_cast<std::string>(text.getString());
    spdlog::debug(log_msg.str());
    
}

void TypeWriterDraw::add_letter(const char& letter) {
    
    spdlog::debug("TypeWriterDraw::add_letter");
    
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

TypeWriterDraw& TypeWriterDraw::operator= (const TypeWriterDraw& copy) {
    
    DrawComponent::operator= (copy);
    init_copy(copy);
    return *this;
    
}
