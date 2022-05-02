#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <GLES2/gl2.h>

#include "game.h"

struct Platform {

    SDL_Window *window;
    SDL_GLContext glcontext;

    Platform();
    ~Platform();

    void clear_buffer(Color color);
    void show_buffer();
    void process_event_queue(Game &game);
    void render(Game &game);

};


Platform::Platform()  {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "XuularakQuest",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr) {
	std::string error_message = (
	    std::ostringstream()
	    << "Could not create window: "
	    << SDL_GetError() << '\n').str();

	throw std::runtime_error(error_message);
    }


    glcontext = SDL_GL_CreateContext(window);
}


Platform::~Platform() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Platform::clear_buffer(Color color) {
    glClearColor(color.red, color.green, color.blue, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Platform::show_buffer() {
    SDL_GL_SwapWindow(window);
}

void Platform::process_event_queue(Game &game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
	if ( event.type == SDL_KEYDOWN )
	    game.running = false;
    }
}

void Platform::render(Game &game) {
    clear_buffer(game.background_color);
    show_buffer();

}
