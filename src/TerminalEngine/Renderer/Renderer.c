#include "Renderer.h"

void createRenderer(Renderer* renderer) {
    // 2D Array of unicode characters which acts as the screen buffer that will be printed on the console
    renderer->screen = (wchar_t*) malloc(sizeof(wchar_t) * renderer->screenWidth * renderer->screenHeight);
    // Create a handle to the console
    renderer->hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(renderer->hConsole);

    float nearC = 0.1f;
    float farC = 1000.0f;
    float aspectRatio = (float)renderer->screenHeight / (float)renderer->screenWidth;
    float fov = 90.0f;
    float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * PI);

    renderer->camera.nearClip = nearC;
    renderer->camera.farClip = farC;
    renderer->camera.aspectRatio = aspectRatio;
    renderer->camera.fov = fov;
    renderer->camera.fovRad = fovRad;
  
    renderer->camera.projectionMat.mat[0][0] = aspectRatio * fovRad;
    renderer->camera.projectionMat.mat[1][1] = fovRad;
    renderer->camera.projectionMat.mat[2][2] = farC / (farC - nearC);
    renderer->camera.projectionMat.mat[3][2] = (-nearC * farC) / (farC - nearC);
    renderer->camera.projectionMat.mat[2][3] = 1.0f;
    renderer->camera.projectionMat.mat[3][3] = 0.0f;

    renderer->camera.pos = (Vec3){0, 0, 0};
}

void clear(Renderer* renderer) {
    // Clear Buffer
    for(int y = 0; y < renderer->screenHeight; y++) {
        for(int x = 0; x < renderer->screenWidth; x++) {
            Vec2 pos = {x, y};
            renderer->screen[y*renderer->screenWidth + x] = ' ';
        }
    }
}

void render(Renderer* renderer) {
    DWORD dwBytesWritten = 0;

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
    
    if(ady <= adx) {
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

void drawTriangle(Renderer* renderer, Vec2* a, Vec2* b, Vec2* c) {
    drawLine(renderer, a, b);
    drawLine(renderer, a, c);
    drawLine(renderer, b, c);
}

void drawTriangle2(Renderer* renderer, Triangle* triangle) {
    Vec2 a = {triangle->points[0].x, triangle->points[0].y};
    Vec2 b = {triangle->points[1].x, triangle->points[1].y};
    Vec2 c = {triangle->points[2].x, triangle->points[2].y};
    drawTriangle(renderer, &a, &b, &c);
}

void drawText(Renderer* renderer, char* str, Vec2* pos) {
    char* c = str;
    int i = 0;
    while(*c != '\0') {
        renderer->screen[(int)pos->y * renderer->screenWidth + (int)pos->x + i] = *c;
        i++;
        c++;
    }
}