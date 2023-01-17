#include <iostream>
#include <csignal>

#include "PortalCredits/App.hpp"

using namespace std;

PortalCredits::PortalCreditsApp* runningApp = NULL;

void quitAppIfNecessary(int signal);

int main(int anzahl, char* args[]) {
    cout << "Hello World" << endl;

    //Register signal handlers
    std::signal(SIGABRT, quitAppIfNecessary);
    std::signal(SIGINT, quitAppIfNecessary);
    std::signal(SIGTERM, quitAppIfNecessary);

    //Run app
    PortalCredits::PortalCreditsApp app;
    runningApp = &app;
    int exitCode = app.onExecute();

    //Clean up
    runningApp = NULL;
}

void quitAppIfNecessary(int signal) {
    if (runningApp) {
        runningApp->quit();
        runningApp = NULL;
    }
}