#include <iostream>

#include "raylib.h"

#include "Particle.h"
#include "ParticleSystem.h"

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particles");
    SetTargetFPS(60);

    auto particleSystem = std::make_unique<ParticleSystem>(
        Vector2 { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 4.0f }
    );

    // Particle particle = { 0 };
    auto particle = std::make_unique<Particle>(
        Vector2 { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 4.0f }, // Position
        (Color) { 255, 255, 255, 255 }, // Color
        1.0f, // Alpha
        0.5f, // Size
        0.0f, // Rotation
        0.0f, // Velocity
        0.0f, // Acceleration
        true // Active
    );

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(Color { 24, 24, 24, 255 });

        particle->update(3.0f);
        particle->draw();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}
