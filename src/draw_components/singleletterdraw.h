
#pragma once

#include "component.h"

class SingleLetterDraw : public DrawComponent {
public:
    void start (const sf::Event& event,
                Command& command,
                Game& game) override;
    bool isCompleted () override;
};
