#ifndef PC_SOUNDHANDLER_HPP
#define PC_SOUNDHANDLER_HPP

#include <SFML/Audio.hpp>

namespace PortalCredits {

    /**
     * This class handles the sfml sound resource
    */
    class SoundHandler {
        public:
            SoundHandler() : loaded(false) {}

            /**
             * Loads the music
             * @return Whether the load was successful
            */
            bool load();

            /**
             * Starts or resumes the music if it is loaded
            */
            void play();

            /**
             * Pauses the music if it is running
            */
            void pause();

            /**
             * Stops the music if it is running
            */
            void stop();

        private:
            sf::Music music;
            bool loaded;
    };
}

#endif //PC_SOUNDHANDLER_HPP