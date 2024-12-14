#pragma once
#include "utils.hpp"

namespace draw {
	inline void rect(const float x, const float y, const float w, const float h, const color dcolor) {
		DrawRectangle(x, y, w, h, dcolor);
	}
	inline void rect(const vector2 position, const float w, const float h, const color dcolor) {
		DrawRectangle(position.x, position.y, w, h, dcolor);
	}
	inline void rect(const float x, const float y, const vector2 size, const color dcolor) {
		DrawRectangle(x, y, size.x, size.y, dcolor);
	}
	inline void rect(const vector2 position, const vector2 size, const color dcolor) {
		DrawRectangleV(position, size, dcolor);
	}
	inline void rect(const rect2 r, const color dcolor) {
		DrawRectangle(r.x, r.y, r.w, r.h, dcolor);
	}

	inline void circle_center(const float x, const float y, const float radius, const color dcolor) {
		DrawCircle(x, y, radius, dcolor);
	}
	inline void circle_center(const vector2 position, const float radius, const color dcolor) {
		DrawCircleV(position, radius, dcolor);
	}

	inline void circle(const float x, const float y, const float radius, const color dcolor) {
		circle_center(x - radius / 2, y - radius / 2, radius, dcolor);
	}
	inline void circle(const vector2 position, const float radius, const color dcolor) {
		circle_center(position.x - radius / 2, position.y - radius / 2, radius, dcolor);
	}

	inline void ring(const float x, const float y, const float inner_radius, const float outer_radius, const color dcolor, const float start = 0, const float end = 360, const int segments = 1) {
		DrawRing(vector2(x, y), inner_radius, outer_radius, start, end, segments, dcolor);
	}
	inline void ring(const vector2 center, const float inner_radius, const float outer_radius, const color dcolor, const float start = 0, const float end = 360, const int segments = 1) {
		DrawRing(center, inner_radius, outer_radius, start, end, segments, dcolor);
	}
	inline void ring_easy(const vector2 center, const float radius, const float width, const color dcolor, const float start = 0, const float end = 360, const int segments = 1) {
		DrawRing(center, radius, radius + width, start, end, segments, dcolor);
	}

	void text(const float x, const float y, const str text, const int size, const color dcolor, const int space = 0);
	inline void text(const vector2 position, const str dtext, const int size, const color dcolor, const int space = 0) {
		text(position.x, position.y, dtext, size, dcolor, space);
	}
	inline void text(const float x, const float y, const StrGenerator::_ dtext, const int size, const color dcolor, const int space = 0) {
		text(x, y, dtext.value.c_str(), size, dcolor, space);
	}
	inline void text(const vector2 position, const StrGenerator::_ dtext, const int size, const color dcolor, const int space = 0) {
		text(position.x, position.y, dtext.value.c_str(), size, dcolor, space);
	}

	inline void text_fast(const float x, const float y, const str dtext, const int size, const color dcolor) {
		DrawText(dtext.c_str(), x, y, size, dcolor);
	}
	inline void text_fast(const vector2 position, const str dtext, const int size, const color dcolor) {
		text_fast(position.x, position.y, dtext, size, dcolor);
	}
	inline void text_fast(const float x, const float y, const StrGenerator::_ dtext, const int size, const color dcolor) {
		text_fast(x, y, dtext.value.c_str(), size, dcolor);
	}
	inline void text_fast(const vector2 position, const StrGenerator::_ dtext, const int size, const color dcolor) {
		text_fast(position.x, position.y, dtext.value.c_str(), size, dcolor);
	}

	inline void texture_fast(const float x, const float y, const size_t id, const color dcolor) {
		DrawTexture(textures[id], x, y, dcolor);
	}
	inline void texture_fast(const vector2 position, const size_t id, const color dcolor) {
		DrawTexture(textures[id], position.x, position.y, dcolor);
	}

	inline void texture(const float x, const float y, const float frame_x, const float frame_y, const float frame_w, const float frame_h, const size_t id, const color dcolor) {
		DrawTextureRec(textures[id], rect2(frame_x, frame_y, frame_w, frame_h), vector2(x, y), dcolor);
	}
	inline void texture(const vector2 position, const float frame_x, const float frame_y, const float frame_w, const float frame_h, const size_t id, const color dcolor) {
		DrawTextureRec(textures[id], rect2(frame_x, frame_y, frame_w, frame_h), position, dcolor);
	}
	inline void texture(const float x, const float y, const rect2 frame, const size_t id, const color dcolor) {
		DrawTextureRec(textures[id], frame, vector2(x, y), dcolor);
	}
	inline void texture(const vector2 position, const rect2 frame, const size_t id, const color dcolor) {
		DrawTextureRec(textures[id], frame, position, dcolor);
	}

	inline void texture(const float x, const float y, const atexture dtexture, const color dcolor) {
		texture(x, y, dtexture, dtexture, dcolor);
	}
	inline void texture(const vector2 position, const atexture dtexture, const color dcolor) {
		texture(position, dtexture, dtexture, dcolor);
	}


	inline void texture_fast_rotated(const float x, const float y, const float rotation, const float scale, const size_t id, const color dcolor) {
		DrawTextureEx(textures[id], vector2(x, y), rotation, scale, dcolor);
	}
	inline void texture_fast_rotated(const vector2 position, const float rotation, const float scale, const size_t id, const color dcolor) {
		DrawTextureEx(textures[id], position, rotation, scale, dcolor);
	}

	inline void texture_rotated(const rect2 dest, const rect2 frame, const vector2 origin, const float rotation, const size_t id, const color dcolor) {
		DrawTexturePro(textures[id], frame, dest, origin, rotation, dcolor);
	}
	inline void texture_rotated(const rect2 dest, const atexture dtexture, const vector2 origin, const float rotation, const color dcolor) {
		texture_rotated(dest, dtexture, origin, rotation, dtexture, dcolor);
	}
	inline void texture_rotated(const rect2 dest, const rect2 frame, const float rotation, const size_t id, const color dcolor) {
		texture_rotated(dest, frame, 0, rotation, id, dcolor);
	}
	inline void texture_rotated(const rect2 dest, const atexture dtexture, const float rotation, const color dcolor) {
		texture_rotated(dest, dtexture, 0, rotation, dtexture, dcolor);
	}
}