//
// Created by David Richter on 9/27/25.
//

#pragma once

#include <vector>

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
                  1.0f
              ))
    {
    }

    void addParticle()
    {
        auto velocityScale = 2.0f;
        auto startVelocity = static_cast<float>(GetRandomValue(500, 1000)) / 1000.0f;
        auto direction = GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;
        auto alpha = static_cast<unsigned char>(GetRandomValue(100, 255));
        auto velocity = Vector2 {
            velocityScale * startVelocity * direction,
            // static_cast<float>(GetRandomValue(0, 0)) / 1000.0f,
            0.0f
        };
        particles.emplace_back(std::make_unique<Particle>(
            Vector2 { position.x, position.y }, // Position
            velocity, // Velocity
            Vector2 { 0.0f, 0.0f }, // Acceleration
            Color { 255, 255, 255, alpha }, // Color
            1.0f, // Alpha
            0.5f, // Size
            0.1f // Mass
        ));
    }

    void run()
    {
        for (const auto& particle: particles)
        {
            auto force = attractor->attract(*particle);
            particle->applyForce(force);
            particle->update();
            particle->draw();
        }

        // Putting this inside the for loop would cause iterator invalidation
        // std::erase_if(particles, [] (const std::unique_ptr<Particle>& particle) {
        //     return !particle->alive();
        // });
    }

    [[nodiscard]] unsigned long getNumParticles() const
    {
        return particles.size();
    }

private:
    Vector2 position;
    // Texture2D texture {};

    std::vector<std::unique_ptr<Particle> > particles;

    std::unique_ptr<Attractor> attractor { nullptr };
};
