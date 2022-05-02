#include "platform.h"

int main(int, char**) {


    Platform platform;
    Game game;


    while ( game.running ) {
	platform.process_event_queue(game);
	platform.render(game);
    };


    return 0;
}
