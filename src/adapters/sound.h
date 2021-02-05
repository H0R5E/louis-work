
#pragma once

#include <memory>
#include <SFML/Audio.hpp>

#include "polymorphic_value.h"

using namespace isocpp_p0201;

class Sound {
public:
    virtual void play () = 0;
    virtual void pause () = 0;
    virtual void stop () = 0;
    virtual void setBuffer (const sf::SoundBuffer &buffer) = 0;
    virtual void setLoop (bool loop) = 0;
    virtual sf::Sound::Status getStatus () const = 0;
    virtual ~Sound () = default;
};

class SoundAdapter: public Sound, private sf::Sound
{
public:
    SoundAdapter() :
        sf::Sound() {};
    SoundAdapter(const SoundAdapter& copy) :
        sf::Sound(copy) {};
    void play () override {
        sf::Sound::play();
    };
    void pause () override {
        sf::Sound::pause();
    };
    void stop () override {
        sf::Sound::stop();
    }
    void setBuffer (const sf::SoundBuffer &buffer) override {
        sf::Sound::setBuffer(buffer);
    };
    void setLoop (bool loop) override {
        sf::Sound::setLoop(loop);
    };
    sf::Sound::Status getStatus () const override {
        return sf::Sound::getStatus();
    };
    SoundAdapter& operator = (const SoundAdapter& right) {
        sf::Sound::operator= (right);
        return *this;
    }
};

class SoundMakerBase {
public:
    virtual ~SoundMakerBase () = default;
    virtual polymorphic_value<Sound> Get () = 0;
};

template<typename T=SoundAdapter>
class SoundMaker : public SoundMakerBase {
public:
    polymorphic_value<Sound> Get () override;
};

template<typename T>
polymorphic_value<Sound> SoundMaker<T>::Get() {
    auto sound = make_polymorphic_value<Sound, T>();
    return sound;
}
