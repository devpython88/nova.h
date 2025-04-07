#pragma once

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFAULT_CAPTION "Game"

#include <string>
#include <raylib.h>
#include <stdexcept>

class NovaWindow {
    public:
    int width, height;
    std::string caption;

    NovaWindow(int w = DEFAULT_WIDTH, int h = DEFAULT_HEIGHT, const std::string& c = DEFAULT_CAPTION)
        : width(w), height(h), caption(c) {
        InitWindow(width, height, caption.c_str());
        InitAudioDevice();
    }

    ~NovaWindow(){
        CloseAudioDevice();
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
    const std::string path;
    
    
    NovaRenderImage(float x, float y, std::string path, float rotation = 0.0f):
    x(x), y(y), width(0), height(0), texture(LoadTexture(path.c_str())), path(path), rotation(rotation) {
        width = texture.width;
        height = texture.height;
    }

    bool checkCollision(NovaRenderImage image);
    bool checkCollision(NovaCircle circle);
    bool checkCollision(NovaRectangle rectangle);

    ~NovaRenderImage(){
        UnloadTexture(texture);
    }
};



class NovaSpritesheet {
    public:
    NovaRenderImage image;
    const float frameWidth, frameHeight;
    float rows, columns;
    float row, column;
    float x, y;

    NovaSpritesheet(std::string path, float x, float y, float frameWidth, float frameHeight):
    x(x), y(y), image(x, y, path), frameWidth(frameWidth), frameHeight(frameHeight),
    row(0), column(0){
        recalculateRows();
        recalculateColumns();
    }

    void recalculateRows();
    void recalculateColumns();


    void render();


};


class NovaAnimation : public NovaSpritesheet {
    protected:
    float frameTime;

    public:
    float maxFrameTime;
    bool loop;

    NovaAnimation(std::string path, float x, float y, float frameWidth, float frameHeight):
    NovaSpritesheet(path, x, y, frameWidth, frameHeight), maxFrameTime(1.0f), loop(false){}

    void play();
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
    static float deltaTime();


    static void text(std::string text, float x, float y, int fontSize, Color color);
};










class NovaInputDevice {
    public:

    static bool keyHit(int key);
    static bool keyHeld(int key);
    static bool keyUp(int key);

    static bool mouseButtonHit(int btn);
    static bool mouseButtonHeld(int btn);
    static bool mouseButtonUp(int btn);
};








/*********************************************/
/******************* AUDIO *******************/
/*********************************************/


class NovaSound {
    public:
    Sound sound;
    const std::string path;


    /****
     * @brief Volume in 0 to 100
     */
    void volume(int volume);

    /**
     * @brief Volume in 0.0f to 1.0f
     */
    void volume(float volume);

    bool loaded();

    NovaSound(std::string path):
    path(path), sound(LoadSound(path.c_str())){}


    void play();
};




class NovaMusic {
    public:
    Music music;
    bool loop;
    std::string path;
    

    /****
     * @brief Volume in 0 to 100
     */
    void volume(int volume);

    /**
     * @brief Volume in 0.0f to 1.0f
     */
    void volume(float volume);


    NovaMusic(std::string path, bool loop = true):
    path(path), loop(loop), music(LoadMusicStream(path.c_str())){
    }


    void update();
    void play();


    ~NovaMusic(){
        UnloadMusicStream(music);
    }
};