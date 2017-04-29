#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>

Camera::Camera()
{
	SetPerspective(1.0f, 1000.0f, 60.0f, 4.0f / 3.0f);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

glm::mat4 Camera::GetViewProjection()
{
	return _projectionMatrix * _viewMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return _viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
	return _transformTerrain.GetPosition();
}

void Camera::SetPosition(float x, float y, float z)
{
	_transformTerrain.SetPosition(x, y, z);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::SetPosition(glm::vec3 position)
{
	_transformTerrain.SetPosition(position);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::SetRotation(float x, float y, float z)
{
	_transformTerrain.SetRotation(x, y, z);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

glm::quat Camera::GetRotation()
{
	return _transformTerrain.GetRotation();
}

void Camera::SetRotation(glm::vec3 rotation)
{
	_transformTerrain.SetRotation(rotation);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::MoveForward(float delta, bool world)
{
	_transformTerrain.MoveForward(delta, world);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::MoveUp(float delta, bool world)
{
	_transformTerrain.MoveUp(delta, world);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::MoveRight(float delta, bool world)
{
	_transformTerrain.MoveRight(delta, world);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::Yaw(float degrees)
{
	_transformTerrain.Rotate(0.0f, degrees, 0.0f, false);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::Pitch(float degrees)
{
	_transformTerrain.Rotate(degrees, 0.0f, 0.0f, false);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::Roll(float degrees)
{
	_transformTerrain.Rotate(0.0f, 0.0f, degrees, false);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::Rotate(float x, float y, float z, bool world)
{
	_transformTerrain.Rotate(x, y, z, world);
	_viewMatrix = glm::inverse(_transformTerrain.GetModelMatrix());
}

void Camera::SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio)
{
	_projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::SetOrthographic(float size, float aspectRatio)
{
	float xSize = aspectRatio * size;
	_projectionMatrix = glm::ortho(-xSize, xSize, -size, size, -size, size);
}