// Example program:
// Using SDL2 to create an application window


#include <csignal>
#include <sstream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <GLES2/gl2.h>


struct Color {

    float red;
    float green;
    float blue;
    float alpha;
};

struct Platform {
    SDL_Window *window;
    SDL_GLContext glcontext;

    Platform();
    ~Platform();

    void clear_buffer(Color color);
    void show_buffer();
};

Platform::Platform() {
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

int main(int, char**) {


    Platform platform;

    Color red = { .red = 1.0, .green = 0.0, .blue = 0.0, .alpha = 1.0 };

    platform.clear_buffer(red);
    platform.show_buffer();

    SDL_Delay(3000);

    return 0;
}
