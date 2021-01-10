
#include "factory.h"

#include "singleletterdraw.h"

#include "lettersound.h"
//#include "sirensound.h"

//std::unique_ptr<Scene> makeSingleLetterSiren () {
//    return std::make_unique<Scene>(std::make_unique<SingleLetterDraw>(),
//                                   std::make_unique<SirenSound>());
//};

std::unique_ptr<Scene> makeSingleLetterSpoken () {
    return std::make_unique<Scene>(std::make_unique<SingleLetterDraw>(),
                                   std::make_unique<LetterSound>());
};
