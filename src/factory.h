
#pragma once

#include <iostream>
#include <memory>

#include "component.h"


using fPtrType = std::unique_ptr<Component> (*) (Service& service);

// Forward declaration
std::unique_ptr<Component> basicSingleLetter (Service& service);
std::unique_ptr<Component> basicTypeWriter (Service& service);
std::unique_ptr<Component> basicLetterSound (Service& service);
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
