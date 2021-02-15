
#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "polymorphic_value.h"

using namespace isocpp_p0201;

// Forward declare
class Component;
class Window;
class Sound;

class Service {
public:
    virtual ~Service () = default;
    virtual const sf::Font& getFont (std::string_view name) const = 0;
    virtual const sf::SoundBuffer& getSoundBuffer
                                            (std::string_view name) const = 0;
    virtual Window& getWindow () = 0;
    virtual bool triggerSpecial () const = 0;
    virtual const std::optional<int> getMaxSpecialLength () const = 0;
    virtual void storeLetter (const char letter) = 0;
    virtual const std::string getWord () const = 0;
    virtual void clearLetters () = 0;
    virtual polymorphic_value<Component> makeScenePValue () = 0;
    virtual polymorphic_value<Component> makeSpecialScenePValue (
                                                    std::string_view word) = 0;
    virtual polymorphic_value<Sound> makeSoundPValue () = 0;
};
