
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

# pragma once

#include "startstate.h"
#include "playstate.h"
#include "drawstate.h"
#include "waitstate.h"
#include "restartstate.h"
#include "specialstate.h"

class StateHolder {
public:
    static StartState start;
    static PlayState play;
    static DrawState draw;
    static WaitState wait;
    static RestartState restart;
    static SpecialState special;
};

