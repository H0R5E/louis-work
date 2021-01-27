
#include "factory.h"
#include "scene.h"

#include "louisdraw.h"
#include "singleletterdraw.h"
#include "typewriterdraw.h"

#include "lettersound.h"
#include "louissound.h"
#include "sirensound.h"

std::unique_ptr<Component> makeLouisSpecial (Service& service) {
    return std::make_unique<Scene>(service,
                                   std::make_unique<LouisDraw>(service),
                                   std::make_unique<LouisSound>(service),
                                   std::make_unique<sf::Color>(
                                                            sf::Color::Black));
};

std::unique_ptr<Component> makeSingleLetterSiren (Service& service) {
    return std::make_unique<Scene>(service,
                                   std::make_unique<SingleLetterDraw>(service),
                                   std::make_unique<SirenSound>(service),
                                   std::make_unique<sf::Color>(
                                                            sf::Color::Black));
};

std::unique_ptr<Component> makeSingleLetterSpoken (Service& service) {
    return std::make_unique<Scene>(service,
                                   std::make_unique<SingleLetterDraw>(service),
                                   std::make_unique<LetterSound>(service),
                                   std::make_unique<sf::Color>(
                                                            sf::Color::Black));
};

std::unique_ptr<Component> makeTypeWriterSpoken (Service& service) {
    return std::make_unique<Scene>(service,
                                   std::make_unique<TypeWriterDraw>(service),
                                   std::make_unique<LetterSound>(service),
                                   std::make_unique<sf::Color>(
                                                            sf::Color::Black));
};

std::unique_ptr<Component> SceneFactory::makeScene (Service& service) {
        
    std::unique_ptr<Component> newScene;
    
    if (force_scene) {
        newScene = force_scene(service);
    } else {
        newScene = myScene(service);
    }
    
    return newScene;
    
}
