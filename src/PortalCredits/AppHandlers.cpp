#include <iostream>

#include "PortalCredits/App.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

namespace PortalCredits {

    void PortalCreditsApp::onEvent() {
        vector<int> data = input.getChars();

        for (const int& i: data) {
            //Only add relevant inputs to events
            switch (i) {
                case -1: //EOF (caused by CTRL + Z (on Windows)) -> Quit
                case 3: //Ctrl + C -> Quit
                case 'q': //Quit
                case 'Q': //Quit
                    quit();
                    break;
                
                case ArrowUp:
                case ArrowDown:
                case ArrowLeft:
                case ArrowRight:
                case ' ': //Space bar: Play/Pause
                case '\r': //Enter key pressed (No newline conversion)
                    events.push_back(i);
                    break;
            }
        }
    }

    void PortalCreditsApp::onLoop() {

    }

    void PortalCreditsApp::onRender() {

    }
}