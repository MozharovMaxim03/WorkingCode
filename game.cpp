#include "game.hpp"

cardlist desk = cardlist::desk();
ml::arraylist<rlcard> cards;
cardlist player;
#define COUNT 5

namespace img {
	size_t cardtypes = 0;
	size_t card = 0;
}

void game_start() {
	srand(time(0));
	img::card = textures.add("res/card.png");
	img::cardtypes = textures.add("res/cardtypes.png");
	for (size_t i = 0; i < COUNT; i++)
	{
		cards.add_end(rlcard(vector2(50 + rand() % GAME_WIDTH / 2, 50 + rand() % GAME_HEIGHT / 2), desk.usernd()));
		player.add(cards[i]);
	}
}

void game_update() {
	for (size_t i = 0; i < cards.size(); i++)
		cards[i].update();
}

void game_draw() {
	for (size_t i = 0; i < cards.size(); i++)
		cards[i].draw();
	draw::text_fast(10, 10, strg() <<  "set   : " << player.check(), 20, colors::black);
	draw::text_fast(10, 30, strg() << "score : " << player.score(), 20, colors::black);
}

window game = window(GAME_TITLE, GAME_WIDTH, GAME_HEIGHT, &game_start, &game_update, &game_draw);
camera3d camera = camera3d(0, vector3(1, 0, 0));

void rlcard::draw()
{
	draw::texture_fast_rotated(pos, 0, 0.5f, img::card, colors::white);
	str value = "?";
	switch (v)
	{
	case CARDVALUE_2:
	case CARDVALUE_3:
	case CARDVALUE_4:
	case CARDVALUE_5:
	case CARDVALUE_6:
	case CARDVALUE_7:
	case CARDVALUE_8:
	case CARDVALUE_9:
		value = v + '0';
		break;
	case CARDVALUE_10:
		value = "10";
		break;
	case CARDVALUE_J:
		value = "J";
		break;
	case CARDVALUE_Q:
		value = "Q";
		break;
	case CARDVALUE_K:
		value = "K";
		break;
	case CARDVALUE_A:
		value = "A";
		break;
	}
	draw::text_fast(pos + vector2(35, 20), value, 50, colors::black);
	draw::texture(pos.x + 25, pos.y + 85, rect2(t * 50, 0, 50, 50), img::cardtypes, colors::white);
}

void rlcard::update()
{
	if (Mouse::inArea(rect2(pos, CARD_WIDTH, CARD_HEIGHT)))
	{
		if (Mouse::onStart(MouseButton::MOUSE_BUTTON_LEFT))
		{
			dragpos = Mouse::position() - pos;
			drag = true;
		}
	}
	if (drag)
	{
		pos = Mouse::position() - dragpos;
		if (Mouse::onEnd(MouseButton::MOUSE_BUTTON_LEFT))
			drag = false;
	}
	
}
