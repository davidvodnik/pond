#include "system.h"

System::System(int width, int height)
    : boids{}, camera{width, height}, renderer{} {}

void System::resize(int width, int height) {
    camera.width = width;
    camera.height = height;
}

void System::update(float deltaTime, bool touch) {
    boids.update(deltaTime, touch);

    auto projectionView = updateCamera(camera);

    renderer.Render(boids.get_boids(), projectionView);
}
