#include "Headers/FontManager.h"
#include <SFML/Window.hpp>

sf::Font FontManager::GetFont()
{
    auto font = sf::Font();
    font.loadFromFile("./BOOKOS.TTF");
    return font;
}
