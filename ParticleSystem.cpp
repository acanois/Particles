//
// Created by David Richter on 10/27/25.
//

#include "ParticleSystem.h"

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
    const auto velocityDirection = GetRandomValue(0, 1) ? -0.05f : 0.05f;
    auto velocity = Vector3 {
        velocityDirection,
        0.0f,
        velocityDirection
    };

    particles.push_back(
        std::make_unique<Particle>(
            Vector3 { 0.0f, 33.0f, 0.0f }, // Position
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
