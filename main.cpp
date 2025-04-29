#include <iostream>
#include <raylib.h>

#include "go_lib.hpp"

using namespace std;

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO_Lib template");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
   
        
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}