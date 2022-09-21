#include "raylib.h"



int main(int argc, char** argv)
{
    const int width = 800;
    const int height = 800;

    InitWindow(width, height, "smoketest");

    while (!WindowShouldClose())
    {        
        BeginDrawing();

            ClearBackground(BLACK);
            DrawCircleV({width / 2., height / 2.}, 100., RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}