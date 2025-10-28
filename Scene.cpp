//
// Created by David Richter on 10/27/25.
//

#include "Scene.h"

Scene::Scene()
    : camera(std::make_unique<SceneCamera>(
          Vector3 { 0.0f, 0.0f, -80.0f }, // position
          Vector3 { 0.0f, 0.0f, 0.0f }, // target
          Vector3 { 0.0f, 1.0f, 0.0f }, // up
          45.0f, // fovy
          CAMERA_PERSPECTIVE // mode
      )),
      particleSystem(std::make_unique<ParticleSystem>(
          Vector3 {
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

Scene::~Scene()
{
    CloseWindow();
}

void Scene::run() const
{
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    auto frameCount = 0;

    while (!WindowShouldClose())
    {
        ClearBackground(Color { 32, 32, 64, 255 });

        // if (currentNote != previousNote && previousNote == 0)
        if (particleSystem->getNumParticles() < 2500 && frameCount % 5 == 0)
            particleSystem->addParticle();

        BeginDrawing();

        camera->beginMode3D();

        DrawSphere(Vector3 {0.0f, 0.0f, 0.0f}, 24.0f, DARKBLUE);

        particleSystem->run();

        SceneCamera::endMode3D();

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

        ++frameCount;
    }
}
