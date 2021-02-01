
#pragma once

#include <memory>
#include <string_view>

#include "component.h"

class SpecialDraw : public DrawComponent {
public:
    SpecialDraw (Service& service,
                 std::string_view word) :
        DrawComponent (service), word(word) {}
    SpecialDraw (Service& service,
                 std::string word,
                 std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, std::move(background)), word(word) {}
    SpecialDraw (const SpecialDraw& copy) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override {}
    void setActiveEvent (Service& service) override {}
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator () (Service& service) override;
private:
    void init ();
    std::string word;
    bool draw_it {false};
    bool aborted {false};
};
