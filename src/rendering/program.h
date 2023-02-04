#include "GL/glew.h"
#include <string>

struct Program {
    GLuint gProgram;
};

std::variant<Program, std::string> createProgram();
