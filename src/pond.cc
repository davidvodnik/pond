#include "GL/glew.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include <cstddef>
#include <string>

#include "mesh.h"
#include "program.h"

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

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return 0;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program.gProgram);

        drawMesh(mesh);

        glUseProgram(NULL);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
