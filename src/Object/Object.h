#pragma once
#include "../Math/Vec3f.h"

class Object 
{
	protected:
		Vec3f m_position;
		Vec3f m_translation;
		Vec3f m_rotation;
	
	public:
		Object();
		~Object();
		Object(Vec3f position);

		// TODO: model matrix cration and update

		void setPosition(Vec3f position);
		void setTranslation(Vec3f translation);
		void setRotation(Vec3f rotation);

		void translateX(float tran);
		void translateY(float tran);
		void translateZ(float tran);
		void rotateX(float rot);
		void rotateY(float rot);
		void rotateZ(float rot);

		Vec3f getPosition();
		Vec3f getTranslation();
		Vec3f getRotation();
};