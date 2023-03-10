#ifndef PC_CONSOLEHANDLER_HPP
#define PC_CONSOLEHANDLER_HPP

#include <string>
#include <sstream>

#include "PortalCredits/SystemHandler.hpp"

namespace PortalCredits {

    /**
     * This struct contains a position (normally for the cursor).
     * It can be used to move the cursor through
     * console << pos << "Text"
    */
    struct Pos {
        int x;
        int y;
    };

    /**
     * This enum contains the different cursor types
    */
    enum class CursorType : unsigned char {
        //The system's default type
        Default,
        //A blinking block character (default in xterm and its derivates)
        BlinkingBlock,
        //A block character
        SteadyBlock,
        //A blinking underline character (default in Windows terminal)
        BlinkingUnderline,
        //An underline character
        SteadyUnderline,
        //A blinking bar (|) character
        BlinkingBar,
        //A bar (|) character
        SteadyBar
    };

    /**
     * This class handles the communication with the console
     * through escape codes and WINAPI calls
    */
    class ConsoleHandler {
        public:
            ConsoleHandler() : prevWidth(0), prevHeight(0), active(false) {}

            /**
             * Initializes the console
             * @return If everything was successful
            */
            bool init();

            /**
             * Resets the console to the previous state
            */
            void close();

            /**
             * Updates the console window's title
             * @param title The new title
            */
            void setTitle(const std::string& title);

            /**
             * Clears the console buffer
             * @return a reference to the handler
            */
            ConsoleHandler& clearScreen();

            /**
             * Resizes the console window
             * @param width The width in characters
             * @param height The height in characters
             * @return a reference to the handler
            */
            ConsoleHandler& resize(const int& width, const int& height);

            /**
             * Sets the window background color to a specified rgb value
             * @param r The red value [0; 255]
             * @param g The green value [0; 255]
             * @param b The blue value [0;255]
             * @param clear When true, the screen is cleared, making the given color the background color for the whole window
             * @return a reference to the handler
            */
            ConsoleHandler& setBackgroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b, const bool& clear = false);

            /**
             * Sets the window foregound color to a specified rgb value
             * @param r The red value [0; 255]
             * @param g The green value [0; 255]
             * @param b The blue value [0;255]
             * @return a reference to the handler
            */
            ConsoleHandler& setForegroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b);

            /**
             * Sets the cursor position
             * @param x The x coordinate
             * @param y The y coordinate
             * @return a reference to the handler
            */
            ConsoleHandler& moveCursor(const int& x, const int& y);

            /**
             * Writes text to the current cursor position
             * @param text The text to write
             * @return a reference to the handler
            */
            ConsoleHandler& write(const std::string& text);

            /**
             * Clear a horizontal line, i.e. fill it with spaces
             * @param width The width of the line
            */
            ConsoleHandler& hline(const size_t& width);

            /**
             * Updates the cursor visibility
             * @param showCursor Whether to show the cursor
             * @return a reference to the handler
            */
            ConsoleHandler& setCursorVisibility(const bool& showCursor);

            /**
             * Updates the cursor type
             * @param type The new type
             * @return a reference to the handler
            */
            ConsoleHandler& setCursorType(CursorType type);

            /**
             * Returns a pressed char. This method blocks until a key is pressed
             * @return A pressed char
            */
            int getChar();

            /**
             * Refreshes the console, i.e. makes the changes visible
             * @return a reference to the handler
            */
            ConsoleHandler& update();

            /**
             * Queries the state of the console
             * @return Whether the console raw mode is active
            */
            bool isActive() {return active;}

            //Operators

            friend ConsoleHandler& operator << (ConsoleHandler& handler, const Pos& pos);
            friend ConsoleHandler& operator << (ConsoleHandler& handler, const std::string& str);
            template<typename T> friend ConsoleHandler& operator << (ConsoleHandler& handler, const T& val);
        
        private:
            int prevWidth, prevHeight;
            std::string prevTitle;
            bool active;
            std::ostringstream str;

            SystemHandler sys;
    };

    /**
     * Moves the cursor position
    */
    ConsoleHandler& operator << (ConsoleHandler& handler, const Pos& pos);

    /**
     * Write something to the console
    */
    ConsoleHandler& operator << (ConsoleHandler& handler, const std::string& str);

    /**
     * Write something to the console
    */
    template<typename T> ConsoleHandler& operator << (ConsoleHandler& handler, const T& val) {
        handler.str << val;
        handler.write(handler.str.str());
        handler.str.str("");
        handler.str.clear();

        return handler;
    }
}

#endif //PC_CONSOLEHANDLER_HPP