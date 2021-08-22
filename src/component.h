
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
#include <SFML/Graphics.hpp>

#include "polymorphic_value.h"
#include "sound.h"

using namespace isocpp_p0201;

// Forward declare
class Service;

class Component {
public:
    Component () = delete;
    Component (Service& service) {};
    Component (Service& service,
               std::unique_ptr<sf::Color>&& background) :
        background(std::move(background)) {};
    Component (const Component& copy) {
        *this = copy;
    }
    Component (Component&& temp) = default;
    virtual void setActiveEvent (const sf::Event& event,
                                 Service& service) = 0;
    virtual void setActiveEvent (Service& service) = 0;
    virtual bool update () = 0;
    virtual bool isCompleted () = 0;
    virtual void abort () = 0;
    virtual bool restartService (const Service& service) {
        return false;
    }
    virtual bool restartKey (const sf::Event::KeyEvent& event) {
        return false;
    }
    virtual void operator() (Service& service) = 0;
    Component& operator= (const Component& copy) {
        if (copy.background) {
            background = std::make_unique<sf::Color>(*copy.background);
        }
        return *this;
    }
    Component& operator= (Component&& temp) = default;
    virtual ~Component () = default;
protected:
    std::unique_ptr<sf::Color> background {nullptr};
    sf::Clock clock;
};

class DrawComponent : public Component {
public:
    DrawComponent (Service& service,
                   const sf::Color& foreground) :
        Component (service), foreground(foreground) {}
    DrawComponent (Service& service,
                   const sf::Color& foreground,
                   std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)), foreground(foreground) {}
protected:
    sf::Color foreground;
};

class SoundComponent : public Component {
public:
    SoundComponent (Service& service) :
        Component (service) {}
    SoundComponent (Service& service,
                    std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)) {};
    Sound* getSoundPtr () {
        if (!sound) {
            throw std::runtime_error("No sound");
        }
        return sound.operator->();
    }
protected:
    polymorphic_value<Sound> sound;
};
