#include <iostream>

#include "PortalCredits/App.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;
using namespace std::chrono;

namespace PortalCredits {

    int PortalCreditsApp::onExecute() {
        if (!onInit()) {
            cerr << "Couldn't initialize the console" << endl;
            return 1;
        }

        running = true;
        while (running) {
            onEvent();

            onLoop();

            onRender();
        }

        onCleanup();

        return exitCode;
    }

    void PortalCreditsApp::quit(const int& exitCode) {
        this->exitCode = exitCode;
        running = false;
    }

    bool PortalCreditsApp::onInit() {
        if (!sound.load()) {
            cerr << "Couldn't load sound" << endl;
            return false;
        } else if (!console.init()) {
            return false;
        }

        draw.init();

        input.start();

        return true;
    }

    void PortalCreditsApp::onCleanup() {
        input.stop();
        sound.stop();
        console.close();
    }

}