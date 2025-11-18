#include <X11/Xlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#define LIMIT_FPS 100

/*
its faster than
SDL_DisplayID display = SDL_GetPrimaryDisplay();
const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(display);
*/
void X11_RootWindowAttrs(XWindowAttributes* attrs) {
    Display* display = XOpenDisplay(NULL);
    Window window = DefaultRootWindow(display);
    XGetWindowAttributes(display, window, attrs);
    XCloseDisplay(display);
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);

    XWindowAttributes attrs;
    X11_RootWindowAttrs(&attrs);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow(
            "Hello World",
            attrs.width,
            attrs.height,
            SDL_WINDOW_FULLSCREEN);

    renderer = SDL_CreateRenderer(window, NULL);

    printf("Renderer name: %s\n", SDL_GetRendererName(renderer));
    printf("FPS limit: %d\n", LIMIT_FPS);
    printf("Window size: %dx%d\n", attrs.width, attrs.height);

    SDL_Event Event;
    bool IsRunning = true;
    while (IsRunning) {
        Uint64 frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&Event)) {
            switch (Event.type) {
                case SDL_EVENT_QUIT:
                    IsRunning = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (Event.key.key) {
                        case SDLK_ESCAPE:
                        case SDLK_Q:
                            IsRunning = false;
                            break;
                    }
                    break;
            }
        }

        const double seed = ((double)SDL_GetTicks()) / 1000.0;
        const float red = (float)(0.5 + 0.5 * SDL_sin(seed));
        const float green =
            (float)(0.5 + 0.5 * SDL_sin(seed + SDL_PI_D * 2 / 3));
        const float blue =
            (float)(0.5 + 0.5 * SDL_sin(seed + SDL_PI_D * 4 / 3));
        SDL_SetRenderDrawColorFloat(
                renderer,
                red, green, blue,
                SDL_ALPHA_OPAQUE_FLOAT);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // milliseconds
        Uint64 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < 1000.0 / LIMIT_FPS) {
            SDL_Delay((Uint32)(1000.0 / LIMIT_FPS - frame_time));
        }
    }

    SDL_Quit();
    return 0;
}
