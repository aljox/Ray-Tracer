#include "./Object.h"

Object::Object() 
{ 
	Vec3f m_position(0.0, 0.0, 0.0);
	Vec3f m_translation(0.0, 0.0, 0.0);
	Vec3f m_rotation(0.0, 0.0, 0.0);
}
Object::~Object() {}

Object::Object(Vec3f position) 
{
	m_position = position;
	Vec3f m_translation(0.0, 0.0, 0.0);
	Vec3f m_rotation(0.0, 0.0, 0.0);
}

void Object::setPosition(Vec3f position) { m_position = position; }
void Object::setTranslation(Vec3f translation) { m_translation = translation; }
void Object::setRotation(Vec3f rotation) { m_rotation = rotation; }

void Object::translateX(float tran) { m_translation.e[0] += tran; }
void Object::translateY(float tran) { m_translation.e[1] += tran; }
void Object::translateZ(float tran) { m_translation.e[2] += tran; }
void Object::rotateX(float rot) { m_rotation.e[0] += rot; }
void Object::rotateY(float rot) { m_rotation.e[1] += rot; }
void Object::rotateZ(float rot) { m_rotation.e[2] += rot; }

Vec3f Object::getPosition() { return m_position; }
Vec3f Object::getTranslation() { return m_translation; }
Vec3f Object::getRotation() { return m_rotation; }