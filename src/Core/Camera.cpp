#include "./Camera.h"

Camera::Camera() { m_up = Vec3f(0.0f, 1.0f, 0.0f); }
Camera::~Camera() {}

// FOV is vertical in degrees
// Canvas is on -1 z axis!
Camera::Camera(Vec3f lookFrom, Vec3f lookAt, float fov, float aspect) 
{	
	Vec3f u, v, w;
	m_up = Vec3f(0.0f, 1.0f, 0.0f);

	// Convert to radians
	float theta = fov * 3.14f / 180.0f;

	float halfHeight = tan(theta / 2.0f);
	float halfWidth = aspect * halfHeight;

	// Create camera ortogonal basis
	m_origin = lookFrom;
	w = unitVector(lookFrom - lookAt);
	u = unitVector(cross(m_up, w));
	v = unitVector(cross(w, u));
	
	// Transform local lower left corner (-halfWidth, -halfHeight, -1.0f) into world lower left
	m_lowerLeftCorner = m_origin - halfWidth * u - halfHeight * v - w;
	m_horizontal = 2.0f * halfWidth * u;
	m_vertical = 2.0f * halfHeight * v;
}

Ray Camera::getRay(float s, float t)
{
	return Ray(m_origin, m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin);
}