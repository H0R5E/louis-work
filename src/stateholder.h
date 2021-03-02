
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

