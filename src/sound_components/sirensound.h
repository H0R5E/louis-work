
#pragma once

#include "component.h"

class SirenSound: public SoundComponent {
public:
    SirenSound (Service& service) :
        SoundComponent(service) {init(service);}
    SirenSound (Service& service,
                std::unique_ptr<sf::Color>&& background) :
        SoundComponent(service, std::move(background)) {init(service);}
    SirenSound (const SirenSound& copy) = default;
    SirenSound (SirenSound&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator () (Service& service) override;
    SirenSound& operator= (const SirenSound& copy) = default;
    SirenSound& operator= (SirenSound&& temp) = default;
private:
    void init (Service& service);
    bool should_replay {false};
    bool aborted {false};
};
