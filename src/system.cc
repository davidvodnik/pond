#include "system.h"

System::System(int width, int height)
    : boids{}, camera{width, height}, renderer{} {}

void System::resize(glm::ivec2 screenSize) {
    camera.width = screenSize.x;
    camera.height = screenSize.y;
}

void System::update(float deltaTime, bool touch, int x, int y) {
    auto projectionView = camera.update();

    boids.update(deltaTime, touch,
                 camera.screenToWorld(projectionView, glm::vec2(x, y), 80.0f));

    renderer.Render(boids.get_boids(), projectionView);
}
