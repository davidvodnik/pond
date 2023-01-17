#include "system.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

System::System(int width, int height) {
    auto p = createProgram();
    if (std::holds_alternative<std::string>(p)) {
        printf("%s\n", std::get<std::string>(p).c_str());
        std::terminate();
    }

    program = std::get<Program>(p);

    mesh = createMesh();

    camera = Camera{width, height};
}

void System::update() {
    auto projectionView = updateCamera(camera);

    glUseProgram(program.gProgram);

    auto transformLoc = glGetUniformLocation(program.gProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                       glm::value_ptr(projectionView));

    drawMesh(mesh);

    glUseProgram(NULL);
}
