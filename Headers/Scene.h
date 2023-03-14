#pragma once
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include "Object.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
class Scene
{
	public:
		std::vector<Object> SceneObject;
		std::vector<glm::vec3> Grid;
		glm::mat4 Perspective;
		glm::mat4 Camera;

		Scene(float width, float height);
		~Scene();

		glm::mat4 GetMvp();
		int AddObjectToScene(Object& object);
		void RemoveObjectToScene(int index);
		sf::VertexArray ProjectObjects(DrawMode mode, sf::Color color);
		std::vector<sf::Text> ProjectObjectsVertexIndex(sf::Color color, const sf::Font& font);
		sf::VertexArray GetGrid();

		void SetFov(float fov);
		void ScaleFov(float deltaFov);

		void SetRatio(float ratio);
		void ScaleRatio(float deltaratio);

		void SetNear(float near);
		void ScaleNear(float deltaNear);

		void SetFar(float far);
		void ScaleFar(float deltaFar);

		void SetCameraPos(glm::vec3 cameraPos);
		void MoveCameraPos(glm::vec3 deltaCameraPos);


		void SetCameraTarget(glm::vec3 cameraTarget);
		void MoveCameraTarget(glm::vec3 deltaCameraTarget);


		void SetCameraUp(glm::vec3 cameraUp);
		void MoveCameraUp(glm::vec3 deltaCameraUp);

		void OrbitCamera(float deltaX, float deltaY);
		void DistanceCamera(float deltaDistance);
	private:
		float radians;
		float ratio;
		float near;
		float far;

		void UpdatePerspective();
		void UpdateCamera();

		glm::vec3 cameraPos;
		glm::vec3 cameraTarget;
		glm::vec3 cameraUp;
};