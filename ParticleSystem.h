//
// Created by David Richter on 9/27/25.
//

#pragma once

#include <vector>

#include "AppConfig.h"
#include "Particle.h"
#include "Attractor.h"

class ParticleSystem
{
public:
    explicit ParticleSystem(const Vector2 position)
        : position(position),
          attractor(
              std::make_unique<Attractor>(
                  Vector2 { 1280.0f / 2.0f, 720.0f / 2.0f },
                  0.005f
              ))
    {
    }

    void addParticle()
    {
        const auto velocityScale = 1.0f;
        const auto startVelocity = static_cast<float>(GetRandomValue(500, 1000)) / 1000.0f;
        const auto direction = GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;
        const auto alpha = static_cast<unsigned char>(GetRandomValue(100, 255));
        auto velocity = Vector2 {
            velocityScale * startVelocity * direction,
            0.0f
        };
        const auto xPos = static_cast<float>(GetRandomValue(0, 1280));
        particles.emplace_back(std::make_unique<Particle>(
            Vector2 { xPos, position.y }, // Position
            velocity, // Velocity
            Vector2 { 0.0f, 0.0f }, // Acceleration
            Color { 255, 255, 255, alpha }, // Color
            1.0f, // Alpha
            2.0f, // Size
            1.0f // Mass
        ));
    }

    void run()
    {
        for (const auto& particle: particles)
        {
            const auto force = attractor->attract(*particle);
            particle->applyForce(force);
            particle->update();
            particle->draw();
        }
    }

    [[nodiscard]] unsigned long getNumParticles() const
    {
        return particles.size();
    }

private:
    AppConfig& cfg = AppConfig::getInstance();

    Vector2 position;

    std::vector<std::unique_ptr<Particle> > particles;

    std::unique_ptr<Attractor> attractor { nullptr };
};
