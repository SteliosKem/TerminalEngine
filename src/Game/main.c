#include "TerminalEngine/Windows/Application.h"

int main() {
    Application app = {220, 70, "Game"};
    createApplication(&app);
    return runApplication(&app);
}