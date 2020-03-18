#pragma once
#include "./Light.h"

class PointLight : public Light
{
	private:
		// Attenuation coficients
		float m_attenC1;
		float m_attenC2;
	public:
		PointLight();
		~PointLight();

		PointLight(Vec3f albedo, Vec3f position, float intensity) 
		{ 
			m_type = "PointLight";
			m_albedo = albedo;  
			m_position = position; 
			m_intensity = intensity; 
			m_ambientConst = 0.2f;
			m_diffuseConst = 0.8f;
			m_speculatConst = 0.8f;
			//m_attenC1 = 1.0; 
			//m_attenC2 = 1.0; 
		}

		PointLight(Vec3f albedo, Vec3f position, float intensity, float attenC1, float attenC2)
		{
			m_type = "PointLight";
			m_albedo = albedo;
			m_position = position;
			m_intensity = intensity;
			m_ambientConst = 0.2f;
			m_diffuseConst = 0.8f;
			m_speculatConst = 0.8f;
			//m_attenC1 = attenC1;
			//m_attenC2 = attenC2;
		}

		PointLight(Vec3f albedo, Vec3f position, float intensity, float ambinetConst, float diffuseConst, float speculatConst, float attenC1, float attenC2)
		{
			m_type = "PointLight";
			m_albedo = albedo;
			m_position = position;
			m_intensity = intensity;
			m_ambientConst = ambinetConst;
			m_diffuseConst = diffuseConst;
			m_speculatConst = speculatConst;
			//m_attenC1 = attenC1;
			//m_attenC2 = attenC2;
		}

		Vec3f generateShadowRayDir(Vec3f hitPoint) { return unitVector(m_position - hitPoint); }

		//void setAttenC1(float attenC1) { m_attenC1 = attenC1; }
		//void setAttenC2(float attenC2) { m_attenC2 = attenC2; }

		//float getAttenC1() { return m_attenC1; }
		//float getAttenC2() { return m_attenC2; }
};