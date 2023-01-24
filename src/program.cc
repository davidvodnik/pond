#include "program.h"
#include "GL/glew.h"
#include "vertex.h"
#include <string>
#include <variant>

auto vertexShaderSource =
    R"glsl(
        in vec3 aPos;
        uniform mat4 transform;
        void main() {
             gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1 );
         }
    )glsl";

auto fragmentShaderSource =
    R"glsl(
        precision mediump float;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )glsl";

std::variant<GLuint, std::string> createShader(const std::string &source,
                                               GLenum type) {
#if __EMSCRIPTEN__
    auto fullSource = "#version 300 es\n" + source;
#else
    auto fullSource = "#version 330 core\n" + source;
#endif
    GLuint shader = glCreateShader(type);
    auto cSource = fullSource.c_str();
    glShaderSource(shader, 1, &cSource, nullptr);
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
