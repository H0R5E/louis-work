
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
    void setScene () override;
    State* getCurrentState ();
    sf::Font& getFont (std::string_view name) override;
    Scene& getScene () override;
    sf::SoundBuffer& getSoundBuffer (std::string_view name) override;
    Window& getWindow () override;
    std::unique_ptr<Sound> makeSoundPtr () override;
private:
    void initResources ();
    ResourceHolder<sf::SoundBuffer> buffer_holder {};
    State* current_state;
    std::unique_ptr<Scene> scene;
    SceneFactory factory;
    ResourceHolder<sf::Font> font_holder {};
    std::unique_ptr<SoundMakerBase> sound_maker;
    std::unique_ptr<Window> window;
};
