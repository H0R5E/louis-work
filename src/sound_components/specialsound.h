
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
    SpecialSound (const SpecialSound& copy);
    SpecialSound (SpecialSound&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override {}
    void setActiveEvent (Service& service) override {}
    bool update () override;
    bool isCompleted () override;
    void operator() (Service& service) override;
    SpecialSound& operator= (const SpecialSound& copy);
    SpecialSound& operator= (SpecialSound&& temp) = default;
private:
    void init_copy (const SpecialSound& copy);
    std::string word;
    std::unique_ptr<sf::SoundBuffer> buffer;
    bool say_it {false};
};
