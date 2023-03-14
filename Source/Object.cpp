#include "Object.h"
Object::Object(glm::vec3 position, std::string name)
{
	this->CenterPosition = position;
	this->Name = name;
	Vertexes = std::vector<glm::vec3>();
	Edges = std::vector<Edge>();
	Planes = std::vector<Plane>();
}

Object::~Object()
{
}

std::vector<sf::Vertex> Object::ProjectObject(glm::mat4x4 mvp, sf::Color color, DrawMode mode)
{
	switch (mode)
	{
		case point:
		{
			std::vector<sf::Vertex> projectedVertices = std::vector<sf::Vertex>();
			for (const auto vertex : Vertexes)
			{
				// Get the points for the line
				glm::vec3 point1 = vertex;

				// Move the points based on the object's position
				point1 += CenterPosition;

				// Project the points using the given camera matrix
				glm::vec4 projectedPoint1 = mvp * glm::vec4(point1, 1.0f);

				// Add the projected points to the vertex array
				projectedVertices.push_back(sf::Vertex(sf::Vector2f(projectedPoint1.x, projectedPoint1.y), color));
			}
			return projectedVertices;
			break;
		}
		case edge:
		{
			std::vector<sf::Vertex> projectedEdges = std::vector<sf::Vertex>();
			for (const auto vertex : Edges)
			{
				// Get the points for the line
				glm::vec3 point1 = *vertex.Point1Index;
				glm::vec3 point2 = *vertex.Point2Index;

				// Move the points based on the object's position
				point1 += CenterPosition;
				point2 += CenterPosition;

				// Project the points using the given camera matrix
				glm::vec4 projectedPoint1 = mvp * glm::vec4(point1, 1.0f);
				glm::vec4 projectedPoint2 = mvp * glm::vec4(point2, 1.0f);

				// Add the projected points to the vertex array
				projectedEdges.push_back(sf::Vertex(sf::Vector2f(projectedPoint1.x, projectedPoint1.y), color));
				projectedEdges.push_back(sf::Vertex(sf::Vector2f(projectedPoint2.x, projectedPoint2.y), color));
			}
			return projectedEdges;
			break;
		}
		case plane:
		{
			std::vector<sf::Vertex> projectedPlanes = std::vector<sf::Vertex>();
			for (const auto plane : Planes)
			{
				// Get the points for the line
				auto point1 = *plane.Edge1Index;
				auto point2 = *plane.Edge2Index;
				auto point3 = *plane.Edge3Index;

				// Move the points based on the object's position
				point1 += CenterPosition;
				point2 += CenterPosition;
				point3 += CenterPosition;

				// Project the points using the given camera matrix
				glm::vec4 projectedPoint1 = mvp * glm::vec4(point1, 1.0f);
				glm::vec4 projectedPoint2 = mvp * glm::vec4(point2, 1.0f);
				glm::vec4 projectedPoint3 = mvp * glm::vec4(point3, 1.0f);

				// Add the projected points to the vertex array
				projectedPlanes.push_back(sf::Vertex(sf::Vector2f(projectedPoint1.x, projectedPoint1.y), color));
				projectedPlanes.push_back(sf::Vertex(sf::Vector2f(projectedPoint2.x, projectedPoint2.y), color));
				projectedPlanes.push_back(sf::Vertex(sf::Vector2f(projectedPoint3.x, projectedPoint3.y), color));
			}
			return projectedPlanes;
			break;
		}
		default:
			return std::vector<sf::Vertex>();
			break;
	}

}

std::vector<sf::Text> Object::GetVertexIndixes(glm::mat4x4 mvp, glm::vec3 cameraPos, float fov, sf::Color color, const sf::Font& font)
{
	std::vector<sf::Text> result = std::vector<sf::Text>();
		
	for (int i = 0; i < Vertexes.size(); i++)
	{
		auto text = sf::Text();
		text.setFont(font);

		auto point = Vertexes[i] * 1.05f;
		point += CenterPosition;
		auto proj = mvp * glm::vec4(point, 1.f);
		text.setPosition(sf::Vector2f(proj.x, proj.y));
		text.setCharacterSize(32/fov);
		auto tex = std::to_string(i);
		text.setString(tex);
		if(text.getCharacterSize() > 1) result.push_back(text);
	}

	return result;
}


int Object::AddPoint(glm::vec3 point)
{
	this->Vertexes.push_back(point);
	auto index = static_cast<int>(this->Vertexes.size() - 1);
	return index;
}

int Object::AddEdge(glm::vec3 point1, glm::vec3 point2)
{
	this->Vertexes.push_back(point1);
	this->Vertexes.push_back(point2);
	this->Edges.push_back(Edge(&point1, &point2));
	auto index = static_cast<int>(this->Edges.size() - 1);

	return index;
}

int Object::AddEdge(int point1, int point2)
{
	this->Edges.push_back(Edge(&Vertexes[point1], &Vertexes[point2]));
	auto index = static_cast<int>(this->Edges.size() - 1);
	return index;
}

int Object::AddPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	this->Vertexes.push_back(point1);
	this->Vertexes.push_back(point2);
	this->Vertexes.push_back(point3);
	this->Edges.push_back(Edge(&point1, &point2));
	this->Edges.push_back(Edge(&point2, &point3));
	this->Edges.push_back(Edge(&point3, &point1));
	this->Planes.push_back(Plane(&point1, &point2, &point3));
	auto index = static_cast<int>(this->Planes.size() - 1);

	return index;
}

int Object::AddPlane(int point1, int point2, int point3)
{
	this->Edges.push_back(Edge(&Vertexes[point1], &Vertexes[point2]));
	this->Edges.push_back(Edge(&Vertexes[point2], &Vertexes[point3]));
	this->Edges.push_back(Edge(&Vertexes[point3], &Vertexes[point1]));
	this->Planes.push_back(Plane(&Vertexes[point1], &Vertexes[point2], &Vertexes[point3]));
	auto index = static_cast<int>(this->Planes.size() - 1);
	return 0;
}


void Object::SetRotation(glm::quat quaternion)
{
	for (glm::vec3& point : Vertexes)
	{
		// Rotate the point using the quaternion
		point = quaternion * point;
	}
}

void Object::SetPosition(glm::vec3 newPosition)
{
	CenterPosition = newPosition;
}

void Object::Rotate(float radiansDelta, glm::vec3 axis)
{
	for (glm::vec3& point : Vertexes)
	{
		// Rotate the point using the quaternion
		point = glm::angleAxis(glm::radians(radiansDelta), axis) * point;
	}
}

void Object::Move(glm::vec3 deltaPosition)
{
	this->CenterPosition += deltaPosition;
}

void Object::Scale(float scaleDelta)
{
	for (glm::vec3& point : Vertexes)
	{
		// Scale the point by the delta distance
		point = scaleDelta * (point);
	}
}

void Object::Scale(float xDelta, float yDelta, float zDelta)
{
	for (glm::vec3& point : Vertexes)
	{
		// Scale the point by the delta distances
		point.x = xDelta * (point.x);
		point.y = yDelta * (point.y);
		point.z = zDelta * (point.z);
	}
}
