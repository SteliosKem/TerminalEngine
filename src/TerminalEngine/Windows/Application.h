#ifndef TE_APP_H
#define TE_APP_H

#include <stdbool.h>

// Struct that contains all information about the Game Application
typedef struct Application {
    int screenWidth;
    int screenHeight;
    char* title;
} Application;

// Initializes an Application based on the struct provided. Returns false if there were errors.
bool createApplication(Application* app);
// Runs the application based on the struct provided. Returns false if there were errors.
bool runApplication(Application* app);

#endif