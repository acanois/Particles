//
// Created by David Richter on 10/11/25.
//

#pragma once

#include <lo/lo.h>
#include <lo/lo_cpp.h>

#include "raylib.h"

#include "AppConfig.h"
#include "ParticleSystem.h"

class Scene
{
public:
    Scene()
        :
        // oscHandler(std::make_unique<OscHandler>()),
        particleSystem(std::make_unique<ParticleSystem>(
            Vector2 {
                static_cast<float>(cfg.getConfig()["screenWidth"]) / 2.0f,
                static_cast<float>(cfg.getConfig()["screenHeight"]) / 20.0f
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
        lo::ServerThread st(7000);

        st.set_callbacks([&st]() { printf("Thread init: %p.\n", &st); },
                         []() { printf("Thread cleanup.\n"); });

        std::atomic<int> noteOn { 0 };

        st.add_method("/note_on", "i",
                      [&noteOn] (lo_arg** argv, int)
                      {
                          noteOn = (argv[0]->i);
                      });

        st.start();

        auto frameCount = 0;
        auto previousNote = 0;

        while (!WindowShouldClose())
        {
            ClearBackground(Color { 32, 32, 64, 255 });

            const auto currentNote = noteOn.load();
            if (currentNote != previousNote && previousNote == 0) {
                particleSystem->addParticle();
            }


            BeginDrawing();

            particleSystem->run();

            const auto particleCount = TextFormat(
                "Particles: (%u)",
                particleSystem->getNumParticles()
            );
            DrawText(particleCount, 10, 10, 20, ORANGE);

            const auto frameRate = TextFormat(
                "Framerate: (%u)",
                GetFPS()
            );
            DrawText(frameRate, 200, 10, 20, ORANGE);

            EndDrawing();
            previousNote = currentNote;
            ++frameCount;
        }
    }

private:
    AppConfig& cfg = AppConfig::getInstance();

    std::unique_ptr<ParticleSystem> particleSystem { nullptr };
};
