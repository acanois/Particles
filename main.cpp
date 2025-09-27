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
    float velocity;
    float acceleration;
    bool active;
} Particle;

void updateParticle(Particle& particle)
{
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particles");
    SetTargetFPS(60);

    Particle particle = { 0 };

    particle.position = Vector2 { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 4.0f };
    particle.color = (Color) { 255, 255, 255, 255 };
    particle.alpha = 1.0f;
    particle.size = 0.5f;
    particle.rotation = 0.0f;
    particle.active = true;

    Texture2D flare = LoadTexture(ASSETS_PATH "particle_texture.png");

    auto gravity = 3.0f;
    while (!WindowShouldClose())
    {
        if (particle.active)
        {
            particle.position.y += gravity / 2;
            particle.alpha -= 0.005f;

            if (particle.alpha <= 0.0f) particle.active = false;

            particle.rotation += 2.0f;
        }

        BeginDrawing();

        ClearBackground(Color { 24, 24, 24, 255 });


        if (particle.active)
        {
            DrawTexturePro(
                flare,
                (Rectangle) { 0.0f, 0.0f, (float) flare.width, (float) flare.height },
                (Rectangle) {
                    particle.position.x,
                    particle.position.y,
                    flare.width * particle.size,
                    flare.height * particle.size
                },
                (Vector2) {
                    (float) (flare.width * particle.size / 2.0f),
                    (float) (flare.height * particle.size / 2.0f)
                }, particle.rotation,
                Fade(particle.color, particle.alpha));
        }

        EndDrawing();
    }

    UnloadTexture(flare);

    CloseWindow();

    return 0;
}
