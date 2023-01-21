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
            draw.drawTitle(mode == AppMode::AboutMenu);
        }

        const vector<MenuInfo>& entries = mode == AppMode::MainMenu ? Resources::menuMain : Resources::menuAbout;
        int& selectedEntry = mode == AppMode::MainMenu ? menuMainPos : menuAboutPos;

        for (int i = 0; i < entries.size(); i++) {
            const MenuInfo& info = entries.at(i);
            if (i == selectedEntry) {
                console.moveCursor(info.x, info.y);
                console.setBackgroundColor(219, 164, 10).setForegroundColor(0, 0, 0);
                console.write(info.text);
                console.setForegroundColor(219, 164, 10).setBackgroundColor(0, 0, 0);
            } else {
                console.moveCursor(info.x, info.y);
                console.write(info.text);
            }
        }
    }

    void PortalCreditsApp::renderTextFile() {

    }

    void PortalCreditsApp::renderMainProgram() {

    }

}