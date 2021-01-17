
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Forward declare
#include "factory.h"
#include "resourceholder.h"
#include "scene.h"
#include "service.h"
#include "sound.h"
#include "state.h"
#include "window.h"

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
    bool hasScene () const override;
    void setScene () override;
    Scene& getScene () const override;
    const sf::Font& getFont (std::string_view name) const override;
    const sf::SoundBuffer& getSoundBuffer
                                        (std::string_view name) const override;
    Window& getWindow () const override;
    void storeLetter (const char letter) override;
    const std::vector<char>& getLetters () const override;
    void clearLetters () override;
    std::unique_ptr<Sound> makeSoundPtr () const override;
private:
    void initResources ();
    SceneFactory factory;
    std::unique_ptr<SoundMakerBase> sound_maker;
    std::unique_ptr<Window> window;
    ResourceHolder<sf::Font> font_holder {};
    ResourceHolder<sf::SoundBuffer> buffer_holder {};
    State* current_state;
    std::unique_ptr<Scene> scene {nullptr};
    std::vector<char> letter_store {};
};
