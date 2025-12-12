#include "Renderer.h"

void createRenderer(Renderer* renderer) {
    // 2D Array of unicode characters which acts as the screen buffer that will be printed on the console
    renderer->screen = (wchar_t*) malloc(sizeof(wchar_t) * renderer->screenWidth * renderer->screenHeight);
    // Create a handle to the console
    renderer->hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(renderer->hConsole);
}

void render(Renderer* renderer) {
    DWORD dwBytesWritten = 0;

    // Clear Buffer
    for(int y = 0; y < renderer->screenHeight; y++) {
        for(int x = 0; x < renderer->screenWidth; x++) {
            Vec2 pos = {x, y};
            drawSolid(renderer, &pos);
            renderer->screen[y*renderer->screenWidth + x] = ' ';
        }
    }

    Vec2 pA = {15.0f, 10.0f};
    Vec2 pB = {80.0f, 30.0f};
    drawLine(renderer, &pA, &pB);

    // Null terminate
    renderer->screen[renderer->screenWidth * renderer->screenHeight - 1] = '\0';
    static const COORD topRight = {0, 0};
    // Output screen buffer to console
    WriteConsoleOutputCharacterW(renderer->hConsole, renderer->screen, renderer->screenWidth * renderer->screenHeight, topRight, &dwBytesWritten);
}
    
void destroyRenderer(Renderer* renderer) {
    free(renderer->screen);
}

void draw(Renderer* renderer, Fragment* frag) {
    renderer->screen[renderer->screenWidth * frag->y + frag->x] = frag->type;
}

void drawSolid(Renderer* renderer, Vec2* point) {
    Fragment frag = {point->x, point->y, 0x2588, 0};
    draw(renderer, &frag);
}

void drawLine(Renderer* renderer, Vec2* a, Vec2* b) {
    // Bresenham's Line Algorithm
    int dx = b->x - a->x;
    int dy = b->y - a->y;
    int adx = abs(dx);
    int ady = abs(dy);

    Vec2 endPoint;
    Vec2 currentPoint;

    int px = 2 * ady - adx;
    int py = 2 * adx - ady;
    
    if(adx <= adx) {
        if(dx >= 0) {
            currentPoint = *a;
            endPoint.x = b->x;
        }
        else {
            currentPoint = *b;
            endPoint.x = a->x;
        }

        drawSolid(renderer, &currentPoint);

        for(int i = 0; currentPoint.x < endPoint.x; i++) {
            currentPoint.x++;
            if(px < 0)
                px += 2 * ady;
            else {
                if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    currentPoint.y += 1;
                else
                    currentPoint.y -= 1;

                px += 2 * (ady - adx);
            }

            drawSolid(renderer, &currentPoint);
        }
    }
    else {
        if(dy >= 0) {
            currentPoint = *a;
            endPoint.y = b->y;
        }
        else {
            currentPoint = *b;
            endPoint.y = a->y;
        }

        drawSolid(renderer, &currentPoint);

        for(int i = 0; currentPoint.y < endPoint.y; i++) {
            currentPoint.y++;
            if(py < 0)
                py += 2 * adx;
            else {
                if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    currentPoint.x += 1;
                else
                    currentPoint.x -= 1;

                py += 2 * (adx - ady);
            }

            drawSolid(renderer, &currentPoint);
        }
    }
}