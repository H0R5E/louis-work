
#pragma once

#include <string_view>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Font GetFont (std::string_view name);
sf::SoundBuffer GetSoundBuffer (std::string_view name);
bool CtrlC ();
