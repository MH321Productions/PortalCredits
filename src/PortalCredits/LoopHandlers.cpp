#include <iostream>
#include <algorithm>
#include <cmath>

#include "PortalCredits/App.hpp"
#include "PortalCredits/Resources.hpp"

using namespace std;
using namespace std::chrono;

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
                } else if (i == Quit) {
                    quit();
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
                } else if (i == Quit) {
                    quit();
                    break;
                }
            }
        }

        return ret;
    }

    bool PortalCreditsApp::loopTextFile() {
        bool ret = false;
        if (stateChanged) {
            ret = true;
            textPos = 0;
        }

        const int& maxPos = mode == AppMode::Conditions ? textConditionsMaxPos : mode == AppMode::License ? textLicenseMaxPos : textWarrantyMaxPos;

        //Evaluate events
        for (const int& i: events) {
            if (i == ArrowDown) {
                ret = true;
                textPos = min(textPos + 1, maxPos);
            } else if (i == ArrowUp) {
                ret = true;
                textPos = max(textPos - 1, 0);
            } else if (i == Quit) {
                changeState(AppMode::AboutMenu);
                break;
            }
        }


        return ret;
    }

    bool PortalCreditsApp::loopMainProgram() {
        bool ret = false;
        if (stateChanged) {
            ret = true;
            mainTime = 0.0;
            mainTimeAdd = 0.0;
            start = system_clock::now();
            mainIsMusicStarted = false;
            mainIsRunning = true;

            //Init timings
            mainInfo.lyrics = Resources::timingLyrics.size() ? Resources::timingLyrics.data() : NULL;
            mainInfo.credits = Resources::timingCredits.size() ? Resources::timingCredits.data() : NULL;
            mainInfo.logo = Resources::timingLogos.size() ? Resources::timingLogos.data() : NULL;
        }

        //Determine time
        if (mainIsRunning) {
            end = system_clock::now();
            dur = end - start;
            mainTime = dur.count() + mainTimeAdd;
        }

        //Evaluate events
        for (const int& i: events) {
            if (i == Space) {
                ret = true;
                if (mainIsRunning) {
                    mainIsRunning = false;
                    mainTimeAdd = mainTime;
                    if (mainIsMusicStarted) sound.pause();
                } else {
                    mainIsRunning = true;
                    start = system_clock::now();
                    if (mainIsMusicStarted) sound.play();
                }
            } else if (i == Quit) {
                sound.stop();
                changeState(AppMode::MainMenu);
                break;
            }
        }

        if (!mainIsRunning) return ret;

        //Check for music start
        if (mainTime >= Resources::audioStartTime && !mainIsMusicStarted) {
            ret = true;
            mainIsMusicStarted = true;
            sound.play();
        }

        //Song is finished, return to main menu
        if (!mainInfo.lyrics && !mainInfo.credits && !mainInfo.logo) {
            changeState(AppMode::MainMenu);
            sound.stop();
            return true;
        }

        //Check transitions
        if (mainInfo.lyrics && mainTime > mainInfo.lyrics->endTime) {
            ret = true;
            mainInfo.lyricsIndex++;
            if (mainInfo.lyricsIndex >= Resources::timingLyrics.size()) mainInfo.lyrics = NULL;
            else {
                mainInfo.lyrics = &Resources::timingLyrics.at(mainInfo.lyricsIndex);
                if (mainInfo.lyrics->stringIndex == 0) mainInfo.lyricsClear = true;
            }

        }
        if (mainInfo.credits && mainTime > mainInfo.credits->endTime) {
            ret = true;
            mainInfo.creditsIndex++;
            if (mainInfo.creditsIndex >= Resources::timingCredits.size()) mainInfo.credits = NULL;
            else {
                mainInfo.credits = &Resources::timingCredits.at(mainInfo.creditsIndex);
                mainInfo.creditsClear = true;
            }
        }
        if (mainInfo.logo && mainTime > mainInfo.logo->endTime) {
            ret = true;
            mainInfo.logoIndex++;
            if (mainInfo.logoIndex >= Resources::timingLogos.size()) mainInfo.logo = NULL;
            else {
                mainInfo.logo = &Resources::timingLogos.at(mainInfo.logoIndex);
                mainInfo.logoClear = true;
            }
        }

        //Calculate text positions
        long newPos;
        double percentage;
        if (mainInfo.lyrics) {
            percentage = (mainTime - mainInfo.lyrics->startTime) / (mainInfo.lyrics->duration);
            newPos = (long) round(percentage * (mainInfo.lyrics->endPos - mainInfo.lyrics->startPos));
            if (newPos < 0) newPos = 0;
            else if (newPos > mainInfo.lyrics->endPos) newPos = mainInfo.lyrics->endPos;

            if (newPos != mainInfo.lyricsPos) {
                ret = true;
                mainInfo.lyricsPos = newPos;
            }
        }
        if (mainInfo.credits) {
            percentage = (mainTime - mainInfo.credits->startTime) / (mainInfo.credits->duration);
            newPos = (size_t) (percentage * (mainInfo.credits->endPos - mainInfo.credits->startPos));
            if (newPos < 0) newPos = 0;
            else if (newPos > mainInfo.credits->endPos) newPos = mainInfo.credits->endPos;

            if (newPos != mainInfo.creditsPos) {
                ret = true;
                mainInfo.creditsPos = newPos;
            }
        }

        return ret;
    }

}