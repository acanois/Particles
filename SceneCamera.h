//
// Created by David Richter on 10/28/25.
//

#pragma once

#include <raylib.h>

class SceneCamera
{
public:
    SceneCamera(
        Vector3 position,
        Vector3 target,
        Vector3 up,
        float fovy,
        int mode
    ) : camera({ position, target, up, fovy, mode })
    {
    }

    Camera3D& getCamera() { return camera; }

    void beginMode3D() const { BeginMode3D(camera); }

    static void endMode3D() { EndMode3D(); }

    void setPosition(const Vector3 newPosition) { camera.position = newPosition; }

    void setTarget(const Vector3 newTarget) { camera.target = newTarget; }

    void setFovy(const float newFovy) { camera.fovy = newFovy; }

private:
    Camera3D camera;
};
