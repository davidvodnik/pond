#include "boids.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

Boids::Boids() {
    for (int i = 0; i < 500; ++i) {
        boids.emplace_back(glm::linearRand(glm::vec3(-50), glm::vec3(50)));
        velocities.emplace_back(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
    }
}

void Boids::update() {
    // separation
    for (int t = 0; t < boids.size(); ++t) {
        auto close = glm::vec3(0);
        for (auto &boid : boids) {
            if (glm::distance(boids[t], boid) < 7.0f) {
                close += boids[t] - boid;
            }
        }
        velocities[t] += close * 0.1f;
    }
    // alignment
    for (int t = 0; t < boids.size(); ++t) {
        auto vel = glm::vec3(0);
        int count = 0;
        for (int s = 0; s < boids.size(); ++s) {
            if (glm::distance(boids[t], boids[s]) < 10.0f) {
                vel += velocities[s];
                count++;
            }
        }
        if (count > 0) {
            velocities[t] += vel / (float)count * 0.1f;
        }
    }
    // cohesion
    for (int t = 0; t < boids.size(); ++t) {
        auto center = glm::vec3(0);
        int count = 0;
        for (auto &boid : boids) {
            if (glm::distance(boids[t], boid) < 10.0f) {
                center += boid;
                count++;
            }
        }
        if (count > 0) {
            center = center / (float)count;
            velocities[t] -= (boids[t] - center) * 0.01f;
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        if (glm::abs(boids[t].x) > 50 || glm::abs(boids[t].y) > 50 ||
            glm::abs(boids[t].z) > 50) {
            velocities[t] -= boids[t] * 0.1f;
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        auto speed = glm::length(velocities[t]);
        if (speed > 50) {
            velocities[t] = velocities[t] * 50.0f / speed;
        }
        boids[t] += velocities[t] * 0.01f;
    }
}

[[nodiscard]] std::vector<glm::vec3> const &Boids::get_boids() const {
    return boids;
}
