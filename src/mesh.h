#include "GL/glew.h"

struct Mesh {
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
};

Mesh createMesh();
void drawMesh(const Mesh &mesh);
