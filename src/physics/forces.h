#pragma once
#include <glm/glm.hpp>

auto limit(float lim) {
    return [=](auto &forces) {
        for (int t = 0; t < forces.size(); ++t) {
            auto f = glm::length(forces[t]);
            if (f > lim) {
                forces[t] = forces[t] * lim / f;
            }
        }
    };
}

auto drag(float coeff) {
    return [=](auto &forces, const auto &velocities) {
        for (int t = 0; t < forces.size(); ++t) {
            forces[t] -= velocities[t] * coeff;
        }
    };
}

auto box(float radius, float weigth) {
    return [=](auto &forces, auto &positions) {
        for (int t = 0; t < positions.size(); ++t) {
            if (glm::abs(positions[t].x) > radius ||
                glm::abs(positions[t].y) > radius ||
                glm::abs(positions[t].z) > radius) {
                forces[t] -= positions[t] * weigth;
            }
        }
    };
}

auto shape(glm::vec3 pos, float distance, float coeff, float drag_coeff) {
    return [=](auto &forces, const auto &velocities, const auto &positions,
               float deltaTime) {
        for (int t = 0; t < positions.size(); ++t) {
            auto x = t % 8;
            auto y = (t / 8) % 8;
            auto z = (t / 8 / 8) % 8;
            auto c = (glm::vec3(x, y, z) - 4.0f) * distance + pos;
            forces[t] += (c - positions[t]) * coeff;
            forces[t] -= velocities[t] * drag_coeff;
        }
    };
}

auto integrate(float deltaTime) {
    return [=](auto &forces, auto &velocities, auto &positions) {
        for (int t = 0; t < positions.size(); ++t) {
            velocities[t] += forces[t] * deltaTime;
            positions[t] += velocities[t] * deltaTime * 1.0f;
            forces[t] = glm::vec3(0, 0, 0);
        }
    };
}
