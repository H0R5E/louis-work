
#pragma once

#include <iostream>
#include <memory>

#include "scene.h"


using fPtrType = std::unique_ptr<Scene> (*) (Service& service);

// Forward declaration
std::unique_ptr<Scene> makeSingleLetterSiren (Service& service);
std::unique_ptr<Scene> makeSingleLetterSpoken (Service& service);

class SceneFactory {
public:
    SceneFactory () = default;
    SceneFactory (fPtrType&& sceneFPtr) :
        force_scene(sceneFPtr) {}
    std::unique_ptr<Scene> makeScene (Service& service);
private:
    fPtrType force_scene {nullptr};
    fPtrType myScene {&makeSingleLetterSiren};
};
