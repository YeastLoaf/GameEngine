#pragma once

#include <cmath>
#include <cassert>

namespace nu {
	struct Vector2 {
		float x, y, z;

		Vector2() = default;
		Vector2(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector2(float v) : x{ v }, y{ v }, z{ v } {}

		float  operator [] (unsigned int i) const { assert(i < 2); return (&x)[i]; }
		float& operator [] (unsigned int i) { assert(i < 2); return (&x)[i]; }

		bool operator == (const Vector2& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z); }
		bool operator != (const Vector2& v) const { return (this->x != v.x || this->y != v.y || this->z != v.z); }

		Vector2 operator + (const Vector2& v) const { return Vector2{ this->x + v.x, this->y + v.y, this->z + v.z }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ this->x - v.x, this->y - v.y, this->z - v.z }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ this->x * v.x, this->y * v.y, this->z * v.z }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ this->x / v.x, this->y / v.y, this->z / v.z }; }

		Vector2 operator + (float v) const { return Vector2{ this->x + v, this->y + v, this->z + v }; }
		Vector2 operator - (float v) const { return Vector2{ this->x - v, this->y - v, this->z - v }; }
		Vector2 operator * (float v) const { return Vector2{ this->x * v, this->y * v, this->z * v }; }
		Vector2 operator / (float v) const { return Vector2{ this->x / v, this->y / v, this->z / v }; }

		Vector2& operator += (const Vector2& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
		Vector2& operator -= (const Vector2& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
		Vector2& operator *= (const Vector2& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return *this; }
		Vector2& operator /= (const Vector2& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return *this; }

		Vector2& operator += (float v) { this->x += v; this->y += v; this->z += v; return *this; }
		Vector2& operator -= (float v) { this->x -= v; this->y -= v; this->z -= v; return *this; }
		Vector2& operator *= (float v) { this->x *= v; this->y *= v; this->z *= v; return *this; }
		Vector2& operator /= (float v) { this->x /= v; this->y /= v; this->z /= v; return *this; }

		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		float Length() const { return std::sqrt(LengthSqr()); }
		Vector2 Normalize() const { return (*this) / Length(); }
		float Dot(const Vector2& v) const { return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); }
	};
}