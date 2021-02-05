
#pragma once

#include <iostream>
#include <memory>

#include "component.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

using fPtrType = polymorphic_value<Component> (*) (Service& service);

template<typename T>
fPtrType componentMaker () {
    
    auto f1 = [](Service& service) -> polymorphic_value<Component> {
        return make_polymorphic_value<Component, T>(
                            service,
                            std::make_unique<sf::Color>(sf::Color::Black));
    };
    
    return f1;
    
};

// Forward declaration
polymorphic_value<Component> makeSpecial (Service& service,
                                          std::string_view word);
polymorphic_value<Component> makeSingleLetterSiren (Service& service);
polymorphic_value<Component> makeSingleLetterSpoken (Service& service);
polymorphic_value<Component> makeTypeWriterSpoken (Service& service);

class SceneFactory {
public:
    SceneFactory () = default;
    SceneFactory (fPtrType&& sceneFPtr) :
        force_scene(sceneFPtr) {}
    polymorphic_value<Component> makeScene (Service& service);
private:
    fPtrType force_scene {nullptr};
    fPtrType myScene {&makeTypeWriterSpoken};
};
