#pragma once
#include <glm/glm.hpp>

auto separation(float coeff, float radius) {
    return [=](auto &forces, const auto &positions) {
        for (int t = 0; t < positions.size(); ++t) {
            auto close = glm::vec3(0);
            for (auto &boid : positions) {
                if (glm::distance(positions[t], boid) < radius) {
                    close += positions[t] - boid;
                }
            }
            forces[t] += close * coeff;
        }
    };
}

auto alignment(float coeff, float radius) {
    return [=](auto &forces, const auto &velocities, const auto &positions) {
        for (int t = 0; t < positions.size(); ++t) {
            auto vel = glm::vec3(0);
            float weigth = 0;
            for (int s = 0; s < positions.size(); ++s) {
                float d = glm::distance(positions[t], positions[s]);
                if (d < radius && d > 0.0f) {
                    vel += velocities[s] / d;
                    weigth += 1.0f / d;
                }
            }
            if (weigth > 0) {
                glm::vec3 avg = vel / weigth;
                forces[t] += glm::normalize(avg) * coeff;
            }
        }
    };
}

auto cohesion(float coeff, float radius) {
    return [=](auto &forces, const auto &velocities, const auto &positions) {
        for (int t = 0; t < positions.size(); ++t) {
            auto center = glm::vec3(0);
            float weigth = 0;
            for (auto &boid : positions) {
                float d = glm::distance(positions[t], boid);
                if (d < radius && d > 0.0f) {
                    center += boid / d;
                    weigth += 1.0f / d;
                }
            }
            if (weigth > 0) {
                center = center / weigth;
                forces[t] -= glm::normalize(positions[t] - center) * coeff;
            }
        }
    };
}
