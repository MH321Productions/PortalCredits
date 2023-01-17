#include <iostream>

#include "PortalCredits/SoundHandler.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

namespace PortalCredits {

    bool SoundHandler::load() {
        loaded = music.openFromMemory(Resources::stillAlive.data, Resources::stillAlive.size);
        return loaded;
    }

    void SoundHandler::play() {
        if (loaded) music.play();
    }

    void SoundHandler::pause() {
        if (loaded) music.pause();
    }

    void SoundHandler::stop() {
        if (loaded) music.stop();
    }
}