
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
#include <SFML/Graphics.hpp>

#include "component.h"
#include "polymorphic_value.h"
#include "service.h"

using namespace isocpp_p0201;

class Scene : public Component {
public:
    Scene (Service& service,
           polymorphic_value<DrawComponent>&& draw_component,
           polymorphic_value<SoundComponent>&& sound_component) :
        Component(service),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    Scene (Service& service,
           polymorphic_value<DrawComponent>&& draw_component,
           polymorphic_value<SoundComponent>&& sound_component,
           std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    bool restartService (const Service& service) override;
    bool restartKey (const sf::Event::KeyEvent& event) override;
    SoundComponent* getSoundComponentPtr () {
        return sound_component.operator->();
    }
    void operator () (Service& service) override;
private:
    polymorphic_value<DrawComponent> draw_component;
    polymorphic_value<SoundComponent> sound_component;
    bool replay {true};
};
