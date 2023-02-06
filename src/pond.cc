#include "GL/glew.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "system.h"
#include <exception>

struct App {
    SDL_Window *window{};
    System sys;
    Uint64 lastTime{};
    bool touch;
    int x;
    int y;
};

bool mainLoop(App &app) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            return false;
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                app.sys.resize(e.window.data1, e.window.data2);
            }
            break;
        case SDL_MOUSEMOTION:
            app.x = e.motion.x;
            app.y = e.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            app.touch = true;
            app.x = e.motion.x;
            app.y = e.motion.y;
            break;
        case SDL_MOUSEBUTTONUP:
            app.touch = false;
            app.x = e.motion.x;
            app.y = e.motion.y;
            break;
        }
    }

    Uint64 currentTime = SDL_GetPerformanceCounter();

    auto deltaTime = (double)(currentTime - app.lastTime) /
                     (double)SDL_GetPerformanceFrequency();

    if (deltaTime > 0.1) {
        deltaTime = 0.1;
    }

    app.sys.update((float)deltaTime, app.touch);

    SDL_GL_SwapWindow(app.window);

    app.lastTime = currentTime;

    return true;
}

void mainLoopEm(void *arg) {
    auto app = (App *)arg;
    mainLoop(*app);
}

int main() {
    int width = 640;
    int height = 480;

    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Pond", 0, 0, width, height,
                                   (unsigned)SDL_WINDOW_OPENGL |
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

#ifdef __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
#endif

    SDL_GL_CreateContext(window);

    glewInit();

    auto sys = System(width, height);

    auto app = App{window, sys, SDL_GetPerformanceCounter()};

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(mainLoopEm, &app, 0, 1);
#else
    while (mainLoop(app)) {
    }
#endif
}
