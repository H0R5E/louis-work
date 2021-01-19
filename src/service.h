
#pragma once

#include <memory>
#include <string_view>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
    virtual Window& getWindow () const = 0;
    virtual void storeLetter (const char letter) = 0;
    virtual const std::vector<char>& getLetters () const = 0;
    virtual void clearLetters () = 0;
    virtual std::unique_ptr<Component> makeScenePtr () = 0;
    virtual std::unique_ptr<Sound> makeSoundPtr () const = 0;
};
