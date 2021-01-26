
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "factory.h"
#include "resourceholder.h"
#include "service.h"
#include "sound.h"
#include "state.h"
#include "window.h"

using uniqueComponent = std::unique_ptr<Component>;

class Game : public Service {
public:
    Game() = delete;
    Game(std::unique_ptr<Window>&& window,
         std::unique_ptr<SoundMakerBase>&& sound_maker);
    Game(std::unique_ptr<Window>&& window,
         std::unique_ptr<SoundMakerBase>&& sound_maker,
         fPtrType&& sceneFPtr);
    void EventLoop ();
    State* getCurrentState () const;
    const sf::Font& getFont (std::string_view name) const override;
    const sf::SoundBuffer& getSoundBuffer
                                        (std::string_view name) const override;
    Window& getWindow () const override;
    void storeLetter (const char letter) override;
    const std::string getWord () const override;
    void clearLetters () override;
    uniqueComponent makeScenePtr () override;
    std::unique_ptr<Sound> makeSoundPtr () const override;
protected:
    std::vector<uniqueComponent> scenes {};
private:
    void initResources ();
    void updateScene ();
    SceneFactory factory;
    std::unique_ptr<SoundMakerBase> sound_maker;
    std::unique_ptr<Window> window;
    ResourceHolder<sf::Font> font_holder {};
    ResourceHolder<sf::SoundBuffer> buffer_holder {};
    State* current_state;
    std::vector<char> letter_store {};
};
