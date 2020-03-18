#pragma once
#include "./Object.h"
#include <string>

class Light : public Object
{
	protected:

		std::string m_type;
		Vec3f m_albedo;
		float m_intensity;
		float m_ambientConst;
		float m_diffuseConst;
		float m_speculatConst;

	public:
		Light() {};
		~Light() {};

		Light(Vec3f albedo) 
		{ 
			m_type = "Light";
			m_albedo = albedo; 
			m_intensity = 1.0; 
			m_ambientConst = 0.1f;
			m_diffuseConst = 0.8f;	
			m_speculatConst = 0.8f;
		}
		Light(Vec3f albedo, float intensity) 
		{ 
			m_type = "Light";
			m_albedo = albedo; 
			m_intensity = intensity; 
			m_ambientConst = 0.1f; 
			m_diffuseConst = 0.8f;
			m_speculatConst = 0.8f; 
		}
		
		Light(Vec3f albedo, float intensity, float ambientConst, float diffuseConst, float specularConst) 
		{ 
			m_type = "Light";
			m_albedo = albedo; 
			m_intensity = intensity; 
			m_ambientConst = ambientConst;
			m_diffuseConst = diffuseConst;
			m_speculatConst = specularConst; 
		}

		virtual Vec3f generateShadowRayDir(Vec3f hitPoint) { return Vec3f(0.0f, 0.0f, 0.0f); }

		void setAlbedo(Vec3f albedo) { m_albedo = albedo; }
		void setIntensity(float intensity) { m_intensity = intensity; }
		void setAmbientConst(float ambientConst) { m_ambientConst = ambientConst; }
		void setDiffuseConst(float diffuseConst) { m_diffuseConst = diffuseConst; }
		void setSpecularConst(float speculatConst) { m_speculatConst = speculatConst; }

		std::string getType() { return m_type; }
		Vec3f getAlbedo() { return m_albedo; }
		float getIntensity() { return m_intensity; }
		float getAmbientConst() { return m_ambientConst; }
		float getDiffuseConst() { return m_diffuseConst; }
		float getSpecularConst() { return m_speculatConst; }

};