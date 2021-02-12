
#pragma once

#include <memory>

#include "component.h"

class SingleLetterDraw : public DrawComponent {
public:
    SingleLetterDraw (Service& service,
                      const sf::Color& foreground) :
        DrawComponent (service, foreground) {};
    SingleLetterDraw (Service& service,
                      const sf::Color& foreground,
                      std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, foreground, std::move(background)) {};
    SingleLetterDraw (const SingleLetterDraw& copy);
    SingleLetterDraw (SingleLetterDraw&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator() (Service& service) override;
    SingleLetterDraw& operator= (const SingleLetterDraw& copy);
    SingleLetterDraw& operator= (SingleLetterDraw&& temp) = default;
private:
    std::unique_ptr<char> letter {nullptr};
    bool should_draw {true};
    bool aborted {false};
};
