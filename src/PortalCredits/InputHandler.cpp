#include <iostream>

#include "PortalCredits/InputHandler.hpp"

using namespace std;

namespace PortalCredits {

    void InputHandler::start() {
        if (running) return;
        running = true;

        t = thread(&InputHandler::readThread, this);
        t.detach();
    }

    void InputHandler::stop() {
        if (!running) return;

        running = false;
    }

    vector<int> InputHandler::getChars(const bool& clearChars) {
        scoped_lock lock(m); //Lock mutex to avoid concurrency problems

        vector<int> ret = data;

        if (clearChars) data.clear();

        return ret;
    }

    void InputHandler::clearChars() {
        scoped_lock lock(m);

        data.clear();
    }

    void InputHandler::readThread() {
        while (running) {
            int i = cin.get(); //Read char (blocking)

            if (i == 27) { //Esc
                hasEsc = true;
                hasCsi = false;
                continue;
            } else if (i == '[' && hasEsc) { //CSI
                hasCsi = true;
                continue;
            } else { //Determine data to be written
                if (hasEsc && hasCsi) {
                    //If a valid escape code is given, parse it to an arrow code
                    switch (i) {
                        case 'A':
                            i = ArrowUp;
                            break;
                        case 'B':
                            i = ArrowDown;
                            break;
                        case 'C':
                            i = ArrowRight;
                            break;
                        case 'D':
                            i = ArrowLeft;
                    }

                    hasEsc = false;
                    hasCsi = false;
                }
            }

            m.lock(); //Lock mutex
            data.push_back(i); //Add data
            m.unlock();
        }
    }

}