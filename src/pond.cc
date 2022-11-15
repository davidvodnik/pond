#include "GL/glew.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include <cstddef>
#include <string>
#include <variant>

auto vertexShaderSource =
    R"glsl(
        #version 140
        in vec2 LVertexPos2D;
        void main() {
             gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
         }
    )glsl";

auto fragmentShaderSource =
    R"glsl(
        #version 140
        out vec4 LFragment;
        void main() {
            LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );
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

GLint gVertexPosLocation;

std::variant<GLuint, std::string> createProgram() {
    auto program = glCreateProgram();

    auto vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    if (std::holds_alternative<std::string>(vertexShader)) {
        return std::get<std::string>(vertexShader);
    }
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

    gVertexPosLocation = glGetAttribLocation(program, "LVertexPos2D");
    if (gVertexPosLocation == -1) {
        return "LVertexPos2D not found";
    }

    return program;
}

GLuint gProgram;
GLuint gVAO;
GLuint gVBO;
GLuint gIBO;

bool init() {
    auto p = createProgram();
    if (std::holds_alternative<std::string>(p)) {
        printf("%s\n", std::get<std::string>(p).c_str());
        return false;
    }

    gProgram = std::get<GLuint>(p);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLfloat vertexData[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

    GLuint indexData[] = {0, 1, 2, 3};

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<unsigned long>(2) * 4 * sizeof(GLfloat),
                 vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData,
                 GL_STATIC_DRAW);

    glBindVertexArray(0);

    return true;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glBindVertexArray(gVAO);
    glEnableVertexAttribArray(gVertexPosLocation);

    glVertexAttribPointer(gVertexPosLocation, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), nullptr);

    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(gVertexPosLocation);

    glUseProgram(NULL);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Pond", 0, 0, 640, 480,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_CreateContext(window);

    glewInit();

    if (!init()) {
        return 1;
    }

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return 0;
            }
        }

        render();
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
