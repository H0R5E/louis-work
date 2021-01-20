
#pragma once

#include <iostream>
#include <memory>

#include "component.h"


using fPtrType = std::unique_ptr<Component> (*) (Service& service);

template<typename T>
fPtrType componentMaker () {
    
    std::unique_ptr<Component> f1 = [](Service& service) {
        return std::make_unique<T>(service,
                                   std::make_unique<sf::Color>(
                                                sf::Color::Black)); };
    
    return f1;
    
};

// Forward declaration
std::unique_ptr<Component> makeSingleLetterSiren (Service& service);
std::unique_ptr<Component> makeSingleLetterSpoken (Service& service);
std::unique_ptr<Component> makeTypeWriterSpoken (Service& service);

class SceneFactory {
public:
    SceneFactory () = default;
    SceneFactory (fPtrType&& sceneFPtr) :
        force_scene(sceneFPtr) {}
    std::unique_ptr<Component> makeScene (Service& service);
private:
    fPtrType force_scene {nullptr};
    fPtrType myScene {&makeTypeWriterSpoken};
};
