
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
