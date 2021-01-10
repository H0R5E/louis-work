
#pragma once

#include "component.h"

class TypeWriterDraw : public DrawComponent {
public:
    void start (const sf::Event& event,
                Service& service) override;
    bool isCompleted () override;
};
