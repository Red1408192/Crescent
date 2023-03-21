#include "Map.cpp"
#include "bitmap.cpp"
#include <vector>

constexpr int kWindowWidth = 1920;
constexpr int kWindowHeight = 1080;

constexpr int FRAME_RATE = 60;
constexpr int FRAME_TIME = 1000 / FRAME_RATE;
std::map<int, Pixel> TileColors
{
    {0, Pixel(255, 255, 255)},
    {1, Pixel(255, 0, 0)},
    {2, Pixel(0, 255, 0)},
    {3, Pixel(0, 0, 255)},
    {4, Pixel(255, 255, 0)},
    {5, Pixel(255, 0, 255)},
    {6, Pixel(0, 255, 255)},
    {7, Pixel(150, 150, 150)},
    {8, Pixel(150, 0, 0)},
    {9, Pixel(0, 150, 0)},
    {10, Pixel(0, 0, 150)},
    {11, Pixel(150, 150, 0)},
    {12, Pixel(150, 0, 150)},
    {13, Pixel(0, 150, 150)},
    {14, Pixel(75, 75, 75)},
    {15, Pixel(75, 0, 0)},
    {16, Pixel(0, 75, 0)},
    {17, Pixel(0, 0, 75)},
    {18, Pixel(75, 75, 0)},
    {19, Pixel(75, 0, 75)},
    {20, Pixel(0, 75, 75)},
    {21, Pixel(0, 0, 0)},
};

int main(){
    auto map = Map(kWindowWidth, kWindowHeight, 20, 200, 8989);
    Bitmap image;
    std::vector<std::vector<Pixel>> bmp(kWindowHeight, std::vector<Pixel>(kWindowWidth));
    Pixel rgb;
    for (size_t c = 0; c < kWindowHeight; c++)
    {
        for (size_t r = 0; r < kWindowWidth; r++)
        {
            auto tile = map.Matrix[c][r];
            bmp[c][r] = TileColors[tile.ClusterIndex];
            auto tileHeight = map.Matrix[c][r].Height;
            bmp[c][r].blue = static_cast<char>(bmp[c][r].blue *(.3 + tileHeight/1000.));
            bmp[c][r].red = static_cast<char>(bmp[c][r].red * (.3 + tileHeight/1000.));
            bmp[c][r].green = static_cast<char>(bmp[c][r].green * (.3 + tileHeight/1000.));
        }
    }
    image.fromPixelMatrix(bmp);
    image.save("Map.bmp");
}