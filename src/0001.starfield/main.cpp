#include "raylib.h"
#include "raymath.h"

#include <array>
#include <random>

static constexpr int width = 800;
static constexpr int height = 800;

static std::mt19937 generator(std::random_device{}()); 
static std::uniform_real_distribution<> width_dist(-width / 2.f,width / 2.f); // TODO(andrei): mai facem o distributie pentru inaltime ( in caz ca au valori diferite )
static std::uniform_real_distribution<> depth_dist(-1000, 0);

static constexpr unsigned stars_count = 400;
static constexpr float star_radius = 2;
static constexpr float star_speed = 15;

struct Star {
    Vector3 position;

    Star()
    {
        this->regenerate();
    }

    void update(float clipping_distance) {
        this->position.z += star_speed;
        if (this->position.z >= clipping_distance) {
            regenerate();
        }
    }

    void show() {
        //Body
        DrawSphere(this->position, star_radius, WHITE);
        //Tail
        DrawLine3D(this->position, Vector3Subtract(this->position, {0.f , 0.f, star_speed*10}), {128, 200, 200, 200});
    }

    void regenerate() {
        position.x = width_dist(generator);
        position.y = width_dist(generator);
        position.z = depth_dist(generator);
    }
};

int main(int argc, char **argv) {
  std::array<Star, stars_count> stars;
  Camera3D camera{
      {0, 0.f, 875}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, 0};

  InitWindow(width, height, "starfield");

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode3D(camera);

    ClearBackground(BLACK);

    for (auto &star : stars) {
        star.update(camera.position.z);
        star.show();
    }

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}