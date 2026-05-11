#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

class ConsoleColor {
private:
    static HANDLE hConsole;
public:
    static void setColor(int color) {
        #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, color);
        #else
        // ANSI color codes for Linux/Mac
        const char* colors[] = {
            "\033[0m",   "\033[31m", "\033[32m", "\033[33m",
            "\033[34m", "\033[35m", "\033[36m", "\033[37m"
        };
        if (color >= 0 && color <= 7) {
            cout << colors[color];
        }
        #endif
    }
    
    static void reset() {
        setColor(7); // White on Windows, Reset on Linux/Mac
    }
};

// Color constants
enum Colors {
    RESET = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
};

#endif