
#pragma once

#include <memory>

#include "component.h"

class SpecialSound: public SoundComponent {
public:
    SpecialSound (Service& service,
                 std::string_view word) :
        SoundComponent (service), word(word) {}
    SpecialSound (Service& service,
                 std::string word,
                 std::unique_ptr<sf::Color>&& background) :
        SoundComponent(service, std::move(background)), word(word) {}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override {}
    void setActiveEvent (Service& service) override {}
    bool update () override;
    bool isCompleted () override;
    void operator () (Service& service) override;
private:
    std::string word;
    std::unique_ptr<sf::SoundBuffer> buffer;
    bool clearBuffer {false};
    bool say_it {false};
};
