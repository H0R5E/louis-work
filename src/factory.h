
#pragma once

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

#include "component.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

using fPtrBasic = polymorphic_value<Component> (*) (Service& service);
using fPtrColor = polymorphic_value<Component> (*) (
                                                Service& service,
                                                const sf::Color& foreground,
                                                const sf::Color& background);
using colorPair = std::pair<sf::Color, sf::Color>;

template<typename T>
fPtrBasic componentMaker () {
    
    auto f1 = [](Service& service) -> polymorphic_value<Component> {
        return make_polymorphic_value<Component, T>(
                            service,
                            std::make_unique<sf::Color>(sf::Color::Black));
    };
    
    return f1;
    
};

template<typename T>
fPtrBasic drawComponentMaker (const sf::Color& foreground) {
    
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
    SceneFactory (fPtrBasic&& sceneFPtr) :
        force_scene(sceneFPtr) {}
    SceneFactory (fPtrColor&& sceneFPtr) :
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
    std::variant<std::monostate, fPtrBasic, fPtrColor> force_scene
                                                        = std::monostate {};
    const std::vector<fPtrColor> sceneMakers {&makeSingleLetterSiren,
                                              &makeSingleLetterSpoken,
                                              &makeTypeWriterSpoken};
    const std::vector<colorPair> colorCombos {
        std::make_pair(sf::Color::Black, sf::Color::Yellow),
        std::make_pair(sf::Color::Red, sf::Color::Black),
        std::make_pair(sf::Color::Blue, sf::Color::Magenta)};
    std::unique_ptr<colorPair> lastColors {nullptr};
};
