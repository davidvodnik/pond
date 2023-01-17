#include "GL/glew.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include <cstddef>
#include <string>

#include "camera.h"
#include "mesh.h"
#include "program.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    auto p = createProgram();
    if (std::holds_alternative<std::string>(p)) {
        printf("%s\n", std::get<std::string>(p).c_str());
        return 1;
    }

    auto program = std::get<Program>(p);

    auto mesh = createMesh();

    auto camera = Camera{640, 480};

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return 0;
            }
        }

        auto projectionView = updateCamera(camera);

        glUseProgram(program.gProgram);

        auto transformLoc = glGetUniformLocation(program.gProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                           glm::value_ptr(projectionView));

        drawMesh(mesh);

        glUseProgram(NULL);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
