
#include <sstream>
#include <spdlog/spdlog.h>

#include "singleletterdraw.h"
#include "service.h"
#include "window.h"

SingleLetterDraw::SingleLetterDraw (const SingleLetterDraw& copy) :
            DrawComponent(copy) {
    
    if (copy.letter) {
        letter = std::make_unique<char>(*copy.letter);
    }
    
    should_draw = copy.should_draw;
    aborted = copy.aborted;
    
}

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
    
    spdlog::get("file_logger")->debug("SingleLetterDraw::isCompleted");
    
    if (aborted) {
        return true;
    }
    
    auto elapsed = clock.getElapsedTime();
    
    std::stringstream log_msg;
    log_msg << "SingleLetterDraw::isCompleted time elapsed: " <<
                                                        elapsed.asSeconds();
    spdlog::get("file_logger")->debug(log_msg.str());

    if (elapsed.asSeconds() < 0.5f) {
        return false;
    }
    
    return true;
    
}

void SingleLetterDraw::abort () {
    aborted = true;
}

bool SingleLetterDraw::restartService (const Service& service) {
    
    auto max_length = service.getMaxSpecialLength();
    auto word_length = service.getWord().length();
    
    int stop_length = 10;
    
    if (max_length and max_length >= stop_length) {
        stop_length = *max_length + 1;
    }
    
    if (word_length >= stop_length) {
        return true;
    }
    
    return false;
    
}

void SingleLetterDraw::operator() (Service& service) {
    
    spdlog::get("file_logger")->debug("SingleLetterDraw::operator()");
    
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
    text.setFillColor(foreground);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    auto& window = service.getWindow();
    window.draw(text);
    
    clock.restart();
    should_draw = false;
    
}

SingleLetterDraw& SingleLetterDraw::operator= (const SingleLetterDraw& copy) {
    
    DrawComponent::operator= (copy);
    
    if (copy.letter) {
        letter = std::make_unique<char>(*copy.letter);
    }
    
    should_draw = copy.should_draw;
    aborted = copy.aborted;
    
    return *this;
    
}
