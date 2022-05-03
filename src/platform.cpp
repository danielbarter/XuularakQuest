#include "platform.h"

const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec4 color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
    "}\0";

const char *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "    frag_color = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\0";


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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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

void Platform::marshal_vertex_data(Game &game) {

    int success;
    char infoLog[512];

    vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader_id);

    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(vertex_shader_id, 512, NULL, infoLog);
	std::cout << "vertex shader error: " <<  infoLog << '\n';
    }


    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
	glGetShaderInfoLog(fragment_shader_id, 512, NULL, infoLog);
	std::cout << "fragment shader error: " <<  infoLog << '\n';
    }




    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
	glGetProgramInfoLog(program_id, 512, NULL, infoLog);
	std::cout << "shader link error: " << infoLog << '\n';
    }

    glGenVertexArrays(1, &vertex_array_object_id);
    glGenBuffers(1, &vertex_buffer_object_id);


    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_id);
    raise(SIGINT);
    glBufferData(
	GL_ARRAY_BUFFER,
	game.vertex_buffer.size() * sizeof(Vertex),
	game.vertex_buffer.data(),
	GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*) 0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*) 2);

}


void Platform::render(Game &game) {
    clear_buffer(game.background_color);
    glUseProgram(program_id);
    glBindVertexArray(vertex_array_object_id);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    show_buffer();

}
