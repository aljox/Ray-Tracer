#pragma once
#include "./Light.h"

class DirectionalLight : public Light
{	
	public:
		DirectionalLight() {}
		~DirectionalLight() {}
		DirectionalLight(Vec3f direction, Vec3f albedo, float intensity)
		{	
			m_type = "DirectionalLight";
			direction.makeUnitVector();
			m_position = direction;

			m_albedo = albedo;
			m_intensity = intensity;
			m_ambientConst = 0.1f; 
			m_diffuseConst = 0.8f, 
			m_speculatConst = 0.8;
		}

		DirectionalLight(Vec3f direction, Vec3f albedo, float intensity, float ambientConst, float diffuseConst, float specularConst)
		{	
			m_type = "DirectionalLight";
			direction.makeUnitVector();
			m_position = direction;

			m_albedo = albedo;
			m_intensity = intensity;
			m_ambientConst = ambientConst;
			m_diffuseConst = diffuseConst,
			m_speculatConst = specularConst;
		}

		Vec3f generateShadowRayDir(Vec3f hitPoint) { return unitVector(-1.0f * m_position); }

		void setDirection(Vec3f direction) { m_position = direction; }
		Vec3f getDirection() { return m_position; }

};