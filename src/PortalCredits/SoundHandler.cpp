#include <iostream>

#include "PortalCredits/SoundHandler.hpp"
#include "Song.hpp"

using namespace std;

namespace PortalCredits {

    bool SoundHandler::start() {
        if (!music.openFromMemory(stillAlive.data(), stillAlive.size())) return false;

        music.play();
        
        while (music.getStatus() == sf::SoundSource::Status::Playing);
        
        return true;
    }

    void SoundHandler::stop() {
        music.stop();
    }
}