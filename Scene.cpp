//
// Created by David Richter on 10/27/25.
//

#include "Scene.h"

#include "raylib.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

Scene::Scene()
    : camera(std::make_unique<SceneCamera>(
          Vector3 { 0.0f, 0.0f, -10.0f }, // position
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
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    const Shader shader = LoadShader(
        TextFormat("%s/lighting.vs", SHADER_PATH, 330),
        TextFormat("%s/lighting.fs", SHADER_PATH, 330)
    );

    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level (some basic lighting)
    const int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]) { 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3) { -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
    lights[1] = CreateLight(LIGHT_POINT, (Vector3) { 2, 1, 2 }, Vector3Zero(), RED, shader);
    lights[2] = CreateLight(LIGHT_POINT, (Vector3) { -2, 1, 2 }, Vector3Zero(), GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, (Vector3) { 2, 1, -2 }, Vector3Zero(), BLUE, shader);

    auto frameCount = 0;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera->getCamera(), CAMERA_ORBITAL);
        auto [x, y, z] = camera->getCamera().position;

        const float cameraPos[3] = { x, y, z };

        SetShaderValue(
            shader,
            shader.locs[SHADER_LOC_VECTOR_VIEW],
            cameraPos,
            SHADER_UNIFORM_VEC3
        );
        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        for (const auto& light: lights) UpdateLightValues(shader, light);

        // if (currentNote != previousNote && previousNote == 0)
        // if (particleSystem->getNumParticles() < 2500 && frameCount % 5 == 0)
        //     particleSystem->addParticle();

        BeginDrawing();

        ClearBackground(Color { 32, 32, 64, 255 });

        camera->beginMode3D();

        BeginShaderMode(shader);

        DrawSphere(Vector3 { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
        // DrawCubeV(Vector3Zero(), Vector3 { 1.0f, 1.0f, 1.0f }, WHITE);

        EndShaderMode();

        // particleSystem->run();

        for (const auto& light: lights)
        {
            if (light.enabled) DrawSphereEx(light.position, 0.2f, 8, 8, light.color);
            else DrawSphereWires(light.position, 0.2f, 8, 8, ColorAlpha(light.color, 0.3f));
        }

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

    UnloadShader(shader);
}
