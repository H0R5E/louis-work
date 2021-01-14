
#pragma once

#include <string>

#include "component.h"

class TypeWriterDraw : public DrawComponent {
public:
    TypeWriterDraw (Service& service);
    void set_active_event (const sf::Event& event,
                           Service& service) override;
    void set_active_event (Service& service) override;
    void draw (Service& service) override;
    bool redraw () override;
    bool isCompleted () override;
private:
    void add_letter(const char& letter);
    sf::Text text;
    std::unique_ptr<char> active_letter;
    std::string draw_letters {};
    std::unique_ptr<float> yorigin;
    bool force_draw {false};
    bool reset_yorigin {false};
};
