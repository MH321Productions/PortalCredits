#ifndef PC_SOUNDHANDLER_HPP
#define PC_SOUNDHANDLER_HPP

#include <SFML/Audio.hpp>

namespace PortalCredits {

    /**
     * This class handles the sfml sound resource
    */
    class SoundHandler {
        public:
            /**
             * Loads the music and starts it
             * @return If the music could be loaded
            */
            bool start();

            /**
             * Stops the music if it isready started
            */
            void stop();

        private:
            sf::Music music;
    };
}

#endif //PC_SOUNDHANDLER_HPP