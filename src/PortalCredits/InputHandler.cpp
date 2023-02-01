#include <iostream>

#include "PortalCredits/InputHandler.hpp"

using namespace std;

static const int IgnoreEvent = -6;

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
        #ifdef PC_WINDOWS
        hIn = GetStdHandle(STD_INPUT_HANDLE);
        unsigned long numRead;
        int i;

        while (running) {
            ReadConsoleInput(hIn, events.data(), events.size(), &numRead);

            for (int j = 0; j < numRead; j++) {
                if (events.at(j).EventType == KEY_EVENT) i = processKeyEvent(events.at(j).Event.KeyEvent);
                else if (events.at(j).EventType == MOUSE_EVENT) i = processMouseEvent(events.at(j).Event.MouseEvent);
                else i = IgnoreEvent;

                if (i == IgnoreEvent) continue;

                m.lock(); //Lock mutex
                data.push_back(i); //Add data
                m.unlock();
            }
        }
        #else
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
        #endif
    }

    #ifdef PC_WINDOWS
    int InputHandler::processKeyEvent(const KEY_EVENT_RECORD& record) {
        if (!record.bKeyDown) return IgnoreEvent;

        switch (record.wVirtualKeyCode) {
            case VK_UP:
                return ArrowUp;
            case VK_DOWN:
                return ArrowDown;
            case VK_LEFT:
                return ArrowLeft;
            case VK_RIGHT:
                return ArrowRight;
            case VK_RETURN:
                return Enter;
            default:
                return record.uChar.AsciiChar;
        }
    }

    int InputHandler::processMouseEvent(const MOUSE_EVENT_RECORD& record) {
        if (record.dwEventFlags == MOUSE_WHEELED) {
            int scroll = record.dwButtonState & 0xFFFF0000;
            if (scroll > 0) return ArrowUp;
            else if (scroll < 0) return ArrowDown;
        }
        return IgnoreEvent;
    }

    #endif
}