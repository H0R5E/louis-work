
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

class SingleLetterDraw : public DrawComponent {
public:
    SingleLetterDraw (Service& service,
                      const sf::Color& foreground) :
        DrawComponent (service, foreground) {};
    SingleLetterDraw (Service& service,
                      const sf::Color& foreground,
                      std::unique_ptr<sf::Color>&& background) :
        DrawComponent(service, foreground, std::move(background)) {};
    SingleLetterDraw (const SingleLetterDraw& copy);
    SingleLetterDraw (SingleLetterDraw&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    bool restartKey (const sf::Event::KeyEvent& event) override;
    bool restartService (const Service& service) override;
    void operator() (Service& service) override;
    SingleLetterDraw& operator= (const SingleLetterDraw& copy);
    SingleLetterDraw& operator= (SingleLetterDraw&& temp) = default;
private:
    std::unique_ptr<char> letter {nullptr};
    bool should_draw {true};
    bool aborted {false};
};
