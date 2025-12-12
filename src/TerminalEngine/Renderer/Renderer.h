#ifndef TE_RENDERER_H
#define TE_RENDERER_H

#include <Windows.h>
#include "TerminalEngine/Math.h"

typedef struct Renderer {
    int screenWidth;
    int screenHeight;
    wchar_t* screen;
    HANDLE hConsole;
} Renderer;

// Initializes the renderer struct.
void createRenderer(Renderer* renderer);

// Outputs to the terminal.
void render(Renderer* render);

// Frees memory held by the struct.
void destroyRenderer(Renderer* renderer);

typedef enum Color {
    WHITE
} Color;

typedef struct Fragment {
    int x;
    int y;
    wchar_t type;
    Color color;
} Fragment;

// Draw Commands

// Draws a single "pixel" (character) at specified location.
void draw(Renderer* renderer, Fragment* frag);
// Draws a solid (filled) character at specified location.
void drawSolid(Renderer* renderer, Vec2* point);
void drawLine(Renderer* renderer, Vec2* a, Vec2* b);

#endif