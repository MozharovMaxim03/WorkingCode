#pragma once
#include "utils.hpp"
#include "2d.hpp"
#include "3d.hpp"

#ifndef RL_LIB
#define RL_LIB 1.0f;
#endif // !RL_LIB

struct window {
	str title;
	unsigned int width;
	unsigned int height;

	color clearcolor = colors::light_blue;

	void(*start)(void);
	void(*update)(void);
	void(*draw)(void);

	inline window(str dtitle, uint dwidth, uint dheight, void(*dstart)(void), void(*dupdate)(void), void(*ddraw)(void)) : title{ dtitle }, width{ dwidth }, height{ dheight }, start{ dstart }, update{ dupdate }, draw{ ddraw } {
		InitWindow(width, height, title.c_str());
	};
	inline window() : title{ "" }, width{ 0 }, height{ 0 }, start{ ptr_empty_func }, update{ ptr_empty_func }, draw{ ptr_empty_func } {};
	inline ~window() {
		CloseWindow();
	}

	inline void begindraw() const {
		BeginDrawing();
	}
	inline void enddraw() const {
		EndDrawing();
	}

	inline void cursor(bool v) const {
		if (v) ShowCursor();
		else DisableCursor();
	}
	inline void fps(uchar v) const {
		SetTargetFPS(v);
	}
	inline bool isclose() const {
		return WindowShouldClose();
	}

	inline void clearbg() const {
		ClearBackground(clearcolor);
	}
};