#include "platform.h"

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

	switch (event.type) {

	case SDL_KEYDOWN:
	    process_keydown( event.key.keysym.sym, game );
	    break;

	default:
	    break;
	}
    }
}

void Platform::process_keydown(SDL_Keycode sym, Game &game) {

    switch (sym) {

    case SDLK_ESCAPE:
	game.running = false;
	break;

    default:
	break;
    }

}

void Platform::render(Game &game) {
    clear_buffer(game.background_color);
    show_buffer();

}
