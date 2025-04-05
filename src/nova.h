#pragma once

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFAULT_CAPTION "Game"

#include <string>
#include <raylib.h>

class NovaWindow {
    public:
    int width, height;
    std::string caption;

    NovaWindow(int w = DEFAULT_WIDTH, int h = DEFAULT_HEIGHT, const std::string& c = DEFAULT_CAPTION)
        : width(w), height(h), caption(c) {
        InitWindow(width, height, caption.c_str());
    }

    ~NovaWindow(){
        CloseWindow();
    }


    bool open();
    void start();
    void end();
};











class NovaRectangle {
    public:
    float x, y;
    float width, height;
    float rotation;
    Color color;

    NovaRectangle(float x, float y, float width, float height, Color color, float rotation = 0.0f)
        : x(x), y(y), width(width), height(height), color(color), rotation(rotation) {}
    
    bool checkCollision(NovaRectangle other);
};


class NovaCircle {
    public:
    float x, y;
    float radius;
    Color color;

    NovaCircle(float x, float y, float radius, Color color): x(x), y(y), radius(radius), color(color) {}
    
    bool checkCollision(NovaRectangle other);
    bool checkCollision(NovaCircle other);
};


class NovaRenderImage {    
    public:
    Texture texture;
    float x, y;
    float width, height;
    float rotation;


    NovaRenderImage(float x, float y, std::string path, float rotation = 0.0f):
    x(x), y(y), width(0), height(0), texture(LoadTexture(path.c_str())), rotation(rotation) {
        width = texture.width;
        height = texture.height;
    }

    bool checkCollision(NovaRenderImage image);
    bool checkCollision(NovaCircle circle);
    bool checkCollision(NovaRectangle rectangle);
};







class NovaRenderDevice {
    public:

    static void fill(Color color);
    
    static void rect(float left, float top, float width, float height, Color color);
    static void rect(NovaRectangle rect);

    static void circle(float centerX, float centerY, float radius, Color color);
    static void circle(NovaCircle circle);

    static void image(NovaRenderImage image);
    
    static bool imageLoaded(NovaRenderImage image);

    static void framerateLimit(int limit);
};
