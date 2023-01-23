#include <iostream>
#include <sstream>

#include "PortalCredits/DrawHandler.hpp"
#include "PortalCredits/ConsoleHandler.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

namespace PortalCredits {

    const vector<Rect> DrawHandler::outlineMain = {
        {0, 0, 50, CONSOLE_HEIGHT},
        {50, 0, 50, 21}
    };

    const vector<Rect> DrawHandler::outlineMenu = {
        {0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT + 1}
    };

    const vector<Rect> DrawHandler::areas = {
        {2, 2, 47, 37},
        {51, 2, 46, 18},
        {55, 21, 45, 23},
        {2, 2, CONSOLE_WIDTH - 3, 39}
    };

    const string DrawHandler::quitEditor = "Press 'q' to quit text viewer";

    void DrawHandler::init() {
        console.init();
        console.setTitle("PortalCredits");
        console.resize(100, 41);
        console.setBackgroundColor(0, 0, 0, true);
        console.setForegroundColor(219, 164, 10);
    }

    void DrawHandler::drawOutlines(const bool& drawMenu) {
        //Change characters based on draw mode
        string cHorizontal, cVertical;
        string cTopLeft, cTopRight;
        string cBottomLeft, cBottomRight;
        if (drawModern) {
            cout << "\033(0"; //Switch to line drawing character set
            
            cHorizontal = 0x71;     // -> "\u2500"
            cVertical = 0x78;       // -> "\u2502"
            cTopLeft = 0x6C;        // -> "\u250C"
            cTopRight = 0x6B;       // -> "\u2510"
            cBottomLeft = 0x6D;     // -> "\u2514"
            cBottomRight = 0x6A;    // -> "\u2518"
        } else {
            cHorizontal = '-';
            cVertical = '|';
            cTopLeft = '-';
            cTopRight = ' ';
            cBottomLeft = '-';
            cBottomRight = ' ';
        }

        for (const Rect& r: (drawMenu ? outlineMenu : outlineMain)) {
            int i;

            for (i = 1; i < r.width - 1; i++) {
                console.moveCursor(r.x + i, r.y).write(cHorizontal); //Top line
                console.moveCursor(r.x + i, r.y + r.height - 1).write(cHorizontal); //Bottom line
            }

            for (i = 1; i < r.height - 1; i++) {
                console.moveCursor(r.x, r.y + i).write(cVertical); //Left line
                console.moveCursor(r.x + r.width - 1, r.y + i).write(cVertical); //Right line
            }

            console.moveCursor(r.x, r.y).write(cTopLeft);
            console.moveCursor(r.x + r.width - 1, r.y).write(cTopRight);
            console.moveCursor(r.x, r.y + r.height - 1).write(cBottomLeft);
            console.moveCursor(r.x + r.width - 1, r.y + r.height - 1).write(cBottomRight);
        }

        if (drawModern) cout << "\033(B"; //Switch to US-ASCII
    }

    void DrawHandler::drawSymbol(PortalSymbols symbol) {
        vector<string> text = Resources::getSymbol(symbol);

        for (int i = 0; i < text.size(); i++) console.moveCursor(55, 21 + i).write(text.at(i));
    }

    void DrawHandler::drawTitle(const bool& drawAboutTitle) {
        vector<string> text = drawAboutTitle ? Resources::titleAbout : Resources::titleMain;

        //Switch to line drawing character set
        cout << "\033(0";

        for (int i = 0; i < text.size(); i++) console.moveCursor(3, 2 + i).write(text.at(i));

        cout << "\033(B"; //Switch to US-ASCII
    }

    void DrawHandler::drawText(DrawArea area, const vector<string>& text, const size_t& stringIndex, const size_t& stringPosition) {
        if (area == DrawArea::Logo) return; //Logo does nothing

        const Rect& r = areas.at((int) area);
        int startY, startIndex, numLines, drawPos;
        bool writePreviousLines;

        if (area == DrawArea::Credits) { //Draw from bottom to top
            //Determine text position
            if (stringIndex < r.height) {
                startY = r.y + r.height - stringIndex - 1;
                startIndex = 0;
            } else {
                startY = r.y;
                startIndex = stringIndex - r.height + 1;
            }
            numLines = stringIndex - startIndex;
            drawPos = r.y + r.height - 1;

            //Only write previous lines if they are available and if a new line is drawn
            writePreviousLines = stringIndex && !stringPosition;
        } else { //Draw from top to bottom
            startY = r.y;
            startIndex = 0;
            numLines = stringIndex;
            drawPos = r.y + stringIndex;
            writePreviousLines = false; //Never write previous lines since they aren't overwritten
        }

        
        if (writePreviousLines) {
                for (int i = 0; i < numLines; i++) { //previous lines
                    console.moveCursor(r.x, startY + i).write(text.at(startIndex + i));
                }
            }

        console.moveCursor(r.x, drawPos);
        //Only draw text if it is non-empty the index is non-zero
        if (text.at(stringIndex).size() && stringPosition) for (int i = 0; i <= stringPosition; i++) console << text.at(stringIndex).at(i);
    }

    void DrawHandler::drawLicenseText(const LicenseInfo& info, const size_t& stringIndex) {
        const Rect& r = areas.at((int) DrawArea::Menu);

        int textHeight = r.height - 1;
        int numLines = info.text.size() < textHeight ? info.text.size() : textHeight;
        int bottomPos = r.y + textHeight;

        //Draw normal text
        for (int i = 0; i < numLines; i++) {
            console.moveCursor(r.x, r.y + i).write(info.text.at(stringIndex + i));
        }

        //Draw status line
        console.moveCursor(r.x, bottomPos);
        console.setBackgroundColor(COLOR_YELLOW).setForegroundColor(COLOR_BLACK).hline(r.width);
        
        console.moveCursor(r.x + 1, bottomPos).write(info.title);

        ostringstream str;
        str << "Lines: " << (stringIndex + 1) << '-' << (stringIndex + numLines) << '/' << info.text.size();
        string lines = str.str();
        int linePos = (r.width / 2) - (lines.size() / 2);
        console.moveCursor(r.x + linePos, bottomPos).write(lines);

        console.moveCursor(r.x + r.width - quitEditor.size() - 1, bottomPos).write(quitEditor);

        console.setBackgroundColor(COLOR_BLACK).setForegroundColor(COLOR_YELLOW);
    }

    void DrawHandler::clearArea(const Rect& area) {
        for (int i = 0; i < area.height; i++) {
            console.moveCursor(area.x, area.y + i);
            console.hline(area.width);
        }
    }
}