
#include "factory.h"
#include "helpers.h"
#include "scene.h"

#include "singleletterdraw.h"
#include "specialdraw.h"
#include "typewriterdraw.h"

#include "lettersound.h"
#include "sirensound.h"
#include "specialsound.h"

polymorphic_value<Component> makeSpecial (Service& service,
                                          std::string_view word,
                                          const sf::Color& foreground,
                                          const sf::Color& background) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent,
                                   SpecialDraw>(service,
                                                foreground,
                                                word),
            make_polymorphic_value<SoundComponent,
                                   SpecialSound>(service, word),
            std::make_unique<sf::Color>(background));
};

polymorphic_value<Component> makeSingleLetterSiren (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent,
                                   SingleLetterDraw>(service,
                                                     foreground),
            make_polymorphic_value<SoundComponent, SirenSound>(service),
            std::make_unique<sf::Color>(background));
};

polymorphic_value<Component> makeSingleLetterSpoken (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent,
                                   SingleLetterDraw>(service, foreground),
            make_polymorphic_value<SoundComponent, LetterSound>(service),
            std::make_unique<sf::Color>(background));
};

polymorphic_value<Component> makeTypeWriterSpoken (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent,
                                   TypeWriterDraw>(service, foreground),
            make_polymorphic_value<SoundComponent, LetterSound>(service),
            std::make_unique<sf::Color>(background));
};

polymorphic_value<Component> SceneFactory::makeScene (Service& service) {
    
    const auto& color_pair = getRandomSample(colorCombos);
    lastColors = std::make_unique<colorPair>(color_pair);
    
    switch (force_scene.index()) {

        case 0: break; // do nothing because the type is std::monostate

        case 1: {
            auto f = std::get<fPtrBasic>(force_scene);
            return f(service);
        }

        case 2: {
            auto f = std::get<fPtrColor>(force_scene);
            return f(service, color_pair.second, color_pair.first);
        }
    
    }
    
    const auto& scene_maker = getRandomSample(sceneMakers);
    
    return scene_maker(service, color_pair.second, color_pair.first);
    
}

polymorphic_value<Component> SceneFactory::makeSpecialScene (
                                                Service& service,
                                                std::string_view word) {
    
    colorPair color_pair;
    
    if (lastColors) {
        color_pair = *lastColors;
    } else {
        color_pair = getRandomSample(colorCombos);
    }
    
    return makeSpecial(service, word, color_pair.second, color_pair.first);
    
}
