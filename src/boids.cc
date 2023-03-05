#include "boids.h"
#include <glm/gtc/random.hpp>
#include <physics/flocking.h>
#include <physics/forces.h>

Boids::Boids() {
    for (int i = 0; i < 512; ++i) {
        positions.emplace_back(glm::linearRand(glm::vec3(-50), glm::vec3(50)));
        velocities.emplace_back(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
        forces.emplace_back(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
    }
}

void Boids::update(float deltaTime, bool touch, glm::vec3 pos) {
    separation(10.0f, 7.0f)(forces, positions);
    alignment(100.0f, 20.0f)(forces, velocities, positions);
    cohesion(10.0f, 20.0f)(forces, velocities, positions);
    limit(100)(forces);
    drag(1.2)(forces, velocities);
    box(50, 10.0f)(forces, positions);
    if (touch) {
        shape(pos, 3.0f, 300.0f, 20.0f)(forces, velocities, positions,
                                        deltaTime);
    }
    integrate(deltaTime)(forces, velocities, positions);
}
