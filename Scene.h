//
// Created by David Richter on 10/11/25.
//

#pragma once

#include "raylib.h"

#include "AppConfig.h"
#include "ParticleSystem.h"
#include "OscHandler.h"

class Scene
{
public:
    Scene()
        : particleSystem(std::make_unique<ParticleSystem>(
            Vector2 {
                static_cast<float>(cfg.getConfig()["screenWidth"]) / 2.0f,
                static_cast<float>(cfg.getConfig()["screenHeight"]) / 20.0f
            }
        )),
        oscHandler(std::make_unique<OscHandler>())
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
            ClearBackground(Color { 32, 32, 64, 255 });

            if (particleSystem->getNumParticles() < 3000)
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
    AppConfig& cfg = AppConfig::getInstance();

    std::unique_ptr<OscHandler> oscHandler { nullptr };

    std::unique_ptr<ParticleSystem> particleSystem { nullptr };
};
