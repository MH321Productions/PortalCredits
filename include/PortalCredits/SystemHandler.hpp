#ifndef PC_UTIL_HPP
#define PC_UTIL_HPP

#include <vector>
#include <array>
#include <string>

#ifdef PC_WINDOWS
#include "PortalCredits/WinInclude.hpp"
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace PortalCredits {

    /**
     * This class configures the console on different systems
    */
    class SystemHandler {
        public:
            /**
             * Init the console
             * @return If everything was successful
            */
            bool init();

            /**
             * Resets the console
            */
            void close();

            /**
             * Query the console size
            */
            void getSize(int* width, int* height);

            /**
             * Query the console window's title
             * @return The title
            */
            std::string getWindowTitle();

            #ifdef PC_WINDOWS
            /**
             * Resizes the console and its window
             * @param width The new width in characters
             * @param height The new height in characters
            */
            bool resize(const int& width, const int& height);
            #endif
        
        private:
            #ifdef PC_WINDOWS
            HANDLE hIn, hOut;
            DWORD origIn, origOut;
            long origStyle;
            #else
            struct termios origAttr;
            #endif
    };
}

#endif //PC_UTIL_HPP