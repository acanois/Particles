#include <iostream>

#include "raylib.h"

#include "Particle.h"
#include "ParticleSystem.h"

static constexpr int WINDOW_WIDTH { 1280 };
static constexpr int WINDOW_HEIGHT { 720 };
static constexpr int MAX_PARTICLES { 200 };

static constexpr int FPS { 120 };

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particles");
    SetTargetFPS(FPS);

    auto particleSystem = std::make_unique<ParticleSystem>(
        Vector2 { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 20.0f }
    );

    auto frameCount = 0;
    while (!WindowShouldClose())
    {
        ++frameCount;

        particleSystem->addParticle();

        BeginDrawing();

        ClearBackground(Color { 24, 24, 24, 255 });

        particleSystem->run();

        const auto text = TextFormat("Particles: (%u)", particleSystem->getNumParticles());
        DrawText(text, 10, 10, 20, ORANGE);

        EndDrawing();
    }


    CloseWindow();

    return 0;
}
