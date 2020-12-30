
# pragma once

#include "startstate.h"
#include "playstate.h"
#include "drawstate.h"
#include "waitstate.h"

class StateHolder {
public:
    static StartState start;
    static PlayState play;
    static DrawState draw;
    static WaitState wait;
};

