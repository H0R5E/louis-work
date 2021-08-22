
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
#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "component.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

using polyComponentVector = std::vector<polymorphic_value<Component>>;

// Forward declare
class Service;

class State {
public:
    virtual ~State () {};
    virtual State* HandleKeyPressed (const sf::Event& event,
                                     polyComponentVector& scenes,
                                     Service& service) {return nullptr;}
    virtual State* HandleTextEntered (const sf::Event& event,
                                      polyComponentVector& scenes,
                                      Service& service) {return nullptr;}
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      polyComponentVector& scenes,
                                      Service& service) {return nullptr;}
    virtual State* Update (polyComponentVector& scenes,
                           Service& service) {return nullptr;}
    virtual void Enter (polyComponentVector& scenes,
                        Service& service) {return;}
    bool skipEvents {false};
};
