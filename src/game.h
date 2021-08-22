
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
          polymorphic_value<SoundMakerBase>&& sound_maker,
          const bool& test_assets=false);
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker,
          fPtrBasic&& sceneFPtr,
          const bool& test_assets=false);
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker,
          fPtrColor&& sceneFPtr,
          const bool& test_assets=false);
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker,
          const std::unordered_set<std::string>& special_words,
          const bool& test_assets=false);
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker,
          const std::unordered_set<std::string>& special_words,
          fPtrBasic&& sceneFPtr,
          const bool& test_assets=false);
    Game (std::unique_ptr<Window>&& window,
          polymorphic_value<SoundMakerBase>&& sound_maker,
          const std::unordered_set<std::string>& special_words,
          fPtrColor&& sceneFPtr,
          const bool& test_assets=false);
    void EventLoop ();
    State* getCurrentState () const;
    const sf::Font& getFont (std::string_view name) const override;
    const sf::SoundBuffer& getSoundBuffer
                                        (std::string_view name) const override;
    Window& getWindow () override;
    bool triggerSpecial () const override;
    const std::optional<int> getMaxSpecialLength () const override;
    void storeLetter (const char letter) override;
    const std::string getWord () const override;
    void clearLetters () override;
    polyComponent makeSpecialScenePValue (std::string_view word) override;
    polyComponent makeScenePValue () override;
    polymorphic_value<Sound> makeSoundPValue () override;
protected:
    std::vector<polyComponent> scenes {};
    void updateScene ();
private:
    void initResources (const bool& test_assets);
    SceneFactory factory;
    polymorphic_value<SoundMakerBase> sound_maker;
    std::shared_ptr<Window> window;
    ResourceHolder<sf::Font> font_holder;
    ResourceHolder<sf::SoundBuffer> buffer_holder;
    State* current_state;
    std::vector<char> letter_store {};
    std::unordered_set<std::string> special_words {"louis", 
                                                   "mummy",
                                                   "daddy",
                                                   "fart",
                                                   "poo",
                                                   "wee"};
};
