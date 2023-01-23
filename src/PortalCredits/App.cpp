#include <iostream>

#include "PortalCredits/App.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;

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

            if (pendingStateChange) {
                mode = pendingStateChange.value();
                pendingStateChange.reset();
                stateChanged = true;
                if (mode == AppMode::QuitProgram) quit();
            } else {
                stateChanged = false;
            }
        }

        onCleanup();

        return exitCode;
    }

    void PortalCreditsApp::quit(const int& exitCode) {
        this->exitCode = exitCode;
        running = false;
    }

    void PortalCreditsApp::changeState(AppMode newMode) {
        pendingStateChange.emplace(newMode);
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

        textHeight = DrawHandler::getArea(DrawArea::Menu).height - 1;
        textLicenseMaxPos = max((int) Resources::license.text.size() - textHeight, 0);
        textWarrantyMaxPos = max((int) Resources::warranty.text.size() - textHeight, 0);
        textConditionsMaxPos = max((int) Resources::conditions.text.size() - textHeight, 0);

        return true;
    }

    void PortalCreditsApp::onEvent() {
        vector<int> data = input.getChars();
        events.clear();

        for (const int& i: data) {
            //Only add relevant inputs to events
            switch (i) {
                case -1: //EOF (caused by CTRL + Z (on Windows)) -> Quit directly
                case 3: //Ctrl + C -> Quit directly
                    quit();
                    break;
                
                case ArrowUp:
                case ArrowDown:
                case ArrowLeft:
                case ArrowRight:
                case Space: //Space bar: Play/Pause
                case Enter: //Enter key pressed (No newline conversion)
                case Quit: //q key pressed -> Quit event
                    events.push_back(i);
                    break;
            }
        }
    }

    void PortalCreditsApp::onLoop() {
        switch (mode) {
            case AppMode::MainMenu:
            case AppMode::AboutMenu:
                dirty = loopMenu();
                break;
            
            case AppMode::Warranty:
            case AppMode::Conditions:
            case AppMode::License:
                dirty = loopTextFile();
                break;
            
            case AppMode::MainProgram:
            case AppMode::MainProgramModern:
                dirty = loopMainProgram();
                break;
        }
    }

    void PortalCreditsApp::onRender() {
        if (!dirty) return; //Only update when marked dirty

        switch (mode) {
            case AppMode::MainMenu:
            case AppMode::AboutMenu:
                renderMenu();
                break;
            
            case AppMode::Warranty:
            case AppMode::Conditions:
            case AppMode::License:
                renderTextFile();
                break;
            
            case AppMode::MainProgram:
            case AppMode::MainProgramModern:
                renderMainProgram();
                break;
        }

        dirty = false;
        stateChanged = false;
        console.update();
    }

    void PortalCreditsApp::onCleanup() {
        input.stop();
        sound.stop();
        console.setCursorVisibility(true);
        console.setCursorType(CursorType::Default);
        console.close();
    }

}