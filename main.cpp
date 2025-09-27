#include <iostream>

#include "raylib.h"

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;
static constexpr int MAX_PARTICLES = 200;

typedef struct
{
    Vector2 position;
    Color color;
    float alpha;
    float size;
    float rotation;
    bool active;
} Particle;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particles");
    SetTargetFPS(60);

    Particle particles[MAX_PARTICLES] = { 0 };

    for (auto i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].position = (Vector2) { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 4.0f };
        particles[i].color = (Color) { 255, 255, 255, 255 };
        particles[i].alpha = 1.0f;
        particles[i].size = 0.5f;
        particles[i].rotation = 0.0f;
        particles[i].active = true;
    }

    Texture2D flare = LoadTexture(ASSETS_PATH "particle_texture.png");

    auto gravity = 3.0f;
    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (particles[i].active)
            {
                particles[i].position.y += gravity/2;
                particles[i].alpha -= 0.005f;

                if (particles[i].alpha <= 0.0f) particles[i].active = false;

                particles[i].rotation += 2.0f;
            }
        }

        BeginDrawing();

        ClearBackground(Color { 24, 24, 24, 255 });

        for (auto i = 0; i < MAX_PARTICLES; i++)
        {
            if (particles[i].active)
            {
                DrawTexturePro(
                    flare,
                    (Rectangle) { 0.0f, 0.0f, (float) flare.width, (float) flare.height },
                    (Rectangle) {
                        particles[i].position.x,
                        particles[i].position.y,
                        flare.width * particles[i].size,
                        flare.height * particles[i].size
                    },
                    (Vector2) {
                        (float) (flare.width * particles[i].size / 2.0f),
                        (float) (flare.height * particles[i].size / 2.0f)
                    }, particles[i].rotation,
                    Fade(particles[i].color, particles[i].alpha));
            }
        }

        EndDrawing();
    }

    UnloadTexture(flare);

    CloseWindow();

    return 0;
}
