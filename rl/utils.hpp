#pragma once
#include "raylib.h"
#include "iostream"
#include <string>
#include <vector>

inline void empty_func() {}
extern void (*ptr_empty_func)(void);

using str = std::string;
#define tostr(X) std::to_string(X);
template <typename T> using vec = std::vector<T>;

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using ulonglong = unsigned long long;

inline float lerp(const float start, const float end, const float delta) {
	return start > end ? end + (start - end) * delta : start + (end - start) * delta;
}
inline float lerp_line(const float start, const float end, const float delta) {
	return lerp(start, end, std::min(std::max(delta, 0.0f), 1.0f));
}
inline float lerp_arc(const float start, const float end, const float delta) {
	return lerp(start, end, sin(PI / 2 * std::min(std::max(delta, 0.0f), 1.0f)));
}

inline int lerp(const int start, const int end, const float delta) {
	return start > end ? end + (start - end) * delta : start + (end - start) * delta;
}
inline int lerp_line(const int start, const int end, const float delta) {
	return lerp(start, end, std::min(std::max(delta, 0.0f), 1.0f));
}
inline int lerp_arc(const int start, const int end, const float delta) {
	return lerp(start, end, sin(PI / 2 * std::min(std::max(delta, 0.0f), 1.0f)));
}

struct StrGenerator {
	struct _ {
		str value = "";

		inline _& operator << (const str v) {
			value += v;
			return *this;
		}
		inline _& operator << (const char* v) {
			value += v;
			return *this;
		}
		inline _& operator << (const char v) {
			value += v;
			return *this;
		}
		inline _& operator << (const bool v) {
			value += v ? "true" : "false";
			return *this;
		}
		inline _& operator << (const int v) {
			value += tostr(v);
			return *this;
		}
		inline _& operator << (const uint v) {
			value += tostr(v);
			return *this;
		}
		inline _& operator << (const long long v) {
			value += tostr(v);
			return *this;
		}
		inline _& operator << (const ulonglong v) {
			value += tostr(v);
			return *this;
		}
		inline _& operator << (const float v) {
			value += tostr(v);
			return *this;
		}
		inline _& operator << (const double v) {
			value += tostr(v);
			return *this;
		}
	};

	inline _ operator()() const {
		return _();
	}
} const strg;

struct timer {
private:
	uint _value;
	uint _max;
	bool _play;
public:
	timer(uint dmax) : _value{ 0 }, _max{ dmax }, _play{ true } {};

	inline void on() {
		_play = true;
	}
	inline void off() {
		_play = true;
	}

	inline void max(uint v) {
		_max = v;
	}
	inline uint max() const {
		return _max;
	}

	inline void value(uint v) {
		_value = v;
	}
	inline uint value() const {
		return _value;
	}

	inline void start() {
		value(0);
		on();
	}
	inline void update() {
		if (_value < _max) _value++;
	}
	inline bool is() const {
		return _value >= _max;
	}
};

template <typename T, size_t size>
struct list {
private:
	T* arr;

public:
	inline list() : arr{ new T[size] } {}
	list(T* o) : list() {
		for (size_t i = 0; i < size; i++)
			arr[i] = o[i];
	}
	inline list(const list& o) : list(o.arr) {}
	inline ~list() {
		delete[] arr;
	}

	inline size_t len() const {
		return size;
	}

	T* copy(T* out) const {
		for (size_t i = 0; i < size; i++)
			out[i] = arr[i];
		return out;
	}
	inline T* data() const {
		return arr;
	}
	inline T* newdata() {
		T* n = new T[size];
		return copy(n);
	}

	inline T operator[] (const size_t i) const {
		return arr[i];
	}
	inline T& operator[] (const size_t i) {
		return arr[i];
	}
};

template <typename T, size_t size>
struct arraylist {
private:
	T** arr;

public:
	arraylist() : arr{ new T * [size] } {
		for (size_t i = 0; i < size; i++)
			arr[i] = nullptr;
	}
	arraylist(T* o) : arraylist() {
		for (size_t i = 0; i < size; i++)
			arr[i] = new T(o[i]);
	}
	arraylist(T** o) : arraylist() {
		for (size_t i = 0; i < size; i++)
			arr[i] = new T(*o[i]);
	}
	inline arraylist(const arraylist& o) : arraylist(o.arr) {}
	~arraylist() {
		for (size_t i = 0; i < size; i++)
			if (arr[i] != nullptr) delete arr[i];
		delete[] arr;
	}

	inline size_t len() const {
		return size;
	}

	T* copy(T* out) const {
		for (size_t i = 0; i < size; i++)
			out[i] = *arr[i];
		return out;
	}
	T* copy(T** out) const {
		for (size_t i = 0; i < size; i++)
			out[i] = new T(arr[i]);
		return out;
	}
	inline T** data() const {
		return arr;
	}
	inline T** newdata() {
		T** n = new T * [size];
		return copy(n);
	}

	inline T* operator[] (const size_t i) const {
		return arr[i];
	}
	inline T* operator[] (const size_t i) {
		return arr[i];
	}

	size_t add(const T& v) {
		for (size_t i = 0; i < size; i++)
			if (arr[i] == nullptr) {
				arr[i] = new T(v);
				return i;
			}
		return -1;
	}
	size_t add(T* v) {
		for (size_t i = 0; i < size; i++)
			if (arr[i] == nullptr) {
				arr[i] = v;
				return i;
			}
		return -1;
	}
	bool rmv(size_t i) {
		if (arr[i] == nullptr) return false;
		delete arr[i];
		arr[i] = nullptr;
		return true;
	}

	inline arraylist& operator +(const T v) {
		add(v);
		return *this;
	}
	inline arraylist& operator -(const size_t i) {
		rmv(i);
		return *this;
	}
};

struct point2 {
	int x, y;

	inline point2(int dx, int dy) : x{ dx }, y{ dy } {}
	inline point2(int d) : point2(d, d) {}
	inline point2(const Vector2 d) : point2(d.x, d.y) {}
	inline point2() : point2(0) {}

	inline bool operator == (const point2 o) const {
		return x == o.x && y == o.y;
	}
	inline bool operator != (const point2 o) const {
		return x != o.x || y != o.y;
	}

	inline point2 operator + (const point2 o) const {
		return point2(x + o.x, y + o.y);
	}
	inline void operator += (const point2 o) {
		x += o.x;
		y += o.y;
	}
	inline point2 operator - (const point2 o) const {
		return point2(x - o.x, y - o.y);
	}
	inline void operator -= (const point2 o) {
		x -= o.x;
		y -= o.y;
	}
	inline point2 operator * (const point2 o) const {
		return point2(x * o.x, y * o.y);
	}
	inline void operator *= (const point2 o) {
		x *= o.x;
		y *= o.y;
	}
	inline point2 operator / (const point2 o) const {
		return point2(x / o.x, y / o.y);
	}
	inline void operator /= (const point2 o) {
		x /= o.x;
		y /= o.y;
	}

	inline operator str() const {
		return "( x: " + std::to_string(x) + "; y: " + std::to_string(y) + " )";
	}

	inline operator list<int, 2>() const {
		int arr[2] = { x, y };
		return arr;
	}

	inline operator Vector2() const {
		return { (float)x, (float)y };
	}
};

inline std::ostream& operator << (std::ostream& cout, const point2 o) {
	return cout << "( x: " << o.x << ", y: " << o.y << " )";
}

inline point2 lerp(const point2 start, const point2 end, const float delta) {
	return point2(
		lerp(start.x, end.x, delta),
		lerp(start.y, end.y, delta)
	);
}
inline point2 lerp_line(const point2 start, const point2 end, const float delta) {
	return lerp(start, end, std::min(std::max(delta, 0.0f), 1.0f));
}
inline point2 lerp_arc(const point2 start, const point2 end, const float delta) {
	return lerp(start, end, sin(PI / 2 * std::min(std::max(delta, 0.0f), 1.0f)));
}


struct vector2 {
	float x, y;

	inline vector2(float dx, float dy) : x{ dx }, y{ dy } {}
	inline vector2(float d) : vector2(d, d) {}
	inline vector2(const Vector2 d) : vector2(d.x, d.y) {}
	inline vector2() : vector2(0) {}

	inline float len_sqr() const {
		return x * x + y * y;
	}
	inline float len() const {
		return sqrt(len_sqr());
	}

	inline vector2& norm() {
		float l = len();
		x /= l;
		y /= l;
		return *this;
	}

	inline static vector2 angle(float angle, float length = 1) {
		return vector2(length * cos(angle), length * sin(angle));
	}
	inline float angle() const {
		return atan2f(x, y);
	}
	inline double angle_d() const {
		return atan2(x, y);
	}
	vector2& rotateto(float angle);
	vector2& rotateto(double angle);
	vector2& rotateby(float dangle) {
		return rotateto(angle() + dangle);
	}
	vector2& rotateby(double dangle) {
		return rotateto(angle_d() + dangle);
	}

	inline vector2 copy() const {
		return vector2(x, y);
	}

	inline vector2 operator!() const {
		return len();
	}
	inline vector2 operator+() const {
		return vector2(x, y) / len();
	}
	inline vector2 operator-() const {
		return vector2(-x, -y);
	}

	inline bool operator == (const vector2 o) const {
		return x == o.x && y == o.y;
	}
	inline bool operator != (const vector2 o) const {
		return x != o.x || y != o.y;
	}

	inline vector2 operator + (const vector2 o) const {
		return vector2(x + o.x, y + o.y);
	}
	inline void operator += (const vector2 o) {
		x += o.x;
		y += o.y;
	}
	inline vector2 operator - (const vector2 o) const {
		return vector2(x - o.x, y - o.y);
	}
	inline void operator -= (const vector2 o) {
		x -= o.x;
		y -= o.y;
	}
	inline vector2 operator * (const vector2 o) const {
		return vector2(x * o.x, y * o.y);
	}
	inline void operator *= (const vector2 o) {
		x *= o.x;
		y *= o.y;
	}
	inline vector2 operator * (const float o) const {
		return vector2(x * o, y * o);
	}
	inline void operator *= (const float o) {
		x *= o;
		y *= o;
	}
	inline vector2 operator / (const vector2 o) const {
		return vector2(x / o.x, y / o.y);
	}
	inline void operator /= (const vector2 o) {
		x /= o.x;
		y /= o.y;
	}
	inline vector2 operator / (const float o) const {
		return vector2(x / o, y / o);
	}
	inline void operator /= (const float o) {
		x /= o;
		y /= o;
	}

	inline operator str() const {
		return "{ x: " + std::to_string(x) + "; y: " + std::to_string(y) + " }";
	}

	inline operator list<float, 2>() const {
		float arr[2] = { x, y };
		return arr;
	}

	inline operator Vector2() const {
		return { x, y };
	}
};

inline std::ostream& operator << (std::ostream& cout, const vector2 o) {
	return cout << "{ x: " << o.x << ", y: " << o.y << " }";
}

inline vector2 lerp(const vector2 start, const vector2 end, const float delta) {
	return vector2(
		lerp(start.x, end.x, delta),
		lerp(start.y, end.y, delta)
	);
}
inline vector2 lerp_line(const vector2 start, const vector2 end, const float delta) {
	return lerp(start, end, std::min(std::max(delta, 0.0f), 1.0f));
}
inline vector2 lerp_arc(const vector2 start, const vector2 end, const float delta) {
	return lerp(start, end, sin(PI / 2 * std::min(std::max(delta, 0.0f), 1.0f)));
}


struct rect2 {
	float x, y;
	float w, h;

	inline rect2(const float dx, const float dy, const float dw, const float dh) : x{ dx }, y{ dy }, w{ dw }, h{ dh } {};
	inline rect2(const vector2 pos, const float dw, const float dh) : rect2(pos.x, pos.y, dw, dh) {};
	inline rect2(const float dx, const float dy, const vector2 size) : rect2(dx, dy, size.x, size.y) {};
	inline rect2(const vector2 pos, const vector2 size) : rect2(pos.x, pos.y, size.x, size.y) {};
	inline rect2(const Rectangle r) : rect2(r.x, r.y, r.width, r.height) {};

	inline operator Rectangle() const {
		return { x, y, w ,h };
	}

	inline vector2 center() const {
		return vector2(x + w / 2, y + h / 2);
	}

	inline bool operator == (const rect2 o) const {
		return x == o.x && y == o.y && w == o.w && h == o.h;
	}
	inline bool operator != (const rect2 o) const {
		return x != o.x || y != o.y || w != o.w || h != o.h;
	}

	inline rect2 operator + (const rect2 o) const {
		return rect2(x + o.x, y + o.y, w + o.w, h + o.h);
	}
	inline rect2 operator + (const vector2 o) const {
		return rect2(x + o.x, y + o.y, w, h);
	}
	inline void operator += (const rect2 o) {
		x += o.x;
		y += o.y;
		w += o.w;
		h += o.h;
	}
	inline void operator += (const vector2 o) {
		x += o.x;
		y += o.y;
	}

	inline rect2 operator - (const rect2 o) const {
		return rect2(x - o.x, y - o.y, w - o.w, h - o.h);
	}
	inline rect2 operator - (const vector2 o) const {
		return rect2(x - o.x, y - o.y, w, h);
	}
	inline void operator -= (const rect2 o) {
		x -= o.x;
		y -= o.y;
		w -= o.w;
		h -= o.h;
	}
	inline void operator -= (const vector2 o) {
		x -= o.x;
		y -= o.y;
	}

	inline rect2 operator * (const rect2 o) const {
		return rect2(x * o.x, y * o.y, w * o.w, h * o.h);
	}
	inline rect2 operator * (const vector2 o) const {
		return rect2(x * o.x, y * o.y, w, h);
	}
	inline void operator *= (const rect2 o) {
		x *= o.x;
		y *= o.y;
		w *= o.w;
		h *= o.h;
	}
	inline void operator *= (const vector2 o) {
		x *= o.x;
		y *= o.y;
	}

	inline rect2 operator / (const rect2 o) const {
		return rect2(x / o.x, y / o.y, w / o.w, h / o.h);
	}
	inline rect2 operator / (const vector2 o) const {
		return rect2(x / o.x, y / o.y, w, h);
	}
	inline void operator /= (const rect2 o) {
		x /= o.x;
		y /= o.y;
		w /= o.w;
		h /= o.h;
	}
	inline void operator /= (const vector2 o) {
		x /= o.x;
		y /= o.y;
	}
};

inline std::ostream& operator << (std::ostream& cout, const rect2 o) {
	return cout << "{ x: " << o.x << ", y: " << o.y << ", w: " << o.w << ", h: " << o.h << " }";
}

struct color_t {
	uchar v;

	static inline uchar range(int v) {
		return v < 0 ? 0 : v > 255 ? 255 : v;
	}

	inline color_t(uchar dv) : v{ dv } {};
	inline color_t(int dv) : color_t(range(dv)) {};
	inline color_t() : color_t(0) {};

	inline operator int() const {
		return (int)v;
	}
	inline operator uchar() const {
		return v;
	}
	inline operator str() const {
		return tostr((int)v);
	}

	inline bool operator == (const color_t d) const {
		return v == d.v;
	}
	inline bool operator != (const color_t d) const {
		return v != d.v;
	}
	inline bool operator > (const color_t d) const {
		return v > d.v;
	}
	inline bool operator >= (const color_t d) const {
		return v >= d.v;
	}
	inline bool operator < (const color_t d) const {
		return v < d.v;
	}
	inline bool operator <= (const color_t d) const {
		return v <= d.v;
	}

	inline color_t operator+(const color_t o) const {
		return color_t((int)v + (int)o.v);
	}
	inline color_t operator+=(const color_t o) {
		v = range((int)v + (int)o.v);
	}

	inline color_t operator-(const color_t o) const {
		return color_t((int)v - (int)o.v);
	}
	inline color_t operator-=(const color_t o) {
		v = range((int)v - (int)o.v);
	}

	inline color_t operator*(const color_t o) const {
		return color_t((int)v * (int)o.v);
	}
	inline color_t operator*=(const color_t o) {
		v = range((int)v * (int)o.v);
	}
	inline color_t operator*(const float o) const {
		return color_t((int)(v * o));
	}
	inline color_t operator*=(const float o) {
		v = range((int)(v * o));
	}

	inline color_t operator/(const color_t o) const {
		return color_t((int)v / (int)o.v);
	}
	inline color_t operator/=(const color_t o) {
		v = range((int)v / (int)o.v);
	}
	inline color_t operator/(const float o) const {
		return color_t((int)(v / o));
	}
	inline color_t operator/=(const float o) {
		v = range((int)(v / o));
	}
};
inline std::ostream& operator << (std::ostream& cout, const color_t o) {
	return cout << (int)o;
}

struct color {
	color_t r, g, b, a;

	inline color(color_t dr, color_t dg, color_t db, color_t da) : r{ dr }, g{ dg }, b{ db }, a{ da } {};
	inline color(color_t dr, color_t dg, color_t db) : color(dr, dg, db, 255) {};
	inline color(color_t d) : color(d, d, d, 255) {};
	inline color(const Color o) : color(o.r, o.g, o.b, o.a) {};
	inline color() : color(0, 0, 0, 0) {};

	inline bool operator == (const color o) const {
		return r == o.r && g == o.g && b == o.b && a == o.a;
	}
	inline bool operator != (const color o) const {
		return r != o.r || g != o.g || b != o.b || a != o.a;
	}

	inline color operator + (const color o) const {
		return color(r + o.r, g + o.g, b + o.b, a + o.a);
	}
	inline void operator += (const color o) {
		r += o.r;
		g += o.g;
		b += o.b;
		a += o.a;
	}
	inline color operator - (const color o) const {
		return color(r - o.r, g - o.g, b - o.b, a - o.a);
	}
	inline void operator -= (const color o) {
		r -= o.r;
		g -= o.g;
		b -= o.b;
		a -= o.a;
	}
	inline color operator * (const color o) const {
		return color(r * o.r, g * o.g, b * o.b, a * o.a);
	}
	inline void operator *= (const color o) {
		r *= o.r;
		g *= o.g;
		b *= o.b;
		a *= o.a;
	}
	inline color operator / (const color o) const {
		return color(r / o.r, g / o.g, b / o.b, a / o.a);
	}
	inline void operator /= (const color o) {
		r /= o.r;
		g /= o.g;
		b /= o.b;
		a /= o.a;
	}

	inline operator str() const {
		return "[ r: " + std::to_string(r) + "; g: " + std::to_string(g) + "; b: " + std::to_string(b) + "; a: " + std::to_string(a) + " ]";
	}

	inline operator list<color_t, 4>() const {
		color_t arr[4] = { r, g, b, a };
		return arr;
	}
	inline operator list<int, 4>() const {
		int arr[4] = { r, g, b, a };
		return arr;
	}
	inline operator list<uchar, 4>() const {
		uchar arr[4] = { r, g, b, a };
		return arr;
	}

	inline operator Color() const {
		return Color{ r, g, b, a };
	}
};

namespace colors {
	const color red(255, 0, 0);
	const color orange(255, 100, 0);
	const color gold(255, 170, 0);
	const color yellow(255, 255, 0);
	const color lime(170, 255, 0);
	const color green(0, 255, 0);
	const color cyan(0, 255, 190);
	const color light_blue(0, 230, 255);
	const color sky_blue(0, 150, 255);
	const color blue(0, 0, 255);
	const color purple(140, 0, 255);
	const color pink(255, 0, 255);

	const color white(255, 255, 255);
	const color light_gray(192, 192, 192);
	const color gray(128, 128, 128);
	const color dark_gray(64, 64, 64);
	const color black(0, 0, 0);
}

template<typename T>
struct DataManager {
private:
	std::vector<T> arr;
	T(*load)(const char*);
	void (*unload)(T);
public:
	inline DataManager(T(*dload)(const char*), void (*dunload)(T)) : load{ dload }, unload{ dunload } {};
	inline size_t add(const char* path) {
		arr.push_back(load(path));
		return size() - 1;
	}
	inline size_t add(str path) {
		arr.push_back(load(path.c_str()));
		return size() - 1;
	}

	inline T operator[](const size_t i) const {
		return arr[i];
	}

	inline size_t size() const {
		return arr.size();
	}

	~DataManager()
	{
		for (size_t i = 0; i < arr.size(); i++)
			unload(arr[i]);
	}
};
extern DataManager<Image> images;
extern DataManager<Texture> textures;
extern DataManager<Sound> sounds;

struct atexture {
	size_t textureid;
	int w, h;
	float x, y;

	inline atexture(const size_t dtextureid, const int framewidth, const int frameheight) : textureid{ dtextureid }, w{ framewidth }, h{ frameheight }, x{ 0 }, y{ 0 } {}

	inline operator rect2() const {
		return rect2( x * w, y * h, w, h );
	}
	inline operator size_t() const {
		return textureid;
	}

	inline atexture& next(const float dx, const float dy) {
		x += dx;
		y += dy;
		return *this;
	}
	inline atexture& next(const Vector2 dpos) {
		x += dpos.x;
		y += dpos.y;
		return *this;
	}

	inline atexture& use(const float dx, const float dy) {
		x = dx;
		y = dy;
		return *this;
	}
	inline atexture& use(const Vector2 dpos) {
		x = dpos.x;
		y = dpos.y;
		return *this;
	}
};

struct Mouse {
	// position of mouse
	static inline vector2 position() {
		return GetMousePosition();
	}
	// every times while mouse button is down
	static inline bool isDown(MouseButton button) {
		return IsMouseButtonDown(button);
	}
	// every times while mouse button is up
	static inline bool isUp(MouseButton button) {
		return IsMouseButtonUp(button);
	}
	// when mouse button is down
	static inline bool onStart(MouseButton button) {
		return IsMouseButtonPressed(button);
	}
	// when mouse button is up
	static inline bool onEnd(MouseButton button) {
		return IsMouseButtonReleased(button);
	}

	// check mouse in area
	static inline bool inArea(rect2 area) {
		return CheckCollisionPointRec(position(), area);
	}
};

struct Keyboard {
	// every times while key is down
	static inline bool isDown(char key) {
		return IsKeyDown(key);
	}
	// every times while key is up
	static inline bool isUp(char key) {
		return IsKeyUp(key);
	}
	// when key is down
	static inline bool onStart(char key) {
		return IsKeyPressed(key);
	}
	// when key is up
	static inline bool onEnd(char key) {
		return IsKeyReleased(key);
	}
};