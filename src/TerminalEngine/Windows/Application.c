#include <Windows.h>
#include <time.h>
#include "Application.h"
#include "Input.h"
#include "TerminalEngine/Renderer/Renderer.h"
#include <stdio.h>

bool createApplication(Application* app) {
    SetConsoleTitle(app->title);
    return true;
}

bool runApplication(Application* app) {
    Renderer renderer = {app->screenWidth, app->screenHeight, NULL};
    createRenderer(&renderer);

    int oldTime = clock();

    double theta = 0;

    // TESTING - CUBE
    Mesh cube;
    cube.triangles = malloc(sizeof(Triangle) * 6 * 2);
    // South
    cube.triangles[0] = (Triangle) { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } } };
    cube.triangles[1] = (Triangle) { { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } } };
    // East
    cube.triangles[2] = (Triangle) { { { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } } };
    cube.triangles[3] = (Triangle) { { { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f } } };
    // North
    cube.triangles[4] = (Triangle) { { { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f } } };
    cube.triangles[5] = (Triangle) { { { 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } } };
    // West
    cube.triangles[6] = (Triangle) { { { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } } };
    cube.triangles[7] = (Triangle) { { { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } };
    // Top
    cube.triangles[8] = (Triangle) { { { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } } };
    cube.triangles[9] = (Triangle) { { { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f } } };
    // Bottom
    cube.triangles[10] = (Triangle) { { { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } } };
    cube.triangles[11] = (Triangle) { { { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } } };

    Mat4 rot1;
        Mat4 rot2;

    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j++) {
            rot1.mat[i][j] = 0;
            rot2.mat[i][j] = 0;
        }
    }

    // Game Loop
    while(true) {
        int deltaTime = clock() - oldTime;
        oldTime = clock();

        theta += deltaTime * 0.001f;
        

        rot2.mat[0][0] = cos(theta);
        rot2.mat[0][1] = sin(theta);
        rot2.mat[1][0] = -sin(theta);
        rot2.mat[1][1] = cos(theta);
        rot2.mat[2][2] = 1;
        rot2.mat[3][3] = 1;
        
        
        rot1.mat[0][0] = 1;
        rot1.mat[1][1] = cos(2*theta);
        rot1.mat[1][2] = sin(2*theta);
        rot1.mat[2][1] = -sin(2*theta);
        rot1.mat[2][2] = cos(2*theta);
        rot1.mat[3][3] = 1;

        // Scene Drawing
        clear(&renderer);

        // Draw Cube
        for(int i = 0; i < 6 * 2; i++) {
            Triangle projectedTriangle;
            Triangle rotatedTriangle1;
            Triangle rotatedTriangle2;
            Triangle translatedTriangle;

            matXvec(&rot2, &cube.triangles[i].points[0], &rotatedTriangle2.points[0]);
            matXvec(&rot2, &cube.triangles[i].points[1], &rotatedTriangle2.points[1]);
            matXvec(&rot2, &cube.triangles[i].points[2], &rotatedTriangle2.points[2]);

            matXvec(&rot1, &rotatedTriangle2.points[0], &rotatedTriangle1.points[0]);
            matXvec(&rot1, &rotatedTriangle2.points[1], &rotatedTriangle1.points[1]);
            matXvec(&rot1, &rotatedTriangle2.points[2], &rotatedTriangle1.points[2]);

            translatedTriangle = rotatedTriangle1;
            translatedTriangle.points[0].z += 2;
            translatedTriangle.points[1].z += 2;
            translatedTriangle.points[2].z += 2;

            matXvec(&renderer.camera.projectionMat, &translatedTriangle.points[0], &projectedTriangle.points[0]);
            matXvec(&renderer.camera.projectionMat, &translatedTriangle.points[1], &projectedTriangle.points[1]);
            matXvec(&renderer.camera.projectionMat, &translatedTriangle.points[2], &projectedTriangle.points[2]);

            Vec2 a = {projectedTriangle.points[0].x, projectedTriangle.points[0].y};
            Vec2 b = {projectedTriangle.points[1].x, projectedTriangle.points[1].y};
            Vec2 c = {projectedTriangle.points[2].x, projectedTriangle.points[2].y};

            // Scale to Normalized Screen Space
            a.x += 1.0f;
            a.y += 1.0f;

            b.x += 1.0f;
            b.y += 1.0f;
    
            c.x += 1.0f;
            c.y += 1.0f;

            a.x *= 0.5f * (float)renderer.screenWidth;
            b.x *= 0.5f * (float)renderer.screenWidth;
            c.x *= 0.5f * (float)renderer.screenWidth;

            a.y *= 0.5f * (float)renderer.screenHeight;
            b.y *= 0.5f * (float)renderer.screenHeight;
            c.y *= 0.5f * (float)renderer.screenHeight;

            drawTriangle(&renderer, &a, &b, &c);
        }

        // End Scene
        render(&renderer);
    }

    destroyRenderer(&renderer);
}
