#ifndef PC_RESOURCES_HPP
#define PC_RESOURCES_HPP

#include <array>
#include <vector>
#include <string>

namespace PortalCredits {

    /**
     * This struct contains timing information
     * for the Lyrics and Credits
    */
    struct TimeInfo {
        //The index of the page (unused for Credits) and the line (unused for logos)
        size_t pageIndex, stringIndex;
        /**
         * The start and end position inside the string
         * (Can be used for multiple timings within a line)
        */
        size_t startPos, endPos;
        //The start and end time of the text
        double startTime, endTime;
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
     * This class contains the handles for the resources.
     * The definitions are generated with the
     * GenerateResources.py Script
    */
    class Resources {
        public:
            /**
             * This vector contains the Lyrics, split in pages and lines
            */
            static const std::vector<std::vector<std::string>> lyrics;

            /**
             * This vector contains the Credits, split in lines
            */
            static const std::vector<std::string> credits;

            /**
             * This vector contains a hexdump of the song audio file.
            */
            static const std::vector<unsigned char> stillAlive;

            /**
             * The start time of the audio (in seconds)
            */
            static const double audioStartTime;

            /**
             * This vector contains the timing information for the lyrics
            */
            static const std::vector<TimeInfo> timingLyrics;

            /**
             * This vector contains the timing information for the credits
             * Note: The TimeInfo doesn't use the pageIndex
            */
            static const std::vector<TimeInfo> timingCredits;

            /**
             * This vector contains the timing information for the logos
             * Note: The TimeInfo only uses the pageIndex and time codes
            */
            static const std::vector<TimeInfo> timingLogos;

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

#endif