
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

#include <string>

#include "component.h"

class TypeWriterDraw : public DrawComponent {
public:
    TypeWriterDraw (Service& service,
                    const sf::Color& foreground) :
            DrawComponent(service, foreground) {init(service);}
    TypeWriterDraw (Service& service,
                    const sf::Color& foreground,
                    std::unique_ptr<sf::Color>&& background) :
            DrawComponent(service, foreground, std::move(background)) {
        init(service);
    }
    TypeWriterDraw (const TypeWriterDraw& copy);
    TypeWriterDraw (TypeWriterDraw&& temp) = default;
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    bool restartKey (const sf::Event::KeyEvent& event) override;
    void operator() (Service& service) override;
    TypeWriterDraw& operator= (const TypeWriterDraw& copy);
    TypeWriterDraw& operator= (TypeWriterDraw&& temp) = default;
private:
    void init (Service& service);
    void init_copy (const TypeWriterDraw& copy);
    void add_letter(const char& letter);
    sf::Text text;
    std::unique_ptr<char> active_letter;
    std::string draw_letters {};
    std::unique_ptr<float> yorigin;
    bool force_draw {false};
    bool reset_yorigin {false};
    bool aborted {false};
};
