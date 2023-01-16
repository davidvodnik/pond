#include "mesh.h"
#include "vertex.h"

Mesh createMesh() {
    GLfloat vertexData[] = {-0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
                            0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f};

    GLuint indexData[] = {0, 1, 2, 0, 2, 3};

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<unsigned long>(3) * 4 * sizeof(GLfloat),
                 vertexData, GL_STATIC_DRAW);

    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indexData,
                 GL_STATIC_DRAW);

    glBindVertexArray(0);

    return {VAO, VBO, IBO};
}

void drawMesh(const Mesh &mesh) {
    glBindVertexArray(mesh.VAO);
    glEnableVertexAttribArray(vertexPosLocation);

    glVertexAttribPointer(vertexPosLocation, 2, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), nullptr);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(vertexPosLocation);
}
