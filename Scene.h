//
// Created by David Richter on 10/11/25.
//

#pragma once

#include "raylib.h"

#include "AppConfig.h"
#include "ParticleSystem.h"

class Scene
{
public:
    Scene()
        : particleSystem(std::make_unique<ParticleSystem>(
            Vector2 {
                cfg.getConfig()["screenWidth"] / 2.0f,
                cfg.getConfig()["screenHeight"] / 20.0f
            }
        ))
    {
        InitWindow(
            cfg.getConfig()["screenWidth"],
            cfg.getConfig()["screenHeight"],
            "Particles"
        );
        SetTargetFPS(cfg.getConfig()["fps"]);
    }

    ~Scene()
    {
        CloseWindow();
    }

    Scene(const Scene& other) = default;

    Scene& operator=(const Scene& other) = default;

    Scene(Scene&& other) noexcept = default;

    Scene& operator=(Scene&& other) noexcept = default;

    void run() const
    {
        while (!WindowShouldClose())
        {
            ClearBackground(Color { 28, 24, 42, 255 });

            if (particleSystem->getNumParticles() < 750)
                particleSystem->addParticle();

            BeginDrawing();

            particleSystem->run();

            const auto text = TextFormat(
                "Particles: (%u)",
                particleSystem->getNumParticles()
            );
            DrawText(text, 10, 10, 20, ORANGE);

            EndDrawing();
        }
    }

private:
    // static constexpr int width { 1280 };
    // static constexpr int height { 720 };
    //
    // static constexpr int fps { 120 };

    AppConfig& cfg = AppConfig::getInstance();

    std::unique_ptr<ParticleSystem> particleSystem { nullptr };
};
