#ifndef PC_INPUTHANDLER_HPP
#define PC_INPUTHANDLER_HPP

#include <thread>
#include <mutex>
#include <vector>

namespace PortalCredits {

    /**
     * This enum contains alias codes for the arrow keys
    */
    enum ArrowKeys : int {
        ArrowLeft = -5,
        ArrowRight,
        ArrowDown,
        ArrowUp
    };

    /**
     * This class handles
     * the async input reading
    */
    class InputHandler {
        public:
            InputHandler() : running(false), hasEsc(false), hasCsi(false) {}

            /**
             * Starts the input listener thread
            */
            void start();

            /**
             * Stops the input listener thread
            */
            void stop();

            /**
             * Query the read chars
             * @param clearChars Whether the read data should be cleared directly
             * @return A vector of integers
            */
            std::vector<int> getChars(const bool& clearChars = true);

            /**
             * Clear the read chars
            */
            void clearChars();

        private:
            std::vector<int> data;
            std::mutex m;
            std::thread t;
            bool running;
            bool hasEsc, hasCsi;

            void readThread();
    };
}

#endif //PC_INPUTHANDLER_HPP