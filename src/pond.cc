#include "GL/glew.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"

#include "system.h"

int main() {
    int width = 640;
    int height = 480;

    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Pond", 0, 0, width, height,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_CreateContext(window);

    glewInit();

    System system(width, height);

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return 0;
            }
        }

        system.update();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
