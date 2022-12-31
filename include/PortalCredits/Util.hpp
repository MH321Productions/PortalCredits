#ifndef PC_UTIL_HPP
#define PC_UTIL_HPP

#include <vector>
#include <array>
#include <string>

namespace PortalCredits {

    /**
     * A singleton class with util methods
    */
    class Util {
        public:
            /**
             * Prepares the program for Windows use
            */
            static void setupWindows();
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