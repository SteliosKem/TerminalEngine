#ifndef TE_RENDERER_H
#define TE_RENDERER_H

#include <Windows.h>
#include "TerminalEngine/Math.h"

// ---- CAMERA ----

typedef struct Camera {
    float nearClip;
    float farClip;
    float fov;
    float aspectRatio;
    float fovRad;

    Mat4 projectionMat;
} Camera;


// ---- RENDERER ----

typedef struct Renderer {
    int screenWidth;
    int screenHeight;
    wchar_t* screen;
    HANDLE hConsole;
    Camera camera;
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


// Holds the 3 points of a triangle
typedef struct Triangle {
    Vec3 points[3];
} Triangle;

// Dynamic Array of Triangles
typedef struct Mesh {
    Triangle* triangles;
} Mesh;

// Draw Commands

// Clears the Screen Buffer.
void clear(Renderer* renderer);
// Draws a single "pixel" (character) at specified location.
void draw(Renderer* renderer, Fragment* frag);
// Draws a solid (filled) character at specified location.
void drawSolid(Renderer* renderer, Vec2* point);
// Draws a solid line from point a to point b.
void drawLine(Renderer* renderer, Vec2* a, Vec2* b);
// Draws a non-filled triangle with the three inputs as points.
void drawTriangle(Renderer* renderer, Vec2* a, Vec2* b, Vec2* c);
// Draws a non-filled triangle.
void drawTriangle2(Renderer* renderer, Triangle* triangle);
// Outputs the given string on the terminal starting from the specified point
void drawText(Renderer* renderer, char* str, Vec2* pos);


#endif