#include "Camera.h"



Camera::Camera(Entity &entity) :
	Component(entity),
	m_fieldOfView(90)
{
}

void Camera::Update(World &world)
{

}

void Camera::FixedUpdate(World &world)
{

}

Camera::~Camera()
{
}
