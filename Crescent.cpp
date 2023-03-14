#include "Scene.cpp"
#include "Object.cpp"
#include "ObjectFactory.cpp"
#include "FontManager.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

constexpr int kWindowWidth = 1920;
constexpr int kWindowHeight = 1080;

constexpr int FRAME_RATE = 60;
constexpr int FRAME_TIME = 1000 / FRAME_RATE;

std::mutex inputMutex;
std::queue<std::string> inputQueue;

void InputThread()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        std::lock_guard<std::mutex> lock(inputMutex);
        inputQueue.push(input);
    }
}

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Cube");
    sf::View view;
    view.setSize(kWindowWidth, kWindowHeight);
    view.setCenter(sf::Vector2f(0, 0));
    window.setView(view);
    Scene scene(kWindowWidth, kWindowHeight);

    std::thread inputThread(InputThread);

    auto cube = ObjectFactory::CreateCube("cube");
    auto triangle = ObjectFactory::CreateTriangle("tri");
    auto piramid = ObjectFactory::CreatePiramid("pir");
    triangle.Scale(20);
    triangle.Move(glm::vec3(50, 0, 0));
    triangle.Rotate(90, glm::vec3(1, 0, 0));
    cube.Scale(10);
    cube.Move(glm::vec3(0, 10, 0));
    piramid.Move(glm::vec3(-50, 20, 0));
    piramid.Scale(20);

    scene.AddObjectToScene(cube);
    scene.AddObjectToScene(triangle);
    scene.AddObjectToScene(piramid);
    auto font = FontManager::GetFont();

    window.setFramerateLimit(FRAME_RATE);
    // Main loop
    auto Gridclock = sf::Clock();
    bool showGrid = false;

    auto DrawModeclock = sf::Clock();
    auto mode = DrawMode::point;

    auto Indexeslock = sf::Clock();
    bool showIndexes = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            std::lock_guard<std::mutex> lock(inputMutex);
            if (!inputQueue.empty())
            {
                std::string input = inputQueue.front();
                inputQueue.pop();
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::I) scene.OrbitCamera(0.01, 0);
            if (event.key.code == sf::Keyboard::J) scene.OrbitCamera(0, -0.01);
            if (event.key.code == sf::Keyboard::K) scene.OrbitCamera(-0.01, 0);
            if (event.key.code == sf::Keyboard::L) scene.OrbitCamera(0, 0.01);
            if (event.key.code == sf::Keyboard::R) scene.DistanceCamera(0.01);
            if (event.key.code == sf::Keyboard::F) scene.DistanceCamera(-0.01);

            if (event.key.control == sf::Keyboard::W)
            {
                scene.MoveCameraPos(glm::vec3(0, 0, 1));
            }
            if (event.key.code == sf::Keyboard::A) scene.MoveCameraPos(glm::vec3(1, 0, 0));
            if (event.key.code == sf::Keyboard::S) scene.MoveCameraPos(glm::vec3(0, 0, -1));
            if (event.key.code == sf::Keyboard::D) scene.MoveCameraPos(glm::vec3(-1, 0, 0));
            if (event.key.code == sf::Keyboard::Q) scene.MoveCameraPos(glm::vec3(0, 1, 0));
            if (event.key.code == sf::Keyboard::E) scene.MoveCameraPos(glm::vec3(0, -1, 0));

            if (event.key.code == sf::Keyboard::Add) scene.ScaleFov(-1);
            if (event.key.code == sf::Keyboard::Subtract) scene.ScaleFov(1);


            auto elapsed = Gridclock.getElapsedTime();
            if (elapsed > sf::milliseconds(500) && event.key.code == sf::Keyboard::G)
            {
                Gridclock.restart();
                showGrid = !showGrid;
            }
            auto elapsed2 = DrawModeclock.getElapsedTime();
            if (elapsed2 > sf::milliseconds(500) && event.key.code == sf::Keyboard::T)
            {
                DrawModeclock.restart();
                mode = static_cast<DrawMode>((mode + 1) % 3);
            }
            auto elapsed3 = Indexeslock.getElapsedTime();
            if (elapsed3 > sf::milliseconds(500) && event.key.code == sf::Keyboard::H)
            {
                Indexeslock.restart();
                showIndexes = !showIndexes;
            }
        }
        window.clear();
        if (showGrid) window.draw(scene.GetGrid());

        window.draw(scene.ProjectObjects(mode, sf::Color::White));

        if(showIndexes) for(auto const i : scene.ProjectObjectsVertexIndex(sf::Color(40, 40, 40), font)) window.draw(i);
        window.display();


    }

    return 0;
}