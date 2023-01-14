#include <iostream>

#include "PortalCredits/SoundHandler.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

namespace PortalCredits {

    bool SoundHandler::start() {
        if (!music.openFromMemory(Resources::stillAlive.data(), Resources::stillAlive.size())) return false;

        music.play();
        
        while (music.getStatus() == sf::SoundSource::Status::Playing);
        
        return true;
    }

    void SoundHandler::stop() {
        music.stop();
    }
}