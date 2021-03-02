
#include "stateholder.h"

StartState StateHolder::start {};
PlayState StateHolder::play {};
DrawState StateHolder::draw {};
WaitState StateHolder::wait {};
RestartState StateHolder::restart {};
SpecialState StateHolder::special {};
