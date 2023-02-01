#include <iostream>

#include "PortalCredits/SystemHandler.hpp"

using namespace std;

namespace PortalCredits {

    bool SystemHandler::init() {
        #ifdef PC_WINDOWS
        //Check whether the program has its own console
        HWND window = GetConsoleWindow();
        DWORD pid;
        GetWindowThreadProcessId(window, &pid);
        if (GetCurrentProcessId() != pid) { //The program doesn't have it's own console, create a new one
            cout << "Starting PortalCredits with its own console" << endl;
            FreeConsole();
            AllocConsole();
            window = GetConsoleWindow();
        }

        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);

        hIn = GetStdHandle(STD_INPUT_HANDLE);
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        //Save config for later
        GetConsoleMode(hIn, &origIn);
        GetConsoleMode(hOut, &origOut);
        origStyle = GetWindowLong(window, GWL_STYLE);

        SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
        SetConsoleMode(hOut, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
        SetWindowLong(window, GWL_STYLE, origStyle & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));
        #else
        int ttyfd = STDIN_FILENO;

        if (!isatty(ttyfd)) {
            cerr << "This is not a tty console" << endl;
            return false;
        }

        if (tcgetattr(ttyfd, &origAttr) < 0) {
            cerr << "Couldn't get tty settings" << endl;
            return false;
        }

        //Set console to raw mode
        struct termios raw = origAttr;

        /**
         * Input modes:
         * No break
         * No newline conversion
         * No parity check
         * No char strip (don't strip 8th bit)
         * No XON/XOFF flow control
        */
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

        //Disable post processing
        raw.c_oflag &= ~(OPOST);

        //Set 8-bit chars
        raw.c_cflag |= CS8;

        /**
         * Local modes:
         * No echo
         * No canonical mode (no line buffering)
         * No extended functions
         * No signal chars
        */
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

        //Read condition- Block until one Byte is available
        raw.c_cc[VMIN] = 1; raw.c_cc[VTIME] = 0;

        if (tcsetattr(ttyfd, TCSAFLUSH, &raw) < 0) {
            cerr << "Couldn't set raw mode" << endl;
            return false;
        }
        #endif

        return true;
    }

    void SystemHandler::close() {
        #ifdef PC_WINDOWS
        SetConsoleMode(hIn, origIn);
        SetConsoleMode(hOut, origOut);
        SetWindowLong(GetConsoleWindow(), GWL_STYLE, origStyle);
        #else
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &origAttr) < 0) cerr << "Couldn't reset console" << endl;
        #endif
    }

    void SystemHandler::getSize(int* width, int* height) {
        #ifdef PC_WINDOWS
        CONSOLE_SCREEN_BUFFER_INFOEX info;
        info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
        GetConsoleScreenBufferInfoEx(hOut, &info);

        if (width) *width = info.dwSize.X;
        if (height) *height = info.dwSize.Y;
        #else
        char esc, csi, eight, semi, t;
        int h, w;

        cout << "\033[18t" << flush; //Send query request

        //Read Response: ESC[8;height;width t
        cin >> esc >> csi >> eight >> semi >> h >> semi >> w >> t;

        if (width) *width = w;
        if (height) *height = h;
        #endif
    }

    string SystemHandler::getWindowTitle() {
        #ifdef PC_WINDOWS
        char str[1024];
        return string(str, GetConsoleTitleA(str, 1024));
        #else
        vector<char> res;
        char esc, osc, l, temp = 0;

        //Send request
        cout << "\033[21t" << flush;

        //Read response
        cin >> esc >> osc >> l;
        while (true) {
            cin >> temp;

            //Check for ST (ESC \)
            if (temp == '\033') {
                cin >> temp;
                if (temp == '\\') break;
            }

            res.push_back(temp);
        }
        res.push_back(0);

        return string(res.data());
        #endif
    }

    #ifdef PC_WINDOWS
    bool SystemHandler::resize(const int& width, const int& height) {
        /**
         * This method was taken from StackOverflow: https://stackoverflow.com/a/73917044 -> Set Console Window Size
         * Thank you very much
        */
        HWND hWnd;
        CONSOLE_FONT_INFO fi;
        CONSOLE_SCREEN_BUFFER_INFO bi;
        int w, h, bw, bh;
        RECT rect = {0, 0, 0, 0};
        COORD coord = {0, 0};
        hWnd = GetConsoleWindow();
        if (hWnd) {
            if (GetCurrentConsoleFont(hOut, FALSE, &fi)) {
                if (GetClientRect(hWnd, &rect)) {
                    w = rect.right-rect.left;
                    h = rect.bottom-rect.top;
                    if (GetWindowRect(hWnd, &rect)) {
                        bw = rect.right-rect.left-w;
                        bh = rect.bottom-rect.top-h;
                        if (GetConsoleScreenBufferInfo(hOut, &bi)) {
                            coord.X = bi.dwSize.X;
                            coord.Y = bi.dwSize.Y;
                            if (coord.X < width || coord.Y < height) {
                                if (coord.X < width) {
                                    coord.X = width;
                                }
                                if (coord.Y < height) {
                                    coord.Y = height;
                                }
                                if (!SetConsoleScreenBufferSize(hOut, coord)) {
                                    return false;
                                }
                            }
                            
                            //Center window
                            int nWidth = width * fi.dwFontSize.X + bw;
                            int nHeight = height * fi.dwFontSize.Y + bh;
                            int x = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
                            int y = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;

                            BOOL res = SetWindowPos(
                                hWnd, NULL,
                                x, y,
                                nWidth, nHeight,
                                SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER
                            );
                        }
                    }
                }
            }
        }
        return false;
    }

    #endif
}