#include "system.h"

System::System(int width, int height)
    : boids{}, camera{width, height}, renderer{} {}

void System::resize(int width, int height) {
    camera.width = width;
    camera.height = height;
}

void System::update(float deltaTime, bool touch, int x, int y) {

    auto projectionView = updateCamera(camera);

    // make cursor coordinates from -1 to +1
    float pt_x = (x / (float)camera.width) * 2.f - 1.f;
    float pt_y = -(y / (float)camera.height) * 2.f + 1.f;

    //                       z value from 0.f to 1.f for d3d
    glm::vec4 origin =
        glm::inverse(projectionView) * glm::vec4(pt_x, pt_y, -1.f, 1.f);
    origin.w = 1.0f / origin.w;
    origin.x *= origin.w;
    origin.y *= origin.w;
    origin.z *= origin.w;
    // origin.x = -origin.x;
    // origin.y = -origin.y;
    origin.z += 80;
    printf("%f %f %f\n", origin.x, origin.y, origin.z);

    boids.update(deltaTime, touch, glm::vec3(origin));

    renderer.Render(boids.get_boids(), projectionView);
}
