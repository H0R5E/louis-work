
#pragma once

#include <memory>
#include <SFML/Audio.hpp>

class Sound {
public:
    virtual void play () = 0;
    virtual void pause () = 0;
    virtual void stop () = 0;
    virtual void setBuffer (const sf::SoundBuffer &buffer) = 0;
    virtual void setLoop (bool loop) = 0;
    virtual ~Sound () = default;
};

class SoundAdapter: public Sound, private sf::Sound
{
public:
    SoundAdapter() :
        sf::Sound() {};
    virtual void play () override {
        sf::Sound::play();
    };
    virtual void pause () override {
        sf::Sound::pause();
    };
    virtual void stop () override {
        sf::Sound::stop();
    }
    virtual void setBuffer (const sf::SoundBuffer &buffer) override {
        sf::Sound::setBuffer(buffer);
    };
    virtual void setLoop (bool loop) override {
        sf::Sound::setLoop(loop);
    };
};


class SoundMakerBase {
public:
    virtual ~SoundMakerBase () = default;
    virtual std::unique_ptr<Sound> Get () = 0;
};

template<typename T=SoundAdapter>
class SoundMaker : public SoundMakerBase {
public:
    std::unique_ptr<Sound> Get () override;
};

template<typename T>
std::unique_ptr<Sound> SoundMaker<T>::Get() {
    auto sound = std::make_unique<T>();
    return sound;
}
