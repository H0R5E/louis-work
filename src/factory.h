
#pragma once

#include <memory>

#include "scene.h"


using fPtrType = std::unique_ptr<Scene> (*) ();

// Forward declaration
//std::unique_ptr<Scene> makeSingleLetterSiren ();
std::unique_ptr<Scene> makeSingleLetterSpoken ();

class SceneFactory {
public:
    SceneFactory () = default;
    SceneFactory (std::unique_ptr<Scene>&& scene) :
        force_scene(std::move(scene)) {}
    std::unique_ptr<Scene> makeScene () {
        if (force_scene) {
            return std::move(force_scene);
        }
        auto newScene = myScene();
        return newScene;
    }
private:
    std::unique_ptr<Scene> force_scene;
    fPtrType myScene {&makeSingleLetterSpoken};
};
