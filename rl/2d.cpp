#include "2d.hpp"



void draw::text(const float x, const float y, const str text, const int size, const color dcolor, const int space) {
	str value = "";
	size_t j = 0;
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n') {
			DrawText(value.c_str(), x, y + (j++ + space) * size, size, dcolor);
			value = "";
		}
		else value += text[i];
	}
	if (value != "") DrawText(value.c_str(), x, y + (j + space) * size, size, dcolor);
}