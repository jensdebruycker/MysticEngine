#pragma once

#include "glm/glm.hpp"

namespace Mystic {

	class Camera2D
	{
	public:
		Camera2D(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return _position; }
		void SetPosition(const glm::vec3& position) { _position = position; RecalculateViewMatrix(); }

		const float& GetRotation() const { return _rotation; }
		void SetRotation(const float& rotation) { _rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		glm::mat4 _viewProjectionMatrix;

		glm::vec3 _position = {0.0f, 0.0f, 0.0f};
		float _rotation = 0;
	};

	class Camera
	{
	public:
		Camera();

		void Update(float ts);

		//Position of camera
		void SetPosition(const glm::vec3& position);
		glm::vec3 GetPosition();

		//Set Rotations
		void SetYawPitchRoll(const glm::vec3& yawPitchRoll);
		void AddYawPitchRoll(const glm::vec3& yawPitchRoll);
		void SetForwardUpRight(const glm::vec3& front, const glm::vec3& up, const glm::vec3& right);
		//Look At
		void SetTarget(const glm::vec3& target);

		//Movement
		void MoveForward(float speed);
		void MoveBackward(float speed);
		void MoveUp(float speed);
		void MoveDown(float speed);
		void MoveRight(float speed);
		void MoveLeft(float speed);

		void SetSmoothing(float amount);

		void SetFOV(float fov);
		void SetNear(float near_);
		void SetFar(float far_);

		void SetAspect(float aspect);

		const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }
	private:
		glm::vec3 interpolateVec3(glm::vec3 vector, glm::vec3 desiredVector, float factor);
	private:
		//Rotation with vectors
		glm::vec3 _front = { 0.0f, 0.0f, 1.0f };
		glm::vec3 _up;
		glm::vec3 _right;

		glm::vec3 _moveFront;
		glm::vec3 _moveRight;

		glm::vec3 _worldUp = { 0.0f, 1.0f, 0.0f };

		//Rotation in radians
		float _currentYaw = 0.0f;
		float _currentPitch = 0.0f;
		float _roll = 0.0f;

		glm::vec3 _target = { 0.0f, 0.0f, 0.0f };
		bool _setTarget = false;

		glm::vec3 _currentPosition = { 0.0f, 0.0f, 1.0f };

		//Vertical field of view in radians
		float _fov = 45.0f;

		//Clipping distances
		float _near = 0.01f;
		float _far = 10.0f;

		// Width/Heigth
		float _aspect = 16.0f/9.0f;

		//Smoothing vars
		float _smoothing = 0.1f;
		float _desiredYaw = 0.0f;
		float _desiredPitch = 0.0f;
		glm::vec3 _desiredPosition = { 0.0f, 0.0f, 1.0f };

		//Matricies
		glm::mat4 _viewMatrix = glm::mat4(0.0f);
		glm::mat4 _projectionMatrix = glm::mat4(0.0f);
		glm::mat4 _viewProjectionMatrix;
	};

}