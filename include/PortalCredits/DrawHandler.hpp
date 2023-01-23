#ifndef PC_DRAWHANDLER_HPP
#define PC_DRAWHANDLER_HPP

#include <vector>
#include <string>

namespace PortalCredits {
    enum class PortalSymbols: unsigned char;
    class ConsoleHandler;

    struct Rect {
        int x, y;
        int width, height;
    };

    /**
     * This enum contains the three drawing areas
    */
    enum class DrawArea : unsigned char {
        //The lyrics in the left half
        Lyrics,
        //The credits in the top right corner
        Credits,
        //The logo in the bottom right corner
        Logo,
        //The whole screen used in the main menu
        Menu
    };

    /**
     * This class handles the drawing of the
     * outlines and the text
    */
    class DrawHandler {
        public:
            /**
             * Create a Draw handler
             * @param console The console handler
             * @param drawModern Whether the outlines should be drawn in a modern way
            */
            DrawHandler(ConsoleHandler& console, const bool& drawModern) : console(console), drawModern(drawModern) {}

            /**
             * Finishes the console initialization
            */
            void init();

            /**
             * Draws the outlines for the text
             * @param drawMenu Draw the menu outlines instead of the lyrics and credits
            */
            void drawOutlines(const bool& drawMenu = false);

            /**
             * Draws the specified symbol to the screen
             * @param symbol The symbol to use
            */
            void drawSymbol(PortalSymbols symbol);

            /**
             * Draws the specified title sequence to the screen
             * @param drawAboutTitle Whether to draw the about title rather than the main title
            */
            void drawTitle(const bool& drawAboutTitle);

            /**
             * Draw text in the specified area
             * @param area The area to draw to (NOT Logo)
             * @param text The text, splitted in lines
             * @param stringIndex The index of the current line
             * @param stringPosition The index of the current char in the current line
            */
            void drawText(DrawArea area, const std::vector<std::string>& text, const size_t& stringIndex, const size_t& stringPosition);

            /**
             * Draw the license text
             * @param info The license info
             * @param stringIndex The index of the starting line
            */
            void drawLicenseText(const LicenseInfo& info, const size_t& stringIndex);

            /**
             * Queries the draw mode
             * @return Whether the outlines are drawn in a modern way
            */
            bool isDrawnModern() {return drawModern;}

            /**
             * Sets the draw mode
             * @param drawModern Whether the outlines should be drawn in a modern way
            */
            void setDrawModern(const bool& drawModern) {this->drawModern = drawModern;}

            /**
             * Clears the specified drawing area
             * @param area The area to clear
            */
            void clearArea(DrawArea area) {clearArea(areas.at((int) area));}

            /**
             * Clears the specified drawing area
             * @param area The area to clear
            */
            void clearArea(const Rect& area);
        
        private:
            static const std::vector<Rect> outlineMain;
            static const std::vector<Rect> outlineMenu;
            static const std::vector<Rect> areas;
            static const std::string quitEditor;

            ConsoleHandler& console;
            bool drawModern;
    };
}

#endif //PC_DRAWHANDLER_HPP