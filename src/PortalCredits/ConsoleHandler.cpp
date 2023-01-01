#include <iostream>
#include <iomanip>

#include "PortalCredits/ConsoleHandler.hpp"
#include "PortalCredits/Util.hpp"

using namespace std;

namespace PortalCredits {

    void ConsoleHandler::init() {
        if (isNcursesActive) return;

        Util::setupWindows();

        cout << "\033[?1049h" << flush; //Enable alternative buffer

        //Init ncurses
        initscr();
        cbreak();
        noecho();
        nonl();
        intrflush(stdscr, false);
        keypad(stdscr, true);
        isNcursesActive = true;

        //Save terminal size for later
        getmaxyx(stdscr, prevHeight, prevWidth);
    }

    void ConsoleHandler::close() {
        //Close ncurses
        if (isNcursesActive) {
            endwin();
            isNcursesActive = false;
        }

        cout << "\033[?1049l";  //Disable alternative buffer, restore previous state
        cout << "\033]110\007"; //Reset foreground color
        cout << "\033]111\007"; //Reset background color
        resize(prevWidth, prevHeight);
    }

    void ConsoleHandler::clearScreen() {
        if (isNcursesActive) clear();
    }

    void ConsoleHandler::resize(const int& width, const int& height) {
        cout << "\033[8;" << height << ';' << width << 't' << flush; //Resize terminal window through escape code

        if (isNcursesActive) resizeterm(height, width); //Resize ncurses window
    }

    void ConsoleHandler::setBackgroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b) {
        //ESC]11;#rrggbbBEL
        cout << "\033]11;#" << hex
        << setw(2) << setfill('0') << (int) r
        << setw(2) << setfill('0') << (int) (g)
        << setw(2) << setfill('0') << (int) (b) << "\007" << dec << flush;
    }

    void ConsoleHandler::setForegroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b) {
        //ESC]10;#rrggbbBEL
        cout << "\033]10;#" << hex
        << setw(2) << setfill('0') << (int) r
        << setw(2) << setfill('0') << (int) g
        << setw(2) << setfill('0') << (int) b << "\007" << dec << flush;
    }

    void ConsoleHandler::setCursorPosition(const int& x, const int& y) {
        if (isNcursesActive) move(y, x);
    }

    void ConsoleHandler::setCursorVisibility(CursorVisibility visibility) {
        if (isNcursesActive) curs_set((int) visibility);
    }

    int ConsoleHandler::getChar() {
        if (isNcursesActive) return getch();
        else return 0;
    }

    void ConsoleHandler::update() {
        if (isNcursesActive) refresh();
    }

    //Operators

    ConsoleHandler& operator << (ConsoleHandler& handler, const string& str) {
        if (handler.isNcursesActive) addstr(str.c_str());

        return handler;
    }

    ConsoleHandler& operator<<(ConsoleHandler& handler, const Pos& pos) {
        if (handler.isNcursesActive) handler.setCursorPosition(pos.x, pos.y);

        return handler;
    }
}