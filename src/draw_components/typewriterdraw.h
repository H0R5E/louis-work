
#pragma once

#include <string>

#include "component.h"

class TypeWriterDraw : public DrawComponent {
public:
    TypeWriterDraw (Service& service) :
        DrawComponent(service) {init(service);}
    TypeWriterDraw (Service& service,
                      std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, std::move(background)) {init(service);}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator () (Service& service) override;
private:
    void init (Service& service);
    void add_letter(const char& letter);
    sf::Text text;
    std::unique_ptr<char> active_letter;
    std::string draw_letters {};
    std::unique_ptr<float> yorigin;
    bool force_draw {false};
    bool reset_yorigin {false};
    bool aborted {false};
};
