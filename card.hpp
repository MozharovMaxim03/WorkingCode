#pragma once
#include <string>
#include "ml/main.hpp"
#include<algorithm>

enum cardtype : char {
	CARDTYPE_1 = 3,
	CARDTYPE_2,
	CARDTYPE_3,
	CARDTYPE_4
};
enum cardvalue : char {
	CARDVALUE_2 = 2,
	CARDVALUE_3,
	CARDVALUE_4,
	CARDVALUE_5,
	CARDVALUE_6,
	CARDVALUE_7,
	CARDVALUE_8,
	CARDVALUE_9,
	CARDVALUE_10,
	CARDVALUE_J,
	CARDVALUE_Q,
	CARDVALUE_K,
	CARDVALUE_A,
};

struct card {
	cardtype t;
	cardvalue v;

	card(cardtype dt, cardvalue dv) : t{ dt }, v{ dv } {};
	card() : t{ (cardtype)0 }, v{ (cardvalue)0 } {}
};


inline bool sortcard(const card a, const card b) { 
	return a.v > b.v; 
};

enum cardset {
	CARDSET_OLDER,
	CARDSET_COUPLE,
	CARDSET_COUPLE2,
	CARDSET_THIRD,
	CARDSET_STREET,
	CARDSET_FLESH,
	CARDSET_FULLHOUSE,
	CARDSET_KARE,
	CARDSET_STREETFLESH,
	CARDSET_ROYALFLESH
};
struct cardcheck {
	cardvalue older;
	bool street;
	bool flesh;
	cardvalue couple2[2];
	cardvalue couple3;
	cardvalue couple4;

	inline cardset is() const {
		return older == CARDVALUE_A && flesh && street ? CARDSET_ROYALFLESH :
			flesh && street ? CARDSET_STREETFLESH :
			flesh ? CARDSET_FLESH :
			street ? CARDSET_STREET :
			couple4 != 0 ? CARDSET_KARE :
			couple3 != 0 && couple2[0] != 0 ? CARDSET_FULLHOUSE :
			couple3 != 0 ? CARDSET_THIRD :
			couple2[0] != 0 && couple2[1] != 0 ? CARDSET_COUPLE2 :
			couple2[0] != 0 ? CARDSET_COUPLE :
			CARDSET_OLDER;
	}
	inline operator str() const {
		return is() == CARDSET_ROYALFLESH ? "royal flesh" :
			is() == CARDSET_STREETFLESH ? "street flesh" :
			is() == CARDSET_FLESH ? "flesh" :
			is() == CARDSET_STREET ? "street" :
			is() == CARDSET_KARE ? "kare" :
			is() == CARDSET_FULLHOUSE ? "full-house" :
			is() == CARDSET_THIRD ? "third" :
			is() == CARDSET_COUPLE2 ? "two pair" :
			is() == CARDSET_COUPLE ? "pair" :
			"older card";
	}
};

struct cardlist {
	ml::arraylist<card> cards;

	static cardlist desk();

	inline cardlist(ml::arraylist<card> dcards) : cards{ dcards } {
		std::sort(cards.begin(), cards.end(), sortcard);
	}
	inline cardlist() {}

	inline void add(card v) {
		cards.add_end(v);
		std::sort(cards.begin(), cards.end(), sortcard);
	}
	inline card use() {
		return cards.rmv_start();
	}
	inline card usernd() {
		return cards.rmv(rand() % cards.size());
	}
	void getcards(cardlist desk) {
		for (size_t i = 0; i < 5; i++)
			add(desk.usernd());
	}
	cardcheck check();
	size_t score();
};