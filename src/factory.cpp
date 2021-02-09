
#include <algorithm>
#include <random>

#include "factory.h"
#include "scene.h"

#include "singleletterdraw.h"
#include "specialdraw.h"
#include "typewriterdraw.h"

#include "lettersound.h"
#include "sirensound.h"
#include "specialsound.h"

polymorphic_value<Component> makeSpecial (Service& service,
                                        std::string_view word) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent, SpecialDraw>(service, word),
            make_polymorphic_value<SoundComponent, SpecialSound>(service, word),
            std::make_unique<sf::Color>(sf::Color::Black));
};

polymorphic_value<Component> makeSingleLetterSiren (Service& service) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent, SingleLetterDraw>(service),
            make_polymorphic_value<SoundComponent, SirenSound>(service),
            std::make_unique<sf::Color>(sf::Color::Black));
};

polymorphic_value<Component> makeSingleLetterSpoken (Service& service) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent, SingleLetterDraw>(service),
            make_polymorphic_value<SoundComponent, LetterSound>(service),
            std::make_unique<sf::Color>(sf::Color::Black));
};

polymorphic_value<Component> makeTypeWriterSpoken (Service& service) {
    return make_polymorphic_value<Component, Scene>(
            service,
            make_polymorphic_value<DrawComponent, TypeWriterDraw>(service),
            make_polymorphic_value<SoundComponent, LetterSound>(service),
            std::make_unique<sf::Color>(sf::Color::Black));
};

polymorphic_value<Component> SceneFactory::makeScene (Service& service) {
    
    if (force_scene) {
        return force_scene(service);
    }
    
    std::vector<fPtrType> out;
    size_t nelems = 1;
    std::sample(
        sceneMakers.begin(),
        sceneMakers.end(),
        std::back_inserter(out),
        nelems,
        std::mt19937{std::random_device{}()}
    );
    
    return out.front()(service);
    
}
