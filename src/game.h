
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "factory.h"
#include "polymorphic_value.h"
#include "resourceholder.h"
#include "service.h"
#include "sound.h"
#include "state.h"
#include "window.h"


using namespace isocpp_p0201;

using polyComponent = polymorphic_value<Component>;

class Game : public Service {
public:
    Game () = delete;
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker);
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker,
          fPtrType&& sceneFPtr);
    void EventLoop ();
    State* getCurrentState () const;
    const sf::Font& getFont (std::string_view name) const override;
    const sf::SoundBuffer& getSoundBuffer
                                        (std::string_view name) const override;
    Window& getWindow () override;
    void storeLetter (const char letter) override;
    const std::string getWord () const override;
    void clearLetters () override;
    polyComponent makeScenePValue () override;
    polymorphic_value<Sound> makeSoundPValue () override;
protected:
    std::vector<polyComponent> scenes {};
    void updateScene ();
private:
    void initResources ();
    SceneFactory factory;
    polymorphic_value<SoundMakerBase> sound_maker;
    std::shared_ptr<Window> window;
    ResourceHolder<sf::Font> font_holder {};
    ResourceHolder<sf::SoundBuffer> buffer_holder {};
    State* current_state;
    std::vector<char> letter_store {};
};
