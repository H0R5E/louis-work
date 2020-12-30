
#pragma once

#include <memory>
#include <string_view>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "sound.h"
#include "window.h"

// Forward declare
class Command;

class Service {
public:
    virtual ~Service () = default;
    virtual Command* getCommandPtr () = 0; 
    virtual sf::Font& getFont (std::string_view name) = 0;
    virtual sf::SoundBuffer& getSoundBuffer (std::string_view name) = 0;
    virtual Window* getWindowPtr () = 0;
    virtual std::unique_ptr<Sound> makeSoundPtr () = 0;
};
