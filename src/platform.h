#pragma once

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>
#include <string>
#include <sstream>
#include <csignal>
#include <vector>
#include <iostream>

#include "game.h"

struct Platform {

    SDL_Window *window;
    VkInstance instance;
    VkDevice device;

    // SDL initialization + cleanup
    void init_SDL();
    void cleanup_SDL();

    // vulkan initialization + cleanup
    void init_vulkan();
    void cleanup_vulkan();

    // event loop
    void process_event_queue(Game &game);
    void process_keydown(SDL_Keycode code, Game &game);

    Platform();
    ~Platform();

};


