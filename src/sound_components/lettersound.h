
#pragma once

#include <memory>

#include "component.h"

class LetterSound: public SoundComponent {
public:
    LetterSound (Service& service) :
        SoundComponent(service) {}
    LetterSound (Service& service,
                 std::unique_ptr<sf::Color>&& background) :
        SoundComponent(service, std::move(background)) {}
    LetterSound (const LetterSound& copy);
    LetterSound (LetterSound&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator() (Service& service) override;
    LetterSound& operator= (const LetterSound& copy);
    LetterSound& operator= (LetterSound&& temp) = default;
private:
    std::unique_ptr<sf::SoundBuffer> buffer;
    bool clearBuffer {false}; 
};
