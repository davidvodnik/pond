#include "GL/glew.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Pond", 0, 0, 640, 480,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GL_CreateContext(window);

    glewInit();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return 0;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
