#include "TerminalEngine/Windows/Application.h"

int main() {
    Application app = {232, 62, "Game"};
    createApplication(&app);
    return runApplication(&app);
}