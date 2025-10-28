//
// Created by David Richter on 10/27/25.
//

#include "ParticleSystem.h"

#include <iostream>

ParticleSystem::ParticleSystem(const Vector3 position)
    : position(position),
      attractor(
          std::make_unique<Attractor>(
              Vector3 { 0.0f, 0.0f, 0.0f },
              0.005f
          ))
{
}

void ParticleSystem::addParticle()
{
    auto xVel = static_cast<float>(GetRandomValue(0, 1000)) / 1000.0f * 5.0f * 0.01f;
    const auto direction = GetRandomValue(0, 1) ? -1.0f : 1.0f;
    const auto xVelDirection = xVel * direction;

    if (xVelDirection < 0.0f)
        xVel = -xVel;

    const auto zVelDirection = 0.05f - xVel * direction;

    auto velocity = Vector3 {
        xVelDirection,
        0.0f,
        -zVelDirection
    };

    particles.push_back(
        std::make_unique<Particle>(
            Vector3 { 0.0f, 27.0f, 0.0f }, // Position
            velocity, // Velocity
            Vector3 { 0.0f, 0.0f, 0.0f }, // Acceleration
            Color { 255, 255, 255, 255 }, // Color
            1.0f, // Alpha
            1.0f, // Size
            1.0f // Mass
        ));
}

void ParticleSystem::run() const
{
    for (const auto& particle: particles)
    {
        const auto force = attractor->attract(*particle);
        particle->applyForce(force);
        particle->update();
        particle->draw();
    }
}
