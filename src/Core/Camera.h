#pragma once

#include "../Math/Ray.h"
#include <cmath> 

class Camera
{
	private:
		Vec3f m_up;

		Vec3f m_lowerLeftCorner;
		Vec3f m_horizontal;
		Vec3f m_vertical;
		Vec3f m_origin;

	public:
		Camera();
		~Camera();
		Camera(Vec3f lookFrom, Vec3f lookAt, float fov, float aspect);

		Ray getRay(float s, float t);
};