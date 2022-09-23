#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <cstdio>

constexpr static int width = 800;
constexpr static int height = 800;

struct Cube {
    Vector3 position;
    Vector3 size;
    Color color;
};


auto split(std::vector<Cube> const& old_sponge) -> std::vector<Cube>
{
    printf("[%s:%s:%d]\n", __FILE__, __FUNCTION__, __LINE__);
    std::vector<Cube> new_sponge{};
    new_sponge.reserve(old_sponge.size() * 20);

    for(auto& [old_pos, old_size, old_color] : old_sponge) {
        for(int i = -1; i < 2 ; ++i) {
            for(int j = -1; j < 2 ; ++j) {
                for(int k = -1; k < 2 ; ++k) {

                    float size = old_size.x / 3.f; 
                    Vector3 offset{static_cast<float>(i),static_cast<float>(j),static_cast<float>(k)};
                    Vector3 pos = Vector3Add(old_pos, Vector3Scale(offset, size));
                    if(i == j && i == 0 || i == k && i == 0 || j == k && j == 0)
                        new_sponge.emplace_back(pos, Vector3Scale(Vector3One(), size), (Color){0,0,0,255});
                    else
                        new_sponge.emplace_back(pos, Vector3Scale(Vector3One(), size), old_color);
                    
                }
            }   
        }
    }
    return new_sponge;
}


int main(int argc, char** argv)
{
    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ -15.0f, 15.0f, -15.0f };   // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera mode type
    SetCameraMode(camera, CAMERA_ORBITAL);

    std::vector<Cube> sponge{};
    sponge.emplace_back((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){12.f ,12.f, 12.f}, (Color){128, 128, 128, 255});

    InitWindow(width, height, "menger_sponge");
    SetTargetFPS(1);

    while (!WindowShouldClose())
    {        
        if( IsKeyDown(KEY_SPACE) ) {
            printf("sponge.size() = %zu\n", sponge.size());
            sponge = split(sponge);
        }

        BeginDrawing();
        BeginMode3D(camera);

            ClearBackground(BLACK);
            for(auto& [pos, size, col] : sponge) {
                DrawCubeV(pos, size, col);
            }

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}