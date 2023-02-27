#include "boids.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

Boids::Boids() {
    for (int i = 0; i < 512; ++i) {
        boids.emplace_back(glm::linearRand(glm::vec3(-50), glm::vec3(50)));
        velocities.emplace_back(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
        forces.emplace_back(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
    }
}

void Boids::update(float deltaTime, bool touch, glm::vec3 pos) {
    // separation
    for (int t = 0; t < boids.size(); ++t) {
        auto close = glm::vec3(0);
        for (auto &boid : boids) {
            if (glm::distance(boids[t], boid) < 7.0f) {
                close += boids[t] - boid;
            }
        }
        forces[t] += close * 10.0f;
    }
    // alignment
    for (int t = 0; t < boids.size(); ++t) {
        auto vel = glm::vec3(0);
        float weigth = 0;
        for (int s = 0; s < boids.size(); ++s) {
            float d = glm::distance(boids[t], boids[s]);
            if (d < 20.0f && d > 0.0f) {
                vel += velocities[s] / d;
                weigth += 1.0f / d;
            }
        }
        if (weigth > 0) {
            glm::vec3 avg = vel / weigth;
            forces[t] += glm::normalize(avg) * 100.0f;
        }
    }
    // cohesion
    for (int t = 0; t < boids.size(); ++t) {
        auto center = glm::vec3(0);
        float weigth = 0;
        for (auto &boid : boids) {
            float d = glm::distance(boids[t], boid);
            if (d < 20.0f && d > 0.0f) {
                center += boid / d;
                weigth += 1.0f / d;
            }
        }
        if (weigth > 0) {
            center = center / weigth;
            forces[t] -= glm::normalize(boids[t] - center) * 10.0f;
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        forces[t] -= velocities[t] * deltaTime * 100.0f;
        auto f = glm::length(forces[t]);
        if (f > 100) {
            forces[t] = forces[t] * 100.0f / f;
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        if (glm::abs(boids[t].x) > 50 || glm::abs(boids[t].y) > 50 ||
            glm::abs(boids[t].z) > 50) {
            forces[t] -= boids[t] * 10.0f;
        }
    }
    if (touch) {
        for (int t = 0; t < boids.size(); ++t) {
            auto x = t % 8;
            auto y = (t / 8) % 8;
            auto z = (t / 8 / 8) % 8;
            auto c = (glm::vec3(x, y, z) - 4.0f) * 5.0f + pos;
            forces[t] += (c - boids[t]) * 300.0f;
            forces[t] -= velocities[t] * deltaTime * 500.0f;
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        velocities[t] += forces[t] * deltaTime;
        auto speed = glm::length(velocities[t]);
        boids[t] += velocities[t] * deltaTime * 1.0f;
        forces[t] = glm::vec3(0, 0, 0);
    }
}

[[nodiscard]] std::vector<glm::vec3> const &Boids::get_boids() const {
    return boids;
}
