#include "mspch.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mystic/Core/Timestep.h"

namespace Mystic {

	Camera2D::Camera2D(float left, float right, float bottom, float top)
		: _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
	{
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}

	void Camera2D::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, _position);
		transform = glm::rotate(transform, glm::radians(_rotation), glm::vec3(0, 0, 1));

		_viewMatrix = glm::inverse(transform);
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}
	

	Camera::Camera()
	{
		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));

		_moveFront = _front;
		_moveRight = _right;

		_viewMatrix = glm::lookAt(_currentPosition, _target, _up);
		_projectionMatrix = glm::perspective(_fov, _aspect, _near, _far);
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}

	void Camera::Update(float ts)
	{	
		float blend = 1.0f - glm::pow(0.1f, ts);
		blend += _smoothing;
		blend = glm::min(blend, 1.0f);

		//Interpolation for Smooth Camera Movement
		_currentPosition = interpolateVec3(_currentPosition, _desiredPosition, blend);
		_currentPitch = glm::mix(_currentPitch, _desiredPitch, blend);
		_currentYaw = glm::mix(_currentYaw, _desiredYaw, blend);

		//Limit Pitch
		if (_currentPitch > 89.0f)
		{
			_currentPitch = 89.0f;
			_desiredPitch = 89.0f;
		}
		if (_currentPitch < -89.0f)
		{
			_currentPitch = -89.0f;
			_desiredPitch = -89.0f;
		}

		//Calculate Forward
		glm::vec3 front;
		front.x = cos(glm::radians(_currentYaw - 90.0f)) * cos(glm::radians(_currentPitch));
		front.y = sin(glm::radians(_currentPitch));
		front.z = sin(glm::radians(_currentYaw - 90.0f)) * cos(glm::radians(_currentPitch));

		_front = glm::normalize(front);
		_moveFront.x = _front.x;
		_moveFront.z = _front.z;
		_moveFront = glm::normalize(_moveFront);

		//Calculate Right and Up Vectors
		//normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		_right = glm::normalize(glm::cross(_front, _worldUp));  
		_up = glm::normalize(glm::cross(_right, _front));

		_moveRight.x = _right.x;
		_moveRight.z = _right.z;
		_moveRight = glm::normalize(_moveRight);

		if (!_setTarget)
		{
			_target = _currentPosition + _front;
		}
		_setTarget = false;

		_viewMatrix = glm::lookAt(_currentPosition, _target, _up);
		_projectionMatrix = glm::perspective(_fov, _aspect, _near, _far);
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		_desiredPosition = position;
	}

	glm::vec3 Camera::GetPosition()
	{
		return _currentPosition;
	}

	void Camera::SetYawPitchRoll(const glm::vec3& yawPitchRoll)
	{
		_desiredYaw = yawPitchRoll.x;
		_desiredPitch = yawPitchRoll.y;
		_roll = yawPitchRoll.z;
	}

	void Camera::AddYawPitchRoll(const glm::vec3& yawPitchRoll)
	{
		_desiredYaw += yawPitchRoll.x;
		_desiredPitch += yawPitchRoll.y;
		_roll += yawPitchRoll.z;
	}

	void Camera::SetForwardUpRight(const glm::vec3& front, const glm::vec3& up, const glm::vec3& right)
	{
		_front = front;
		_up = up;
		_right = right;
	}

	void Camera::SetTarget(const glm::vec3& target)
	{
		_target = target;
		_setTarget = true;
	}

	void Camera::MoveForward(float speed)
	{
		_desiredPosition += _moveFront * speed;
	}

	void Camera::MoveBackward(float speed)
	{
		_desiredPosition -= _moveFront * speed;
	}

	void Camera::MoveUp(float speed)
	{
		_desiredPosition += _worldUp * speed;
	}

	void Camera::MoveDown(float speed)
	{
		_desiredPosition -= _worldUp * speed;
	}

	void Camera::MoveRight(float speed)
	{
		_desiredPosition += _moveRight * speed;
	}

	void Camera::MoveLeft(float speed)
	{
		_desiredPosition -= _moveRight * speed;
	}

	void Camera::SetSmoothing(float amount)
	{
		_smoothing = amount;
	}

	void Camera::SetFOV(float fov)
	{
		_fov = fov;
	}

	void Camera::SetNear(float near_)
	{
		_near = near_;
	}

	void Camera::SetFar(float far_)
	{
		_far = far_;
	}

	void Camera::SetAspect(float aspect)
	{
		_aspect = aspect;
	}

	glm::vec3 Camera::interpolateVec3(glm::vec3 currentVector, glm::vec3 desiredVector, float factor)
	{
		return glm::vec3(glm::mix(currentVector.x, desiredVector.x, factor), glm::mix(currentVector.y, desiredVector.y, factor), glm::mix(currentVector.z, desiredVector.z, factor));
	}

}