#ifndef PC_DRAWHANDLER_HPP
#define PC_DRAWHANDLER_HPP

#include <vector>

//#include "PortalCredits/ConsoleHandler.hpp"

namespace PortalCredits {
    enum class PortalSymbols: unsigned char;
    class ConsoleHandler;

    struct Rect {
        int x, y;
        int width, height;
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
            */
            void drawOutlines();

            /**
             * Draws the specified symbol to the screen
             * @param symbol The symbol to use
            */
            void drawSymbol(PortalSymbols symbol);

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
        
        private:
            static const std::vector<Rect> outline;

            ConsoleHandler& console;
            bool drawModern;
    };
}

#endif //PC_DRAWHANDLER_HPP