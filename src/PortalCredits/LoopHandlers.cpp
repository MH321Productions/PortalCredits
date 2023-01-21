#include <iostream>
#include <algorithm>

#include "PortalCredits/App.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

namespace PortalCredits {

    bool PortalCreditsApp::loopMenu() {
        bool ret = false;
        if (stateChanged) {
            console.setCursorVisibility(false);
            menuMainPos = clamp(menuMainPos, 0, 3);
            menuAboutPos = clamp(menuAboutPos, 0, 3);
            if (menuAboutPos == 3) menuAboutPos = 0;
            ret = true;
        }

        //Evaluate events
        if (mode == AppMode::MainMenu) {
            for (const int& i: events) {
                if (i == ArrowDown) {
                    menuMainPos = clamp(menuMainPos + 1, 0, 3);
                    ret = true;
                } else if (i == ArrowUp) {
                    menuMainPos = clamp(menuMainPos - 1, 0, 3);
                    ret = true;
                } else if (i == Enter) {
                    const MenuInfo& info = Resources::menuMain.at(menuMainPos);
                    changeState(info.newMode);
                    break;
                }
            }
        } else {
            for (const int& i: events) {
                if (i == ArrowRight) {
                    menuAboutPos = clamp(menuAboutPos + 1, 0, 3);
                    ret = true;
                } else if (i == ArrowLeft) {
                    menuAboutPos = clamp(menuAboutPos - 1, 0, 3);
                    ret = true;
                } else if (i == Enter) {
                    const MenuInfo& info = Resources::menuAbout.at(menuAboutPos);
                    changeState(info.newMode);
                }
            }
        }

        return ret;
    }

    bool PortalCreditsApp::loopTextFile() {
        return true;
    }

    bool PortalCreditsApp::loopMainProgram() {
        return true;
    }

}