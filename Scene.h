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
    Scene();

    ~Scene();

    Scene(const Scene& other) = default;

    Scene& operator=(const Scene& other) = default;

    Scene(Scene&& other) noexcept = default;

    Scene& operator=(Scene&& other) noexcept = default;

    void run() const;

private:
    AppConfig& cfg = AppConfig::getInstance();

    std::unique_ptr<ParticleSystem> particleSystem { nullptr };
};
