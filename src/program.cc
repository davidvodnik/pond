#include "program.h"
#include "GL/glew.h"
#include "vertex.h"
#include <string>
#include <variant>

auto vertexShaderSource =
    R"glsl(
        #version 330 core
        in vec3 aPos;
        void main() {
             gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1 );
         }
    )glsl";

auto fragmentShaderSource =
    R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )glsl";

std::variant<GLuint, std::string> createShader(const std::string &source,
                                               GLenum type) {
    GLuint shader = glCreateShader(type);
    auto x = source.c_str();
    glShaderSource(shader, 1, &x, nullptr);
    glCompileShader(shader);

    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE) {
        int logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string log;
        log.resize(logLength - 1);
        glGetShaderInfoLog(shader, logLength, &logLength, &log[0]);
        return log;
    }

    return shader;
}

std::variant<Program, std::string> createProgram() {
    auto program = glCreateProgram();

    auto vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    if (std::holds_alternative<std::string>(vertexShader)) {
        return std::get<std::string>(vertexShader);
    }
    glBindAttribLocation(program, vertexPosLocation, "aPos");
    auto fragmentShader =
        createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    if (std::holds_alternative<std::string>(fragmentShader)) {
        return std::get<std::string>(fragmentShader);
    }

    glAttachShader(program, std::get<GLuint>(vertexShader));
    glAttachShader(program, std::get<GLuint>(fragmentShader));

    glLinkProgram(program);
    GLint programSuccess = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        int logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::string log;
        log.resize(logLength - 1);
        glGetProgramInfoLog(program, logLength, &logLength, &log[0]);
        return log;
    }

    return Program{program};
}