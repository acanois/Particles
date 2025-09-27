//
// Created by David Richter on 9/27/25.
//

#pragma once
#include "raylib.h"

class Particle
{
public:
    Particle(Vector2 position,
             Color color,
             float alpha,
             float size,
             float rotation,
             float velocity,
             float acceleration,
             bool active
    ) : m_position(position),
        m_color(color),
        m_alpha(alpha),
        m_size(size),
        m_rotation(rotation),
        m_velocity(velocity),
        m_acceleration(acceleration),
        m_active(active),
        m_texture(LoadTexture(ASSETS_PATH "particle_texture.png"))
    {
    }

    ~Particle()
    {
        UnloadTexture(m_texture);
    }

    void update(float gravity)
    {
        if (m_active)
        {
            m_position.y += gravity / 2;
            m_alpha -= 0.005f;

            if (m_alpha <= 0.0f) m_active = false;

            m_rotation += 2.0f;
        }
    }

    void draw()
    {
        if (m_active)
        {
            DrawTexturePro(
                m_texture,
                Rectangle {
                    0.0f,
                    0.0f,
                    static_cast<float>(m_texture.width),
                    static_cast<float>(m_texture.height)
                },
                Rectangle {
                    m_position.x,
                    m_position.y,
                    m_texture.width * m_size,
                    m_texture.height * m_size
                },
                Vector2 {
                    m_texture.width * m_size / 2.0f,
                    m_texture.height * m_size / 2.0f
                }, m_rotation,
                Fade(m_color, m_alpha));
        }
    }

    bool alive() const
    {
        return m_alpha > 0.0f;
    }

private:
    Vector2 m_position { 0.0f, 0.0f };

    Texture2D m_texture { 0 };

    Color m_color { 0 };

    float m_alpha { 0.0f };
    float m_size { 0.0f };
    float m_rotation { 0.0f };
    float m_velocity { 0.0f };
    float m_acceleration { 0.0f };

    bool m_active { true };
};
