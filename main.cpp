#include "game.hpp"

void main() {
	game.fps(60);
	game.start();
	while (!game.isclose()) {
		game.update();
		game.begindraw();
		game.clearbg();
		game.draw();
		game.enddraw();
	}
}