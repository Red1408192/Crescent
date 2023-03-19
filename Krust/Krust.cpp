#include "Map.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
constexpr int kWindowWidth = 1920;
constexpr int kWindowHeight = 1080;

constexpr int FRAME_RATE = 60;
constexpr int FRAME_TIME = 1000 / FRAME_RATE;
std::map<int, sf::Color> TileColors
{
    {0, sf::Color(255, 255, 255)},
    {1, sf::Color(255, 0, 0)},
    {2, sf::Color(0, 255, 0)},
    {3, sf::Color(0, 0, 255)},
    {4, sf::Color(255, 255, 0)},
    {5, sf::Color(255, 0, 255)},
    {6, sf::Color(0, 255, 255)},
    {7, sf::Color(150, 150, 150)},
    {8, sf::Color(150, 0, 0)},
    {9, sf::Color(0, 150, 0)},
    {10, sf::Color(0, 0, 150)},
    {11, sf::Color(150, 150, 0)},
    {12, sf::Color(150, 0, 150)},
    {13, sf::Color(0, 150, 150)},
};

int main(){
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Cube");
    window.setFramerateLimit(1);


    sf::Image img;
    img.create(kWindowWidth, kWindowHeight);
    sf::Texture tex;
    sf::Sprite spr;

    auto map = Map(kWindowWidth, kWindowHeight, 14, 200, 579);
    for (auto &&row : map.Matrix)
    {
        for (auto &&tile : row)
        {
            img.setPixel(tile.x,tile.y,TileColors[tile.ClusterIndex]);
        }
        
    }
    tex.loadFromImage(img);
    spr.setTexture(tex);

    while (window.isOpen()){
        window.clear();
        window.draw(spr);
        window.display();
    }

}