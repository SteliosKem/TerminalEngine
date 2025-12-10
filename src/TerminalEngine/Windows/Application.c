#include <Windows.h>
#include <stdbool.h>

const int WINDOW_WIDTH = 120;
const int WINDOW_HEIGHT = 40;

int main() {
    // 2D Array of unicode characters which acts as the screen buffer that will be printed on the console
    wchar_t* screen = (wchar_t*) malloc(sizeof(wchar_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
    // Create a handle to the console
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    while(true) {
        // Placeholder fill
        for(int y = 0; y < WINDOW_HEIGHT; y++) {
            for(int x = 0; x < WINDOW_WIDTH; x++) {
                if(x < WINDOW_WIDTH / 2)
                    screen[y*WINDOW_WIDTH + x] = '|';
                else
                    screen[y*WINDOW_WIDTH + x] = '#';
            }
        }

        // Null terminate
        screen[WINDOW_WIDTH * WINDOW_HEIGHT - 1] = '\0';
        static const COORD topRight = {0, 0};
        // Output screen buffer to console
        WriteConsoleOutputCharacterW(hConsole, screen, WINDOW_WIDTH * WINDOW_HEIGHT, topRight, &dwBytesWritten);
    }
}