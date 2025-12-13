#include "TerminalEngine/Windows/Application.h"

int main() {
    Application app = {235, 70, "Game"};
    createApplication(&app);
    return runApplication(&app);
}