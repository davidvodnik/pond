#include "renderer.h"
#include "glm/ext/matrix_transform.hpp"
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() {
    auto p = createProgram();
    if (std::holds_alternative<std::string>(p)) {
        printf("%s\n", std::get<std::string>(p).c_str());
        std::terminate();
    }

    program = std::get<Program>(p);

    mesh = createMesh();
}

void Renderer::Render(const std::vector<glm::vec3>& positions, const glm::mat4x4& projectionView) {
    glUseProgram(program.gProgram);

    for (auto boid : positions) {
        glm::mat4 model = glm::translate(glm::mat4(1), boid);
        auto transformLoc = glGetUniformLocation(program.gProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                           glm::value_ptr(projectionView * model));
        drawMesh(mesh);
    }

    glUseProgram(NULL);
}