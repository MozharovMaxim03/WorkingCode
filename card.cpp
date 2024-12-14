#include "card.hpp"

cardlist cardlist::desk()
{
	cardlist l;
	for (size_t v = 0; v < 13; v++)
		for (size_t t = 0; t < 4; t++)
			l.cards.add_end(card((cardtype)(t + CARDTYPE_1), (cardvalue)(v + CARDVALUE_2)));
	std::sort(l.cards.begin(), l.cards.end(), sortcard);
	return l;
}

cardcheck cardlist::check()
{
	cardvalue older = cards[0].v;
	bool street = true;
	bool flesh = true;
	uchar j = 0;
	cardvalue couple2[2] = { (cardvalue)0, (cardvalue)0 };
	cardvalue couple3 = (cardvalue)0;
	cardvalue couple4 = (cardvalue)0;
	for (size_t i = 0; i < 5; i++)
	{
		older = older < cards[i].v ? cards[i].v : older;
		if (i < 2 && cards[i].v == cards[i + 1].v && cards[i].v == cards[i + 2].v && cards[i].v == cards[i + 3].v) couple4 = cards[i].v;
		if (couple4 == 0 && i < 3 && cards[i].v == cards[i + 1].v && cards[i].v == cards[i + 2].v) couple3 = cards[i].v;
		if (couple4 == 0 && couple3 != cards[i].v && i < 4 && cards[i].v == cards[i + 1].v) couple2[j++] = cards[i].v;
		if (i < 4 && cards[i].v - 1 != cards[i + 1].v) street = false;
		if (i < 4 && cards[i].t != cards[i + 1].t) flesh = false;
	}
	return { older, street, flesh, {couple2[0], couple2[1]}, couple3, couple4 };
}

size_t cardlist::score()
{
	auto c = check();
	auto i = c.is();
	return i == CARDSET_OLDER ? c.older :
		i == CARDSET_COUPLE ? c.couple2[0] * 10 :
		i == CARDSET_COUPLE2 ? c.couple2[0] * 10 + c.couple2[1] * 10 :
		i == CARDSET_THIRD ? c.couple3 * 100 :
		i == CARDSET_STREET ? c.older * 1000 :
		i == CARDSET_FLESH ? c.older * 10000 :
		i == CARDSET_FULLHOUSE ? c.couple3 * 10000 + c.couple2[1] * 1000 :
		i == CARDSET_KARE ? c.couple4 * 100000 :
		i == CARDSET_STREETFLESH ? c.older * 1000000 : 99999999;
}
