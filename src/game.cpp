#include "game.h"

Game::Game() : running(true) {

    background_color =  {
	.red = 0.3,
	.green = 0.3,
	.blue = 0.3,
	.alpha = 1.0 };

    vertex_buffer.push_back(
	Vertex {
	    .point = { .x = 0, .y = -0.5 },
	    .color = { .red = 1.0, .green = 0.0, .blue = 0.0, .alpha = 1.0}
	});

    vertex_buffer.push_back(
	Vertex {
	    .point = { .x = 0, .y = 0.5 },
	    .color = { .red = 1.0, .green = 0.0, .blue = 0.0, .alpha = 1.0}
	});

    vertex_buffer.push_back(
	Vertex {
	    .point = { .x = 0.5, .y = 0 },
	    .color = { .red = 1.0, .green = 0.0, .blue = 0.0, .alpha = 1.0}
	});


};

