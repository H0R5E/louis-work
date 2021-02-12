
#pragma once

#include <string>

#include "component.h"

class TypeWriterDraw : public DrawComponent {
public:
    TypeWriterDraw (Service& service,
                    const sf::Color& foreground) :
            DrawComponent(service, foreground) {init(service);}
    TypeWriterDraw (Service& service,
                    const sf::Color& foreground,
                    std::unique_ptr<sf::Color>&& background) :
            DrawComponent(service, foreground, std::move(background)) {
        init(service);
    }
    TypeWriterDraw (const TypeWriterDraw& copy);
    TypeWriterDraw (TypeWriterDraw&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator() (Service& service) override;
    TypeWriterDraw& operator= (const TypeWriterDraw& copy);
    TypeWriterDraw& operator= (TypeWriterDraw&& temp) = default;
private:
    void init (Service& service);
    void init_copy (const TypeWriterDraw& copy);
    void add_letter(const char& letter);
    sf::Text text;
    std::unique_ptr<char> active_letter;
    std::string draw_letters {};
    std::unique_ptr<float> yorigin;
    bool force_draw {false};
    bool reset_yorigin {false};
    bool aborted {false};
};
