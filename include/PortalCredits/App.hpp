#ifndef PC_APP_HPP
#define PC_APP_HPP

#include <chrono>
#include <vector>

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
        //The main menu (duh)
        MainMenu,
        //Show the GPL warranty disclaimer
        Warranty,
        //Show the GPL redistributing conditions
        Conditions,
        //Run the program
        MainProgram
    };

    class PortalCreditsApp {
        public:
            /**
             * Create the app, along with its handlers
            */
            PortalCreditsApp()
            : console(), draw(console, true), sound(), exitCode(0), time(0.0), running(false), mode(AppMode::MainMenu), dirty(false) {}

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
            std::chrono::time_point<std::chrono::system_clock> start, end;
            std::vector<int> events;

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
    };
}

#endif //PC_APP_HPP