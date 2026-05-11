#include "colors.h"

#ifdef _WIN32
// Define the static member variable here (only once)
HANDLE ConsoleColor::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif