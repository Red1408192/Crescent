#include "Map.cpp"
#include "bitmap.cpp"
#include <vector>
#include <gtk/gtk.h>
#include <future>

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

int EvaluatePixel(int original, double height){
    auto newValue = static_cast<int>(original *(height * (1./4000.)));
    newValue = std::max(newValue, 0);
    newValue = std::min(newValue, 255);
    return newValue;
}
static void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Krust");
  gtk_window_set_default_size (GTK_WINDOW (window), kWindowWidth, kWindowHeight);
  gtk_widget_show (window);
}
int main(int argc, char **argv){
    auto map = Map(kWindowWidth, kWindowHeight, 20, 200, 694149);
    Bitmap image;
    std::vector<std::vector<Pixel>> bmp(kWindowHeight, std::vector<Pixel>(kWindowWidth));
    Pixel rgb;

    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.Krust", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    for (size_t c = 0; c < kWindowHeight; c++)
    {
        for (size_t r = 0; r < kWindowWidth; r++)
        {
            auto tile = map.Matrix[c][r];
            bmp[c][r] = TileColors[tile.ClusterIndex];
            bmp[c][r].blue = EvaluatePixel(bmp[c][r].blue, map.Matrix[c][r].Height);
            bmp[c][r].red = EvaluatePixel(bmp[c][r].red, map.Matrix[c][r].Height);
            bmp[c][r].green = EvaluatePixel(bmp[c][r].green, map.Matrix[c][r].Height);
        }
    }
    image.fromPixelMatrix(bmp);
    image.save("Map.bmp");
}