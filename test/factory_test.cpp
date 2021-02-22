
#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "sound.h"
#include "factory.h"

TEST (FactoryTest, makeSpecial) { 
    MockService service {};
    auto special = makeSpecial (service,
                                "TEST",
                                sf::Color::Yellow, 
                                sf::Color::Black);
}

TEST (FactoryTest, SceneFactoryinit) { 
    ASSERT_NO_THROW(SceneFactory());
}

TEST (FactoryTest, SceneFactorymakeScene) { 
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    true};
    
    auto factory = SceneFactory();
    auto scene = factory.makeScene(test_game);
    
    ASSERT_TRUE(scene);
    
}

TEST (FactoryTest, SceneFactorymakeSpecial) { 
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    true};
    
    auto factory = SceneFactory();
    auto scene = factory.makeSpecialScene(test_game, "TEST");
    
    ASSERT_TRUE(scene);
    
}

TEST (FactoryTest, SceneFactorymakeSpecialColors) { 
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    true};
    
    auto factory = SceneFactory(&makeSingleLetterSiren);
    auto scene = factory.makeScene(test_game);
    auto event = simulateTextEntered(2);
    scene->setActiveEvent(event, test_game);
    (*scene)(test_game);
    
    auto& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    auto color = window.last_text->getFillColor();

    auto special_scene = factory.makeSpecialScene(test_game, "TEST");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    special_scene->update();
    (*special_scene)(test_game);
    
    auto special_color = window.last_text->getFillColor();
    
    ASSERT_EQ(window.totalDraws, 5);
    ASSERT_EQ(color, special_color);
    
}
