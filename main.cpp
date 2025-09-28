#include <iostream>

#include "raylib.h"

#include "Particle.h"
#include "ParticleSystem.h"

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;
static constexpr int NUM_PARTICLES = 200;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particles");
    SetTargetFPS(60);

    auto particleSystem = std::make_unique<ParticleSystem>(
        Vector2 { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f }
    );

    for (auto i = 0; i < NUM_PARTICLES; ++i)
    {
        particleSystem->addParticle();
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(Color { 24, 24, 24, 255 });

        particleSystem->run();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}
