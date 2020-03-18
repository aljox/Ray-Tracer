#pragma once

class Vec2f
{
	public:
		float e[2];

		Vec2f() {}
		~Vec2f() {}
		Vec2f(float x, float y) { e[0] = x; e[1] = y; }

		inline float x() const { return e[0]; }
		inline float y() const { return e[1]; }
};