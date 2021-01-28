
#pragma once

#include <memory>

#include "component.h"

class SingleLetterDraw : public DrawComponent {
public:
    SingleLetterDraw (Service& service) :
        DrawComponent (service) {};
    SingleLetterDraw (Service& service,
                      std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, std::move(background)) {};
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator () (Service& service) override;
private:
    std::unique_ptr<char> letter;
    bool should_draw {true};
    bool aborted {false};
};
