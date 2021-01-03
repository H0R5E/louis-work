
#include "factory.h"

#include "singleletterdraw.h"

#include "lettersound.h"
#include "sirensound.h"

std::unique_ptr<Command> makeSingleLetterSiren () {
    return std::make_unique<Command>(std::make_unique<SingleLetterDraw>(),
                                     std::make_unique<SirenSound>());
};

std::unique_ptr<Command> makeSingleLetterSpoken () {
    return std::make_unique<Command>(std::make_unique<SingleLetterDraw>(),
                                     std::make_unique<LetterSound>());
};
