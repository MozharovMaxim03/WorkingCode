#pragma once
#include "utils.hpp"

struct vector3 {
	float x, y, z;

	inline vector3(float dx, float dy, float dz) : x{ dx }, y{ dy }, z{ dz } {}
	inline vector3(float d) : vector3(d, d, d) {}
	inline vector3(const Vector3 d) : vector3(d.x, d.y, d.z) {}
	inline vector3() : vector3(0) {}

	inline float len_sqr() const {
		return x * x + y * y + z * z;
	}
	inline float len() const {
		return sqrt(len_sqr());
	}

	inline void norm() {
		float l = len();
		x /= l;
		y /= l;
		z /= l;
	}

	inline vector3 copy() const {
		return vector3(x, y, z);
	}

	inline vector3 operator!() const {
		return len();
	}
	inline vector3 operator+() const {
		return vector3(x, y, z) / len();
	}
	inline vector3 operator-() const {
		return vector3(-x, -y, -z);
	}

	inline bool operator == (const vector3 o) const {
		return x == o.x && y == o.y && z == o.z;
	}
	inline bool operator != (const vector3 o) const {
		return x != o.x || y != o.y || z != o.z;
	}

	inline vector3 operator + (const vector3 o) const {
		return vector3(x + o.x, y + o.y, z + o.z);
	}
	inline void operator += (const vector3 o) {
		x += o.x;
		y += o.y;
		z += o.z;
	}
	inline vector3 operator - (const vector3 o) const {
		return vector3(x - o.x, y - o.y, z - o.z);
	}
	inline void operator -= (const vector3 o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
	}
	inline vector3 operator * (const vector3 o) const {
		return vector3(x * o.x, y * o.y, z * o.z);
	}
	inline void operator *= (const vector3 o) {
		x *= o.x;
		y *= o.y;
		z *= o.z;
	}
	inline vector3 operator * (const float o) const {
		return vector3(x * o, y * o, z * o);
	}
	inline void operator *= (const float o) {
		x *= o;
		y *= o;
		z *= o;
	}
	inline vector3 operator / (const vector3 o) const {
		return vector3(x / o.x, y / o.y, z / o.z);
	}
	inline void operator /= (const vector3 o) {
		x /= o.x;
		y /= o.y;
		z /= o.z;
	}
	inline vector3 operator / (const float o) const {
		return vector3(x / o, y / o, z / o);
	}
	inline void operator /= (const float o) {
		x /= o;
		y /= o;
		z /= o;
	}

	inline operator str() const {
		return "{ x: " + std::to_string(x) + "; y: " + std::to_string(y) + "; z: " + std::to_string(z) + " }";
	}

	inline operator list<float, 3>() const {
		float arr[3] = { x, y, z };
		return arr;
	}

	inline operator Vector3() const {
		return { x, y, z };
	}
};

inline std::ostream& operator << (std::ostream& cout, const vector3 o) {
	return cout << "{ x: " << o.x << ", y: " << o.y << ", z: " << o.z << " }";
}

inline vector3 lerp(const vector3 start, const vector3 end, const float delta) {
	return vector3(
		lerp(start.x, end.x, delta),
		lerp(start.y, end.y, delta),
		lerp(start.z, end.z, delta)
	);
}
inline vector3 lerp_line(const vector3 start, const vector3 end, const float delta) {
	return lerp(start, end, std::min(std::max(delta, 0.0f), 1.0f));
}
inline vector3 lerp_arc(const vector3 start, const vector3 end, const float delta) {
	return lerp(start, end, sin(PI / 2 * std::min(std::max(delta, 0.0f), 1.0f)));
}

struct box3 {
	float x, y, z;
	float w, h, l;

	inline box3(const float dx, const float dy, const float dz, const float dw, const float dh, const float dl) : x{ dx }, y{ dy }, z{ dz }, w{ dw }, h{ dh }, l{ dl } {};
	inline box3(const vector3 pos, const vector3 size) : box3(pos.x, pos.y, pos.z, size.x, size.y, size.z) {};
	inline box3(const BoundingBox b) : box3(b.min, b.max) {};

	inline operator BoundingBox() const {
		return { {x, y, z}, {x + w, y + h, z + l} };
	}

	inline vector3 center() const {
		return vector3(x + w / 2, y + h / 2, z + l / 2);
	}

	inline bool operator == (const box3 o) const {
		return x == o.x && y == o.y && z == o.z && w == o.w && h == o.h && l == o.l;
	}
	inline bool operator != (const box3 o) const {
		return x != o.x || y != o.y || z != o.z || w != o.w || h != o.h || l != o.l;
	}

	inline box3 operator + (const box3 o) const {
		return box3(x + o.x, y + o.y, z + o.z, w + o.w, h + o.h, l + o.l);
	}
	inline box3 operator + (const vector3 o) const {
		return box3(x + o.x, y + o.y, z + o.z, w, h, l);
	}
	inline void operator += (const box3 o) {
		x += o.x;
		y += o.y;
		z += o.z;
		w += o.w;
		h += o.h;
		l += o.l;
	}
	inline void operator += (const vector3 o) {
		x += o.x;
		y += o.y;
		z += o.z;
	}
	inline box3 operator - (const box3 o) const {
		return box3(x - o.x, y - o.y, z - o.z, w - o.w, h - o.h, l - o.l);
	}
	inline box3 operator - (const vector3 o) const {
		return box3(x - o.x, y - o.y, z - o.z, w, h, l);
	}
	inline void operator -= (const box3 o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
		w -= o.w;
		h -= o.h;
		l -= o.l;
	}
	inline void operator -= (const vector3 o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
	}
	inline box3 operator * (const box3 o) const {
		return box3(x * o.x, y * o.y, z * o.z, w * o.w, h * o.h, l * o.l);
	}
	inline box3 operator * (const vector3 o) const {
		return box3(x * o.x, y * o.y, z * o.z, w, h, l);
	}
	inline void operator *= (const box3 o) {
		x *= o.x;
		y *= o.y;
		z *= o.z;
		w *= o.w;
		h *= o.h;
		l *= o.l;
	}
	inline void operator *= (const vector3 o) {
		x *= o.x;
		y *= o.y;
		z *= o.z;
	}
	inline box3 operator / (const box3 o) const {
		return box3(x / o.x, y / o.y, z / o.z, w / o.w, h / o.h, l / o.l);
	}
	inline box3 operator / (const vector3 o) const {
		return box3(x / o.x, y / o.y, z / o.z, w, h, l);
	}
	inline void operator /= (const box3 o) {
		x /= o.x;
		y /= o.y;
		z /= o.z;
		w /= o.w;
		h /= o.h;
		l /= o.l;
	}
	inline void operator /= (const vector3 o) {
		x /= o.x;
		y /= o.y;
		z /= o.z;
	}
};

struct sphere3d {
	float x, y, z;
	float r;

	inline sphere3d(const float dx, const float dy, const float dz, const float dr) : x{ dx }, y{ dy }, z{ dz }, r{ dr } {};
	inline sphere3d(const vector3 pos, const float dr) : sphere3d(pos.x, pos.y, pos.z, dr) {};

	inline vector3 center() const {
		return vector3(x, y, z);
	}

	inline bool operator == (const sphere3d o) const {
		return x == o.x && y == o.y && z == o.z && r == o.r;
	}
	inline bool operator != (const sphere3d o) const {
		return x != o.x || y != o.y || z != o.z || r != o.r;
	}

	inline sphere3d operator + (const sphere3d o) const {
		return sphere3d(x + o.x, y + o.y, z + o.z, r + o.r);
	}
	inline sphere3d operator + (const vector3 o) const {
		return sphere3d(x + o.x, y + o.y, z + o.z, r);
	}
	inline sphere3d operator + (const float o) const {
		return sphere3d(x, y, z, r + o);
	}
	inline void operator += (const sphere3d o) {
		x += o.x;
		y += o.y;
		z += o.z;
		r += o.r;
	}
	inline void operator += (const vector3 o) {
		x += o.x;
		y += o.y;
		z += o.z;
	}
	inline void operator += (const float o) {
		r += o;
	}

	inline sphere3d operator - (const sphere3d o) const {
		return sphere3d(x - o.x, y - o.y, z - o.z, r - o.r);
	}
	inline sphere3d operator - (const vector3 o) const {
		return sphere3d(x - o.x, y - o.y, z - o.z, r);
	}
	inline sphere3d operator - (const float o) const {
		return sphere3d(x, y, z, r - o);
	}
	inline void operator -= (const sphere3d o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
		r -= o.r;
	}
	inline void operator -= (const vector3 o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
	}
	inline void operator -= (const float o) {
		r -= o;
	}

	inline sphere3d operator * (const sphere3d o) const {
		return sphere3d(x * o.x, y * o.y, z * o.z, r * o.r);
	}
	inline sphere3d operator * (const vector3 o) const {
		return sphere3d(x * o.x, y * o.y, z * o.z, r);
	}
	inline sphere3d operator * (const float o) const {
		return sphere3d(x, y, z, r * o);
	}
	inline void operator *= (const sphere3d o) {
		x *= o.x;
		y *= o.y;
		z *= o.z;
		r *= o.r;
	}
	inline void operator *= (const vector3 o) {
		x *= o.x;
		y *= o.y;
		z *= o.z;
	}
	inline void operator *= (const float o) {
		r *= o;
	}

	inline sphere3d operator / (const sphere3d o) const {
		return sphere3d(x / o.x, y / o.y, z / o.z, r / o.r);
	}
	inline sphere3d operator / (const vector3 o) const {
		return sphere3d(x / o.x, y / o.y, z / o.z, r);
	}
	inline sphere3d operator / (const float o) const {
		return sphere3d(x, y, z, r / o);
	}
	inline void operator /= (const sphere3d o) {
		x /= o.x;
		y /= o.y;
		z /= o.z;
		r /= o.r;
	}
	inline void operator /= (const vector3 o) {
		x /= o.x;
		y /= o.y;
		z /= o.z;
	}
	inline void operator /= (const float o) {
		r /= o;
	}
};

inline std::ostream& operator << (std::ostream& cout, const box3 o) {
	return cout << "{ x: " << o.x << ", y: " << o.y << ", z: " << o.z << ", w: " << o.w << ", h: " << o.h << ", l: " << o.l << " }";
}

struct raycbox {
	bool collision;
	box3 box;
	float distance;
	vector3 position;
};
struct raycsphere {
	bool collision;
	sphere3d sphere;
	float distance;
	vector3 position;
};

struct ray {
	vector3 position;
	vector3 direction;

	inline ray(vector3 pos, vector3 dir) : position{ pos }, direction{ +dir } {};
	inline ray(vector3 dir) : ray(vector3(0, 0, 0), dir) {};
	inline ray() : ray(vector3(1, 0, 0)) {};
	inline ray(Ray r) : ray(r.position, r.direction) {};

	inline operator Ray() const {
		return { position, direction };
	}
	inline raycbox collisionBox(const box3 b) const {
		auto a = GetRayCollisionBox(*this, b);
		return { a.hit, b, a.distance, a.point };
	}
	inline raycsphere collisionSphere(const sphere3d b) const {
		auto a = GetRayCollisionSphere(*this, b.center(), b.r);
		return { a.hit, b, a.distance, a.point };
	}
};

struct camera3d {
	vector3 position;
	vector3 target;
	vector3 up;
	CameraProjection projection;
	float fovy;

	inline camera3d(vector3 dposition, vector3 dtarget, float dfovy, CameraProjection dprojection, vector3 dup) : position{ dposition }, target{ dtarget }, fovy{ dfovy }, projection{ dprojection }, up{ dup } {};
	inline camera3d(vector3 dposition, vector3 dtarget) : camera3d(dposition, dtarget, 60, CAMERA_PERSPECTIVE, vector3(0, 1, 0)) {};
	inline camera3d(vector3 dposition) : camera3d(dposition, vector3(0, 0, 0), 60, CAMERA_PERSPECTIVE, vector3(0, 1, 0)) {};
	inline camera3d(Camera3D cam) : camera3d(cam.position, cam.target, cam.fovy, (CameraProjection)cam.projection, cam.up) {};

	inline operator Camera3D() const {
		return Camera3D{ position, target, up, fovy, projection };
	}

	inline void begin() const {
		BeginMode3D(*this);
	}

	inline void end() const {
		EndMode3D();
	}

	// while cursor is visible
	inline ray mouse_ray() const {
		return GetMouseRay(GetMousePosition(), *this);
	}
	inline ray camera_ray() const {
		return ray(position, target - position);
	}

	void update();
	void updatepro(vector3 position, vector3 direction, float zoom);
};

namespace draw {
	inline void box_center(const float x, const float y, const float z, const float width, const float height, const float length, const color dcolor) {
		DrawCube({ x, y, z }, width, height, length, dcolor);
	}
	inline void box_center(const vector3 position, const float width, const float height, const float length, const color dcolor) {
		DrawCube(position, width, height, length, dcolor);
	}
	inline void box_center(const float x, const float y, const float z, const vector3 size, const color dcolor) {
		DrawCube({ x, y, z }, size.x, size.y, size.z, dcolor);
	}
	inline void box_center(const vector3 position, const vector3 size, const color dcolor) {
		DrawCube(position, size.x, size.y, size.z, dcolor);
	}
	inline void box_center(const box3 b, const color dcolor) {
		DrawCube({ b.x, b.y, b.z }, b.w, b.h, b.l, dcolor);
	}

	inline void box(const float x, const float y, const float z, const float w, const float h, const float l, const color dcolor) {
		box_center(x - w / 2, y - h / 2, z - l / 2, w, h, l, dcolor);
	}
	inline void box(const vector3 position, const float w, const float h, const float l, const color dcolor) {
		box_center(position.x - w / 2, position.y - h / 2, position.z - l / 2, w, h, l, dcolor);
	}
	inline void box(const float x, const float y, const float z, const vector3 size, const color dcolor) {
		box_center(x - size.x / 2, y - size.y / 2, z - size.z / 2, size, dcolor);
	}
	inline void box(const vector3 position, const vector3 size, const color dcolor) {
		box_center(position.x - size.x / 2, position.y - size.y / 2, position.z - size.z / 2, size, dcolor);
	}
	inline void box(const box3 b, const color dcolor) {
		box_center(b.x + b.w / 2, b.y + b.h / 2, b.z + b.l / 2, b.w, b.h, b.l, dcolor);
	}

	inline void sphere_center(const vector3 center, const float radius, const color dcolor) {
		DrawSphere(center, radius, dcolor);
	}
	inline void sphere_center(const sphere3d dsphere, const color dcolor) {
		sphere_center(dsphere.center(), dsphere.r, dcolor);
	}
	inline void sphere_center(const float x, const float y, const float z, const float radius, const color dcolor) {
		sphere_center(vector3(x, y, z), radius, dcolor);
	}

	inline void sphere(const vector3 center, const float radius, const color dcolor) {
		DrawSphere(center + radius/2, radius, dcolor);
	}
	inline void sphere(const sphere3d dsphere, const color dcolor) {
		sphere(dsphere.center(), dsphere.r, dcolor);
	}
	inline void sphere(const float x, const float y, const float z, const float radius, const color dcolor) {
		sphere(vector3(x, y, z), radius, dcolor);
	}

	inline void ray(const ::ray dray, const color dcolor) {
		DrawRay(dray, dcolor);
	}
	inline void ray(const vector3 position, const vector3 direction, const color dcolor) {
		ray(::ray(position, direction), dcolor);
	}

	inline void billboard(const vector3 position, const camera3d camera, const size_t dtexture, const float size, const color dcolor = colors::white) {
		DrawBillboard(camera, textures[dtexture], position, size, dcolor);
	}
	inline void billboard(const vector3 position, const camera3d camera, const atexture dtexture, const vector2 size, const color dcolor = colors::white) {
		DrawBillboardRec(camera, textures[dtexture], (const rect2)dtexture, position, size, dcolor);
	}
	inline void billboard(const vector3 position, const camera3d camera, const atexture dtexture, const vector2 size, const float rotation, const vector2 origin = 0, const color dcolor = colors::white) {
		DrawBillboardPro(camera, textures[dtexture], (const rect2)dtexture, position, (vector3)0, size, origin, rotation, dcolor);
	}
}