#ifndef PC_CONSOLEHANDLER_HPP
#define PC_CONSOLEHANDLER_HPP

#include <string>
#include <sstream>

#include "PortalCredits/Util.hpp"

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
     * This enum contains the different visibility for the cursor
    */
    enum class CursorVisibility : unsigned char {
        Invisible,
        Visible,
        StrongVisible
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
             * @return a reference to the handler
            */
            ConsoleHandler& setBackgroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b);

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
             * Updates the cursor visibility
             * @param visibility The new visibility
             * @return a reference to the handler
            */
            ConsoleHandler& setCursorVisibility(CursorVisibility visibility);

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