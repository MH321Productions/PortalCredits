#ifndef PC_CONSOLEHANDLER_HPP
#define PC_CONSOLEHANDLER_HPP

#include <string>
#include <sstream>

#include <ncurses.h>

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
            ConsoleHandler() : prevWidth(0), prevHeight(0), isNcursesActive(false) {}

            /**
             * Initializes the console
            */
            void init();

            /**
             * Resets the console to the previous state
            */
            void close();

            /**
             * Clears the console buffer
            */
            void clearScreen();

            /**
             * Resizes the console window
             * @param width The width in characters
             * @param height The height in characters
            */
            void resize(const int& width, const int& height);

            /**
             * Sets the window background color to a specified rgb value
             * @param r The red value [0; 255]
             * @param g The green value [0; 255]
             * @param b The blue value [0;255]
            */
            void setBackgroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b);

            /**
             * Sets the window foregound color to a specified rgb value
             * @param r The red value [0; 255]
             * @param g The green value [0; 255]
             * @param b The blue value [0;255]
            */
            void setForegroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b);

            /**
             * Sets the cursor position
             * @param x The x coordinate
             * @param y The y coordinate
            */
            void setCursorPosition(const int& x, const int& y);

            /**
             * Updates the cursor visibility
             * @param visibility The new visibility
            */
            void setCursorVisibility(CursorVisibility visibility);

            /**
             * Returns a pressed char. This method blocks until a key is pressed
             * @return A pressed char
            */
            int getChar();

            /**
             * Refreshes the console, i.e. makes the changes visible
            */
            void update();

            /**
             * Queries the state of the ncurses library
             * @return Whether ncurses is active
            */
            bool isActive() {return isNcursesActive;}

            //Operators

            friend ConsoleHandler& operator << (ConsoleHandler& handler, const Pos& pos);
            friend ConsoleHandler& operator << (ConsoleHandler& handler, const std::string& str);
            template<typename T> friend ConsoleHandler& operator << (ConsoleHandler& handler, const T& val);
        
        private:
            int prevWidth, prevHeight;
            bool isNcursesActive;
            std::ostringstream str;
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
        addstr(handler.str.str().c_str());
        handler.str.str("");
        handler.str.clear();

        return handler;
    }
}

#endif //PC_CONSOLEHANDLER_HPP