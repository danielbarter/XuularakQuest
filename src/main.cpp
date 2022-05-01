// Example program:
// Using SDL2 to create an application window

#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#include <stdio.h>

int main(int, char**) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;

    window = SDL_CreateWindow(
        "XuularakQuest",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }


    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    SDL_Delay(3000);

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
