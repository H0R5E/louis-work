
#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "component.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

using fPtrType = polymorphic_value<Component> (*) (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background);
using colorPair = std::pair<sf::Color, sf::Color>;

template<typename T>
fPtrType componentMaker () {
    
    auto f1 = [](Service& service) -> polymorphic_value<Component> {
        return make_polymorphic_value<Component, T>(
                            service,
                            std::make_unique<sf::Color>(sf::Color::Black));
    };
    
    return f1;
    
};

template<typename T>
fPtrType drawComponentMaker (const sf::Color& foreground) {
    
    auto f1 = [foreground](Service& service)
                                    -> polymorphic_value<DrawComponent> {
        return make_polymorphic_value<DrawComponent, T>(
                            service,
                            foreground,
                            std::make_unique<sf::Color>(sf::Color::Black));
    };
    
    return f1;
    
};

// Forward declaration
polymorphic_value<Component> makeSpecial (Service& service,
                                          std::string_view word,
                                          const sf::Color& foreground,
                                          const sf::Color& background);
polymorphic_value<Component> makeSingleLetterSiren (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background);
polymorphic_value<Component> makeSingleLetterSpoken (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background);
polymorphic_value<Component> makeTypeWriterSpoken (Service& service,
                                                   const sf::Color& foreground,
                                                   const sf::Color& background);

class SceneFactory {
public:
    SceneFactory () = default;
    SceneFactory (fPtrType&& sceneFPtr) :
        force_scene(sceneFPtr) {}
    SceneFactory (const SceneFactory& copy) {
        std::cout << "Copy" << std::endl;
        *this = copy;
    };
    SceneFactory (SceneFactory&& temp) = default;
    polymorphic_value<Component> makeScene (Service& service);
    polymorphic_value<Component> makeSpecialScene (Service& service,
                                                   std::string_view word);
    SceneFactory& operator= (const SceneFactory& copy) {
        if (copy.lastColors) {
            lastColors = std::make_unique<colorPair>(*copy.lastColors);
        }
        return *this;
    }
    SceneFactory& operator= (SceneFactory&& temp) {
        lastColors = std::move(temp.lastColors);
        return *this;
    }
private:
    fPtrType force_scene {nullptr};
    const std::vector<fPtrType> sceneMakers {&makeSingleLetterSiren,
                                             &makeSingleLetterSpoken,
                                             &makeTypeWriterSpoken};
    const std::vector<colorPair> colorCombos {
        std::make_pair(sf::Color::Black, sf::Color::Yellow),
        std::make_pair(sf::Color::Red, sf::Color::Black),
        std::make_pair(sf::Color::Blue, sf::Color::Magenta)};
    std::unique_ptr<colorPair> lastColors {nullptr};
};
