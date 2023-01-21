#ifndef PC_APP_HPP
#define PC_APP_HPP

#include <chrono>
#include <vector>
#include <optional>

#include "PortalCredits/ConsoleHandler.hpp"
#include "PortalCredits/DrawHandler.hpp"
#include "PortalCredits/SoundHandler.hpp"
#include "PortalCredits/InputHandler.hpp"

namespace PortalCredits {

    /**
     * This enum contains the different modes
     * the app can have
    */
    enum class AppMode : unsigned char {
        //The main menu
        MainMenu,
        //The about menu
        AboutMenu,
        //Show the GPL warranty disclaimer
        Warranty,
        //Show the GPL redistributing conditions
        Conditions,
        //Show the whole GPL License
        License,
        //Run the program
        MainProgram,
        //Run the program with modern outlines
        MainProgramModern,
        //A meta state used for quitting the program
        QuitProgram
    };

    class PortalCreditsApp {
        public:
            /**
             * Create the app, along with its handlers
            */
            PortalCreditsApp()
            : console(), draw(console, true), sound(), exitCode(0), time(0.0),
              running(false), mode(AppMode::MainMenu), dirty(false), stateChanged(true),
              menuMainPos(0), menuAboutPos(0) {}

            /**
             * Execute the app, e.g. running the main loop
             * @return The exit code
            */
            int onExecute();

            /**
             * Quit the app
             * @param exitCode The exit code to be returned in the onExecute method
            */
            void quit(const int& exitCode = 0);

        private:
            ConsoleHandler console;
            DrawHandler draw;
            SoundHandler sound;
            AppMode mode;
            InputHandler input;
            int exitCode;
            double time;
            bool running;
            bool dirty;
            bool stateChanged;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            std::vector<int> events;
            std::optional<AppMode> pendingStateChange;

            //Menu variables
            int menuMainPos;
            int menuAboutPos;

            /**
             * Init everything
             * @return If the initialization was successful
            */
            bool onInit();

            /**
             * Check the inputs
            */
            void onEvent();

            /**
             * Run the logic
            */
            void onLoop();

            /**
             * Draw the contents to the screen
            */
            void onRender();

            /**
             * Clean up and restore the console
            */
            void onCleanup();

            /**
             * Change the app state in the next frame
             * @param newMode The new mode to switch to
            */
            void changeState(AppMode newMode);

            /**
             * The loop method for the different menus.
             * @return If the console should be marked dirty
            */
            bool loopMenu();

            /**
             * The loop method for a scrollable text viewer (like the license).
             * @return If the console should be marked dirty
            */
            bool loopTextFile();

            /**
             * The loop method for the main program.
             * @return If the console should be marked dirty
            */
            bool loopMainProgram();

            /**
             * The render method for the different menus
            */
            void renderMenu();

            /**
             * The render method for the text viewers
            */
            void renderTextFile();

            /**
             * The render method for the main program
            */
            void renderMainProgram();
    };
}

#endif //PC_APP_HPP