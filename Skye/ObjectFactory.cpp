#include "Headers/ObjectFactory.h"

Object ObjectFactory::CreateCube(std::string name)
{
    Object cube(glm::vec3(0, 0, 0), "Cube 1");

    cube.AddPoint(glm::vec3(-1, -1, -1));
    cube.AddPoint(glm::vec3(1, -1, -1));
    cube.AddPoint(glm::vec3(1, 1, -1));
    cube.AddPoint(glm::vec3(-1, 1, -1));

    cube.AddPoint(glm::vec3(-1, -1, 1));
    cube.AddPoint(glm::vec3(1, -1, 1));
    cube.AddPoint(glm::vec3(1, 1, 1));
    cube.AddPoint(glm::vec3(-1, 1, 1));

    //cube.AddEdge(0, 1);
    //cube.AddEdge(1, 2);
    //cube.AddEdge(2, 3);
    //cube.AddEdge(3, 0);

    //cube.AddEdge(4, 5);
    //cube.AddEdge(5, 6);
    //cube.AddEdge(6, 7);
    //cube.AddEdge(7, 4);

    //cube.AddEdge(0, 4);
    //cube.AddEdge(1, 5);
    //cube.AddEdge(2, 6);
    //cube.AddEdge(3, 7);

    cube.AddPlane(0, 1, 2);
    cube.AddPlane(2, 3, 0);

    cube.AddPlane(1, 5, 6);
    cube.AddPlane(6, 2, 1);

    cube.AddPlane(5, 4, 7);
    cube.AddPlane(7, 6, 5);

    cube.AddPlane(4, 0, 3);
    cube.AddPlane(3, 7, 4);

    cube.AddPlane(4, 5, 1);
    cube.AddPlane(1, 0, 4);

    cube.AddPlane(7, 2, 3);
    cube.AddPlane(2, 7, 6);

    //cube.AddPlane(glm::vec3(-1.0f, -1.0f, -1.0f),     glm::vec3(-1.0f, -1.0f, 1.0f),      glm::vec3(-1.0f, 1.0f, 1.0f)); 
    //cube.AddPlane(glm::vec3(1.0f, 1.0f, -1.0f),       glm::vec3(-1.0f, -1.0f, -1.0f),     glm::vec3(-1.0f, 1.0f, -1.0f)); 
    //cube.AddPlane(glm::vec3(1.0f, -1.0f, 1.0f),       glm::vec3(-1.0f, -1.0f, -1.0f),     glm::vec3(1.0f, -1.0f, -1.0f));
    //cube.AddPlane(glm::vec3(1.0f, 1.0f, -1.0f),       glm::vec3(1.0f, -1.0f, -1.0f),      glm::vec3(-1.0f, -1.0f, -1.0f));
    //cube.AddPlane(glm::vec3(-1.0f, -1.0f, -1.0f),     glm::vec3(-1.0f, 1.0f, 1.0f),       glm::vec3(-1.0f, 1.0f, -1.0f));
    //cube.AddPlane(glm::vec3(1.0f, -1.0f, 1.0f),       glm::vec3(-1.0f, -1.0f, 1.0f),      glm::vec3(-1.0f, -1.0f, -1.0f));
    //cube.AddPlane(glm::vec3(-1.0f, 1.0f, 1.0f),       glm::vec3(-1.0f, -1.0f, 1.0f),      glm::vec3(1.0f, -1.0f, 1.0f));
    //cube.AddPlane(glm::vec3(1.0f, 1.0f, 1.0f),        glm::vec3(1.0f, -1.0f, -1.0f),      glm::vec3(1.0f, 1.0f, -1.0f));
    //cube.AddPlane(glm::vec3(1.0f, -1.0f, -1.0f),      glm::vec3(1.0f, 1.0f, 1.0f),        glm::vec3(1.0f, -1.0f, 1.0f));
    //cube.AddPlane(glm::vec3(1.0f, 1.0f, 1.0f),        glm::vec3(1.0f, 1.0f, -1.0f),       glm::vec3(-1.0f, 1.0f, -1.0f));
    //cube.AddPlane(glm::vec3(1.0f, 1.0f, 1.0f),        glm::vec3(-1.0f, 1.0f, -1.0f),      glm::vec3(-1.0f, 1.0f, 1.0f));
    //cube.AddPlane(glm::vec3(1.0f, 1.0f, 1.0f),        glm::vec3(-1.0f, 1.0f, 1.0f),       glm::vec3(1.0f, -1.0f, 1.0f));


    return cube;
}

Object ObjectFactory::CreateTriangle(std::string name)
{
    Object triangle(glm::vec3(0, 0, 0), "Triangle 1");

    // Add the points for the triangle
    triangle.AddPoint(glm::vec3(-1, -1, 0));
    triangle.AddPoint(glm::vec3(1, -1, 0));
    triangle.AddPoint(glm::vec3(0, 1, 0));

    // Add the plane for the triangle
    triangle.AddPlane(0, 1, 2);

    return triangle;
}
Object ObjectFactory::CreateHexagon(std::string name)
{
    Object hexagon(glm::vec3(0, 0, 0), "Hexagon 1");

    // Add the points for the hexagon
    hexagon.AddPoint(glm::vec3(-1, 0, 0));
    hexagon.AddPoint(glm::vec3(-0.5, 0.866, 0));
    hexagon.AddPoint(glm::vec3(0.5, 0.866, 0));
    hexagon.AddPoint(glm::vec3(1, 0, 0));
    hexagon.AddPoint(glm::vec3(0.5, -0.866, 0));
    hexagon.AddPoint(glm::vec3(-0.5, -0.866, 0));
    hexagon.AddPoint(glm::vec3(0, 0, 0));

    // Add the plane for the hexagon
    hexagon.AddPlane(0, 1, 7);
    hexagon.AddPlane(1, 2, 7);
    hexagon.AddPlane(2, 3, 7);
    hexagon.AddPlane(3, 4, 7);
    hexagon.AddPlane(4, 5, 7);
    hexagon.AddPlane(5, 6, 7);
    hexagon.AddPlane(6, 0, 7);

    return hexagon;
}

Object ObjectFactory::CreatePiramid(std::string name)
{
    Object pir(glm::vec3(0, 0, 0), "priramid 1");

    pir.AddPoint(glm::vec3(-1, -1, -1));
    pir.AddPoint(glm::vec3(-1, -1, 1));
    pir.AddPoint(glm::vec3(1, -1, 1));
    pir.AddPoint(glm::vec3(1, -1, -1));

    pir.AddPoint(glm::vec3(0, 1, 0));

    pir.AddPlane(0, 1, 2);
    pir.AddPlane(2, 3, 0);

    pir.AddPlane(4, 0, 1);
    pir.AddPlane(4, 1, 2);
    pir.AddPlane(4, 2, 3);
    pir.AddPlane(4, 3, 0);

    return pir;
}
