#include "boids.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

Boids::Boids() {
    for (int i = 0; i < 500; ++i) {
        boids.emplace_back(glm::linearRand(glm::vec3(-50), glm::vec3(50)));
        velocities.emplace_back(glm::linearRand(glm::vec3(-1), glm::vec3(1)));
    }
}

void Boids::update(float deltaTime, bool touch, glm::vec3 dir) {
    // separation
    for (int t = 0; t < boids.size(); ++t) {
        auto close = glm::vec3(0);
        for (auto &boid : boids) {
            if (glm::distance(boids[t], boid) < 7.0f) {
                close += boids[t] - boid;
            }
        }
        velocities[t] += close * deltaTime * 10.0f;
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
            velocities[t] += glm::normalize(avg) * deltaTime * 100.0f;
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
            velocities[t] -=
                glm::normalize(boids[t] - center) * deltaTime * 10.0f;
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        if (glm::abs(boids[t].x) > 50 || glm::abs(boids[t].y) > 50 ||
            glm::abs(boids[t].z) > 50) {
            velocities[t] -= boids[t] * deltaTime * 10.0f;
        }
    }
    if (touch) {
        auto origin = glm::vec3(0, 0, -80);
        for (int t = 0; t < boids.size(); ++t) {
            auto zdir = glm::normalize(dir); // glm::vec3(0, 0, 1);
            auto intrs =
                origin + glm::dot(zdir, (boids[t] - glm::vec3(0, 0, -80)));
            auto f = boids[t] - intrs * zdir;
            float d = glm::length(f);
            velocities[t] -= (d * d * deltaTime * 1.0f) * glm::normalize(f);
        }
    }
    for (int t = 0; t < boids.size(); ++t) {
        auto speed = glm::length(velocities[t]);
        if (speed > 50) {
            velocities[t] = velocities[t] * 50.0f / speed;
        }
        boids[t] += velocities[t] * deltaTime * 1.0f;
    }
}

[[nodiscard]] std::vector<glm::vec3> const &Boids::get_boids() const {
    return boids;
}
