#include <raylib.h>

#include <iostream>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;


int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    go::Triangle trian(go::Node(200,200), go::Node(300,400), go::Node(100,400));

    while (WindowShouldClose() == false){

        BeginDrawing();
            ClearBackground(BLACK);
            trian.draw();

        EndDrawing();
    }

    CloseWindow();
}