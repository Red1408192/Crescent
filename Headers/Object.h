#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <glm/gtc/quaternion.hpp>


struct Edge
{
	Edge(glm::vec3* point1, glm::vec3* point2)
	{
		Point1Index = point1;
		Point2Index = point2;
	}
	glm::vec3* Point1Index;
	glm::vec3* Point2Index;
};

struct Plane
{
	Plane(glm::vec3* edge1, glm::vec3* edge2, glm::vec3* edge3)
	{
		Edge1Index = edge1;
		Edge2Index = edge2;
		Edge3Index = edge3;
	}
	glm::vec3* Edge1Index;
	glm::vec3* Edge2Index;
	glm::vec3* Edge3Index;
};

enum DrawMode {
	point,
	edge,
	plane
};

class Object
{
public:
	Object(glm::vec3 position, std::string name);
	~Object();

	glm::vec3 CenterPosition;
	std::vector<glm::vec3> Vertexes;
	std::vector<Edge> Edges;
	std::vector<Plane> Planes;
	std::string Name;

	std::vector<sf::Vertex> ProjectObject(glm::mat4x4 mvp, sf::Color color, DrawMode mode);
	std::vector<sf::Text> GetVertexIndixes(glm::mat4x4 mvp, glm::vec3 cameraPos, float fov, sf::Color color, const sf::Font& font);


	int AddPoint(glm::vec3 point);
	int AddEdge(glm::vec3 point1, glm::vec3 point2);
	int AddEdge(int point1, int point2);
	int AddPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	int AddPlane(int point1, int point2, int point3);

	void SetRotation(glm::quat quaternion);
	void SetPosition(glm::vec3 newPosition);

	void Rotate(float radiansDelta, glm::vec3 axis);
	void Move(glm::vec3 deltaPosition);
	void Scale(float scaleDelta);
	void Scale(float xDelta, float yDelta, float zDelta);
};

