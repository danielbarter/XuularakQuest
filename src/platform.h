#pragma once

#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#include <csignal>
#include "game.h"

struct Platform {

    SDL_Window *window;
    SDL_GLContext glcontext;
    unsigned int vertex_buffer_object_id;
    unsigned int vertex_array_object_id;
    unsigned int vertex_shader_id;
    unsigned int fragment_shader_id;
    unsigned int program_id;

    Platform();
    ~Platform();

    void clear_buffer(Color color);
    void show_buffer();
    void process_event_queue(Game &game);
    void process_keydown(SDL_Keycode code, Game &game);
    void marshal_vertex_data(Game &game);
    void render(Game &game);

};


