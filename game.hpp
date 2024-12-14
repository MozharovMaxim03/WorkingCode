#pragma once
#include "iostream"
#include "rl/main.hpp"
#include "card.hpp"

#define GAME_WIDTH 800
#define GAME_HEIGHT 600
#define GAME_TITLE "empty window"

struct rlobject {
	virtual void update() {}
	virtual void draw() {}
};

#define CARD_WIDTH 100
#define CARD_HEIGHT 150
struct rlcard : public rlobject, public card {
	vector2 pos;
	vector2 dragpos;
	bool drag = false;

	rlcard(vector2 dpos, cardtype type, cardvalue value) : card(type, value), pos{ dpos } {};
	rlcard(vector2 dpos, card card) : card(card), pos{ dpos } {};

	void draw() override;
	void update() override;
};

namespace img {
	extern size_t cardtypes;
	extern size_t card;
}

void game_start();
void game_update();
void game_draw();

extern window game;
extern camera3d camera;