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
    void process_keydown(SDL_Keycode code, Game &game);
    void render(Game &game);

};


