#include <Windows.h>
#include "Application.h"
#include "Input.h"

bool createApplication(Application* app) {
    SetConsoleTitle(app->title);
    return true;
}

bool runApplication(Application* app) {
    // 2D Array of unicode characters which acts as the screen buffer that will be printed on the console
    wchar_t* screen = (wchar_t*) malloc(sizeof(wchar_t) * app->screenWidth * app->screenHeight);
    // Create a handle to the console
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    // Variable Declarations
    float divisorPosition = 0;


    // Game Loop
    while(true) {
        if(isKeyDown('D')) divisorPosition += 0.01f;
        if(isKeyDown('A')) divisorPosition -= 0.01f;
        if(divisorPosition > app->screenWidth || divisorPosition < 0) divisorPosition = 0;

        // Placeholder fill
        for(int y = 0; y < app->screenHeight; y++) {
            for(int x = 0; x < app->screenWidth; x++) {
                if(x < divisorPosition)
                    screen[y*app->screenWidth + x] = '|';
                else
                    screen[y*app->screenWidth + x] = '#';
            }
        }

        // Null terminate
        screen[app->screenWidth * app->screenHeight - 1] = '\0';
        static const COORD topRight = {0, 0};
        // Output screen buffer to console
        WriteConsoleOutputCharacterW(hConsole, screen, app->screenWidth * app->screenHeight, topRight, &dwBytesWritten);
    }

    free(screen);
    return true;
}
