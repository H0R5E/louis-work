
#pragma once

#include <memory>

#include "component.h"

class LouisDraw : public DrawComponent {
public:
    LouisDraw (Service& service) :
        DrawComponent (service) {}
    LouisDraw (Service& service,
               std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, std::move(background)) {}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override {}
    void setActiveEvent (Service& service) override {}
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator () (Service& service) override;
private:
    bool draw_it {false};
    bool aborted {false};
};
