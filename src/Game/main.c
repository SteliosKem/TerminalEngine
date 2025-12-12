#include "TerminalEngine/Windows/Application.h"

int main() {
    Application app = {120, 40, "Game"};
    createApplication(&app);
    return runApplication(&app);
}