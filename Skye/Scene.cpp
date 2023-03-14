#include "Headers/Scene.h"

Scene::Scene(float width, float height)
{
	cameraPos = glm::vec3(0.0f, 0, 10.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, -1.0f, 0.0f);

	radians = 45.f;
	ratio = 1;
	near = 0.1f;
	far = 800.f;

	this->Grid = std::vector<glm::vec3>();
	this->SceneObject = std::vector<Object>();
	this->Camera = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	this->Perspective = glm::perspective(glm::radians(radians), ratio, near, far);
}

Scene::~Scene()
{
}

glm::mat4 Scene::GetMvp()
{
	return Perspective * Camera * glm::mat4(1.0f);
}

int Scene::AddObjectToScene(Object& object)
{
	this->SceneObject.push_back(object);
	return 0;
}

sf::VertexArray Scene::ProjectObjects(DrawMode mode, sf::Color color)
{
	sf::VertexArray result(
		mode == point? sf::PrimitiveType::Points :
		mode == edge? sf::PrimitiveType::Lines :
		mode == plane? sf::PrimitiveType::Triangles : sf::PrimitiveType::Points);
	for (auto ob : SceneObject) for (const auto ver : ob.ProjectObject(GetMvp(), color, mode)) result.append(ver);
	return result;
}

std::vector<sf::Text> Scene::ProjectObjectsVertexIndex(sf::Color color, const sf::Font& font)
{
	std::vector<sf::Text> result = std::vector<sf::Text>();
	for (auto ob : SceneObject) for (const auto ver : ob.GetVertexIndixes(GetMvp(), cameraPos, radians, color, font)) result.push_back(ver);
	return result;
}

sf::VertexArray Scene::GetGrid()
{
	sf::VertexArray result(sf::Lines);
	glm::mat4 modelMatrix(1.0f);
	if (Grid.size() == 0)
	{
		for (float i = -80; i < 80; i += 10)
		{
			for (float f = -80; f < 80; f += 10)
			{
				Grid.push_back(glm::vec3(i, 0, f));
				Grid.push_back(glm::vec3(i, 0, -f));
				Grid.push_back(glm::vec3(i, 0, f));
				Grid.push_back(glm::vec3(-i, 0, f));
				Grid.push_back(glm::vec3(i, 0, f));
			}
		}
	}
	for (auto ver : Grid)
	{
		auto point = GetMvp() * glm::vec4(ver, 1.f);
		result.append(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color(50, 50, 50)));
	}
	return result;
}

void Scene::SetFov(float newfov)
{
	radians = newfov;
	this->UpdatePerspective();
}

void Scene::ScaleFov(float deltaFov)
{
	radians += deltaFov;
	this->UpdatePerspective();
}

void Scene::SetRatio(float newratio)
{
	ratio = newratio;
	this->UpdatePerspective();
}

void Scene::ScaleRatio(float deltaratio)
{
	ratio += deltaratio;
	this->UpdatePerspective();
}

void Scene::SetNear(float newNear)
{
	near = newNear;
	this->UpdatePerspective();
}

void Scene::ScaleNear(float deltaNear)
{
	near += deltaNear;
	this->UpdatePerspective();
}

void Scene::SetFar(float newfar)
{
	far = newfar;
	this->UpdatePerspective();
}

void Scene::ScaleFar(float deltaFar)
{
	far += deltaFar;
	this->UpdatePerspective();
}

void Scene::SetCameraPos(glm::vec3 newcameraPos)
{
	cameraPos = newcameraPos;
	cameraTarget = newcameraPos + glm::vec3(0,0,10);
	UpdateCamera();
}

void Scene::MoveCameraPos(glm::vec3 deltaCameraPos)
{
	cameraPos += deltaCameraPos;
	cameraTarget += deltaCameraPos;
	UpdateCamera();
}

void Scene::SetCameraTarget(glm::vec3 newcameraTarget)
{
	cameraTarget = newcameraTarget;
	UpdateCamera();
}

void Scene::MoveCameraTarget(glm::vec3 deltaCameraTarget)
{
	cameraTarget += deltaCameraTarget;
	UpdateCamera();
}

void Scene::SetCameraUp(glm::vec3 newcameraUp)
{
	cameraUp = newcameraUp;
	UpdateCamera();
}

void Scene::MoveCameraUp(glm::vec3 deltaCameraUp)
{
	cameraUp += deltaCameraUp;
	UpdateCamera();
}



void Scene::OrbitCamera(float deltaX, float deltaY)
{
	glm::vec3 direction = glm::normalize(cameraTarget - cameraPos);
	//// Calculate the right vector
	//glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));

	//// Calculate the up vector
	//glm::vec3 up = glm::cross(right, direction);

	// Calculate the rotation quaternion based on the deltaX and deltaY values
	glm::quat rotX = glm::angleAxis(deltaX, glm::vec3(1, 0, 0));
	glm::quat rotY = glm::angleAxis(deltaY, glm::vec3(0, 1, 0));

	// Rotate the direction vector by the rotation quaternion
	direction = glm::rotate(rotX * rotY, -direction);

	// Update the current position based on the rotated direction vector and the deltaDistance value
	cameraPos = cameraTarget + direction;

	UpdateCamera();
}

void Scene::DistanceCamera(float deltaDistance)
{
	float distance = glm::distance(cameraPos, cameraTarget);
	glm::vec3 direction = glm::normalize(cameraTarget - cameraPos);
	glm::vec3 offset = direction * (distance + deltaDistance);

	cameraPos += offset;
	UpdateCamera();
}

void Scene::UpdatePerspective()
{
	this->Perspective = glm::perspective(glm::radians(radians), ratio, near, far);
}

void Scene::UpdateCamera()
{
	this->Camera = glm::lookAt(cameraPos, cameraTarget, cameraUp);
}
