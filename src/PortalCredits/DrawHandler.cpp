#include <iostream>

#include <ncurses.h>

#include "PortalCredits/DrawHandler.hpp"
#include "PortalCredits/ConsoleHandler.hpp"
#include "PortalCredits/Util.hpp"

using namespace std;

namespace PortalCredits {

    const vector<Rect> DrawHandler::outline = {
        {0, 0, 50, 50},
        {50, 0, 50, 25}
    };

    void DrawHandler::init() {
        console.init();
        console.setBackgroundColor(0, 0, 0);
        console.setForegroundColor(219, 164, 10);
        console.resize(100, 50);
    }

    void DrawHandler::drawOutlines() {
        //Change characters based on draw mode
        chtype cHorizontal, cVertical;
        chtype cTopLeft, cTopRight;
        chtype cBottomLeft, cBottomRight;
        if (drawModern) {
            cHorizontal = ACS_HLINE;
            cVertical = ACS_VLINE;
            cTopLeft = ACS_ULCORNER;
            cTopRight = ACS_URCORNER;
            cBottomLeft = ACS_LLCORNER;
            cBottomRight = ACS_LRCORNER;
        } else {
            cHorizontal = '-';
            cVertical = '|';
            cTopLeft = '-';
            cTopRight = ' ';
            cBottomLeft = '-';
            cBottomRight = ' ';
        }

        //Draw horizontal lines
        for (const Rect& r: outline) {
            int i;

            for (i = 1; i < r.width - 1; i++) {
                mvaddch(r.y, r.x + i, cHorizontal);                         //Top line
                mvaddch(r.y + r.height - 1, r.x + i, cHorizontal);          //Bottom line
            }

            for (i = 1; i < r.height - 1; i++) {
                mvaddch(r.y + i, r.x, cVertical);                           //Left line
                mvaddch(r.y + i, r.x + r.width - 1, cVertical);             //Right line
            }

            mvaddch(r.y, r.x, cTopLeft);                                    //Top left corner
            mvaddch(r.y, r.x + r.width - 1, cTopRight);                     //Top right corner
            mvaddch(r.y + r.height - 1, r.x, cBottomLeft);                  //Bottom left corner
            mvaddch(r.y + r.height - 1, r.x + r.width - 1, cBottomRight);   //Bottom right corner
        }
    }

    void DrawHandler::drawSymbol(PortalSymbols symbol) {
        vector<string> text = Symbols::getSymbol(symbol);

        for (int i = 0; i < text.size(); i++) mvaddstr(27 + i, 55, text.at(i).c_str());
    }
}