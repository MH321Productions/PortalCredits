#ifndef PC_RESOURCES_HPP
#define PC_RESOURCES_HPP

#include <array>
#include <vector>
#include <string>

namespace PortalCredits {

    enum class AppMode: unsigned char;

    /**
     * This struct contains timing information
     * for the Lyrics, Credits and Logos
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
     * This struct contains information
     * for a binary array
    */
    struct BinaryData {
        unsigned char* data;
        size_t size;
    };

    /**
     * This struct contains information
     * for a menu entry
    */
    struct MenuInfo {
        int x, y;
        std::string text;
        AppMode newMode;
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
            static const BinaryData stillAlive;

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
             * This vector contains the GNU GPLv3 License text, splitted in lines
            */
            static const std::vector<std::string> license;

            /**
             * This vector contains the sections 15 and 16 of the GPL (warranty and liability)
            */
            static const std::vector<std::string> warranty;

            /**
             * This vector contains the sections 4 to 6 of the GPL (redistributing conditions)
            */
            static const std::vector<std::string> conditions;

            /**
             * This vector contains the title screen text
             * Note: The text uses the Line drawing character set
            */
            static const std::vector<std::string> titleMain;

            /**
             * This vector contains the about screen text
             * Note: The text uses the Line drawing character set
            */
            static const std::vector<std::string> titleAbout;

            /**
             * This vector contains the menu entries for the main menu
            */
            static const std::vector<MenuInfo> menuMain;

            /**
             * This vector contains the menu entries for the about menu
            */
            static const std::vector<MenuInfo> menuAbout;

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