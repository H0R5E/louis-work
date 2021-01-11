
#pragma once

#include <memory>

#include "component.h"

class SingleLetterDraw : public DrawComponent {
public:
    SingleLetterDraw (Service& service) :
        DrawComponent (service) {}
    void set_active_event (const sf::Event& event,
                           Service& service) override;
    void set_active_event (Service& service) override;
    void draw (Service& service) override;
    bool redraw () override;
    bool isCompleted () override;
private:
    std::unique_ptr<char> letter;
    bool should_draw {true};
};
