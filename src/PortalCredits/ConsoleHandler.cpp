#include <iostream>
#include <iomanip>

#include "PortalCredits/ConsoleHandler.hpp"
#include "PortalCredits/Util.hpp"

using namespace std;

namespace PortalCredits {

    bool ConsoleHandler::init() {
        if (active) return true;

        if (!sys.init()) return false;

        cout << "\033[?1049h" << flush; //Enable alternative buffer

        //Save terminal size and title for later
        sys.getSize(&prevWidth, &prevHeight);
        prevTitle = sys.getWindowTitle();

        active = true;
        return true;
    }

    void ConsoleHandler::close() {
        if (!active) return;

        cout << "\033[?1049l";  //Disable alternative buffer, restore previous state
        cout << "\033]110\007"; //Reset foreground color
        cout << "\033]111\007"; //Reset background color
        
        resize(prevWidth, prevHeight);
        setTitle(prevTitle);

        sys.close();
    }

    void ConsoleHandler::setTitle(const string& title) {
        cout << "\033]2;" << title << "\033\\";
    }

    ConsoleHandler& ConsoleHandler::clearScreen() {
        //Move cursor to (0, 0) and clear everything underneath it
        cout << "\033[0;0H\033[0J" << flush;

        return *this;
    }

    ConsoleHandler& ConsoleHandler::resize(const int& width, const int& height) {
        #ifdef PC_WINDOWS
        sys.resize(width, height);
        #else
        cout << "\033[8;" << height << ';' << width << 't' << flush; //Resize terminal window through escape code
        #endif

        return *this;
    }

    ConsoleHandler& ConsoleHandler::setBackgroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b) {
        //Set the background color and clear the screen
        cout << "\033[48;2;" << (int) r << ';' << (int) g << ';' << (int) b << 'm';
        cout << "\033[0;0H\033[0J";

        return *this;
    }

    ConsoleHandler& ConsoleHandler::setForegroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b) {
        cout << "\033[38;2;" << (int) r << ';' << (int) g << ';' << (int) b << 'm';

        return *this;
    }

    ConsoleHandler& ConsoleHandler::moveCursor(const int& x, const int& y) {
        cout << "\033[" << y << ';' << x << 'H';

        return *this;
    }

    ConsoleHandler& ConsoleHandler::write(const string& text) {
        cout << text;

        return *this;
    }

    ConsoleHandler& ConsoleHandler::setCursorVisibility(const bool& showCursor) {
        //ESC[?25h -> Show cursor
        //ESC[?25l -> Hide cursor
        cout << "\033[?25" << (showCursor ? 'h' : 'l');

        return *this;
    }

    ConsoleHandler& ConsoleHandler::setCursorType(CursorType type) {
        cout << "\033[" << (int) type << " q";

        return *this;
    }

    int ConsoleHandler::getChar() {
        return cin.get();
    }

    ConsoleHandler& ConsoleHandler::update() {
        cout.flush();

        return *this;
    }

    //Operators

    ConsoleHandler& operator << (ConsoleHandler& handler, const string& str) {
        handler.write(str);
        return handler;
    }

    ConsoleHandler& operator<<(ConsoleHandler& handler, const Pos& pos) {
        if (handler.active) handler.moveCursor(pos.x, pos.y);

        return handler;
    }
}