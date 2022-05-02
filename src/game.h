#pragma once

struct Color {

    float red;
    float green;
    float blue;
    float alpha;

};

struct Game {

    bool running;
    Color background_color;
    Game();

};

Game::Game() : running(true) {

    background_color =  {
	.red = 1.0,
	.green = 0.0,
	.blue = 0.0,
	.alpha = 1.0 };

};

