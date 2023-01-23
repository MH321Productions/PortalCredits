#include <iostream>

#include "PortalCredits/App.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

namespace PortalCredits {

    void PortalCreditsApp::renderMenu() {
        if (stateChanged) {
            draw.clearArea(DrawArea::Menu);
            draw.setDrawModern(true);
            draw.drawOutlines(true);
            if (mode == AppMode::AboutMenu) {
                draw.drawTitle(true);

                //Draw about text
                for (int i = 0; i < Resources::textAbout.size(); i++) {
                    console.moveCursor(13, 20 + i).write(Resources::textAbout.at(i));
                }
            } else {
                draw.drawTitle(false);
            }
        }

        const vector<MenuInfo>& entries = mode == AppMode::MainMenu ? Resources::menuMain : Resources::menuAbout;
        int& selectedEntry = mode == AppMode::MainMenu ? menuMainPos : menuAboutPos;

        for (int i = 0; i < entries.size(); i++) {
            const MenuInfo& info = entries.at(i);
            if (i == selectedEntry) {
                console.moveCursor(info.x, info.y);
                console.setBackgroundColor(COLOR_YELLOW).setForegroundColor(COLOR_BLACK);
                console.write(info.text);
                console.setForegroundColor(COLOR_YELLOW).setBackgroundColor(COLOR_BLACK);
            } else {
                console.moveCursor(info.x, info.y);
                console.write(info.text);
            }
        }
    }

    void PortalCreditsApp::renderTextFile() {
        if (stateChanged) {
            draw.clearArea(DrawArea::Menu);
            draw.setDrawModern(true);
            draw.drawOutlines(true);
        }

        const LicenseInfo& text =
            mode == AppMode::Conditions ? Resources::conditions
             : mode == AppMode::License ? Resources::license
                                        : Resources::warranty;
        
        draw.clearArea(DrawArea::Menu);
        draw.drawLicenseText(text, textPos);
    }

    void PortalCreditsApp::renderMainProgram() {
        if (stateChanged) {
            console.clearScreen();
            draw.setDrawModern(mode == AppMode::MainProgramModern);
            draw.drawOutlines();
            console.setCursorType(CursorType::BlinkingUnderline).setCursorVisibility(true);
        }

        if (mainInfo.logo && mainInfo.logoClear) {
            draw.clearArea(DrawArea::Logo);
            draw.drawSymbol(PortalSymbols(mainInfo.logo->pageIndex));
            mainInfo.logoClear = false;
        }
        if (mainInfo.lyrics) {
            if (mainInfo.lyricsClear) {
                draw.clearArea(DrawArea::Lyrics);
                mainInfo.lyricsClear = false;
            }

            draw.drawText(
                DrawArea::Lyrics, Resources::lyrics.at(mainInfo.lyrics->pageIndex),
                mainInfo.lyrics->stringIndex, mainInfo.lyricsPos + mainInfo.lyrics->startPos
            );
        }
        if (mainInfo.credits) {
            if (mainInfo.creditsClear) {
                draw.clearArea(DrawArea::Credits);
                mainInfo.creditsClear = false;
            }

            draw.drawText(
                DrawArea::Credits, Resources::credits,
                mainInfo.credits->stringIndex, mainInfo.creditsPos + mainInfo.credits->startPos
            ); 
        }
    }

}