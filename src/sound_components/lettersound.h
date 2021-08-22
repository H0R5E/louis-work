
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

#include "component.h"

class LetterSound: public SoundComponent {
public:
    LetterSound (Service& service) :
        SoundComponent(service) {}
    LetterSound (Service& service,
                 std::unique_ptr<sf::Color>&& background) :
        SoundComponent(service, std::move(background)) {}
    LetterSound (const LetterSound& copy);
    LetterSound (LetterSound&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    void operator() (Service& service) override;
    LetterSound& operator= (const LetterSound& copy);
    LetterSound& operator= (LetterSound&& temp) = default;
private:
    std::unique_ptr<sf::SoundBuffer> buffer;
    bool clearBuffer {false}; 
};
