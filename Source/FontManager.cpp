#include "FontManager.h"
#include <Windows.h>

sf::Font FontManager::GetFont()
{
    auto font = sf::Font();
    font.loadFromFile("./BOOKOS.TTF");
    return font;
}
