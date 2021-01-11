
#include "factory.h"

#include "singleletterdraw.h"

#include "lettersound.h"
#include "sirensound.h"

std::unique_ptr<Scene> makeSingleLetterSiren (Service& service) {
    return std::make_unique<Scene>(std::make_unique<SingleLetterDraw>(service),
                                   std::make_unique<SirenSound>(service));
};

std::unique_ptr<Scene> makeSingleLetterSpoken (Service& service) {
    return std::make_unique<Scene>(std::make_unique<SingleLetterDraw>(service),
                                   std::make_unique<LetterSound>(service));
};

std::unique_ptr<Scene> SceneFactory::makeScene (Service& service) {
        
    std::unique_ptr<Scene> newScene;
    
    if (force_scene) {
        newScene = force_scene(service);
    } else {
        newScene = myScene(service);
    }
    
    return newScene;
    
}
