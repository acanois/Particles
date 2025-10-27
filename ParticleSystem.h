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
    explicit ParticleSystem(Vector2 position);

    void addParticle();

    void run() const;

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
