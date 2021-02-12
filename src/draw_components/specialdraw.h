
#pragma once

#include <memory>
#include <string_view>

#include "component.h"

class SpecialDraw : public DrawComponent {
public:
    SpecialDraw (Service& service,
                 const sf::Color& foreground,
                 std::string_view word) :
        DrawComponent (service, foreground), word(word) {}
    SpecialDraw (Service& service,
                 const sf::Color& foreground,
                 std::string word,
                 std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, foreground, std::move(background)),
        word(word) {}
    SpecialDraw (const SpecialDraw& copy) = default;
    SpecialDraw (SpecialDraw&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override {}
    void setActiveEvent (Service& service) override {}
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator () (Service& service) override;
    SpecialDraw& operator = (const SpecialDraw& copy) = default;
    SpecialDraw& operator = (SpecialDraw&& temp) = default;
private:
    void init ();
    std::string word;
    bool draw_it {false};
    bool aborted {false};
};
