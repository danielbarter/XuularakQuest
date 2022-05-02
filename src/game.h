#pragma once

#include <vector>

struct Color {

    float red;
    float green;
    float blue;
    float alpha;

};

struct Point {

    float x;
    float y;
};


struct Vertex {
    Point point;
    Color color;
};

struct Game {

    bool running;
    Color background_color;
    std::vector<Vertex> vertex_buffer;


    Game();

};
