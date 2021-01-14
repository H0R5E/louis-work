
#pragma once

#include <vector>

#include "component.h"

class TypeWriterDraw : public DrawComponent {
public:
    TypeWriterDraw (Service& service) :
        DrawComponent (service) {}
    void set_active_event (const sf::Event& event,
                           Service& service) override;
    void set_active_event (Service& service) override;
    void draw (Service& service) override;
    bool redraw () override;
    bool isCompleted () override;
private:
    std::unique_ptr<char> active_letter;
    std::vector<char> draw_letters;
    bool force_draw {false};
};
