#include "system.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

System::System(int width, int height) {
    auto p = createProgram();
    if (std::holds_alternative<std::string>(p)) {
        printf("%s\n", std::get<std::string>(p).c_str());
        std::terminate();
    }

    boids = Boids{};

    program = std::get<Program>(p);

    mesh = createMesh();

    camera = Camera{width, height};
}

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
    vec4 origin = glm::mul(glm::vec4(pt_x, pt_y, -1.f, 1.f), VPinv);
    origin.w = 1.0f / origin.w;
    origin.x *= origin.w;
    origin.y *= origin.w;
    origin.z *= origin.w;

    boids.update(deltaTime);

    glUseProgram(program.gProgram);

    for (auto &boid : boids.get_boids()) {
        glm::mat4 model = glm::translate(glm::mat4(1), boid);
        auto transformLoc = glGetUniformLocation(program.gProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                           glm::value_ptr(projectionView * model));
        drawMesh(mesh);
    }

    glUseProgram(NULL);
}
