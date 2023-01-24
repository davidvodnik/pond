#include "system.h"
#include "glm/ext/matrix_transform.hpp"
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

void System::update() {
    boids.update();

    auto projectionView = updateCamera(camera);

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
