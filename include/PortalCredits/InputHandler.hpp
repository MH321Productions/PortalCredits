#ifndef PC_INPUTHANDLER_HPP
#define PC_INPUTHANDLER_HPP

#include <thread>
#include <mutex>
#include <vector>

#ifdef PC_WINDOWS
#include <array>
#include "PortalCredits/WinInclude.hpp"
#endif

namespace PortalCredits {

    /**
     * This enum contains alias codes for the arrow keys
     * and key constants
    */
    enum Keys : int {
        ArrowLeft = -5,
        ArrowRight,
        ArrowDown,
        ArrowUp,
        Enter = '\r',
        Space = ' ',
        Quit = 'q'
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

            #ifdef PC_WINDOWS
            HANDLE hIn;
            std::array<INPUT_RECORD, 128> events;

            int processKeyEvent(const KEY_EVENT_RECORD& record);
            int processMouseEvent(const MOUSE_EVENT_RECORD& record);
            #endif

            void readThread();
    };
}

#endif //PC_INPUTHANDLER_HPP