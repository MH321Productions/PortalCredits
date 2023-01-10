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

    /**
     * This enum contains all ASCII art symbols
     * that are drawn in the bottom right corner
    */
    enum class PortalSymbols : unsigned char {
        ApertureLogo,
        Radioactive,
        Atom,
        HeartBroken,
        Fire,
        Check,
        Explosion,
        BlackMesa,
        Cake,
        Turret
    };

    /**
     * A singleton class containing
     * the definitions for the ASCII art
     * symbols declared in the PortalSymbols
     * enum
    */
    class Symbols {
        public:
            /**
             * Returns the ASCII art for the given symbol
             * @param symbol The symbol to use
             * @return The symbol, splitted in lines
            */
            static std::vector<std::string> getSymbol(PortalSymbols symbol);
        
        private:
            static const std::array<std::vector<std::string>, 10> symbols;
    };
}

#endif //PC_UTIL_HPP