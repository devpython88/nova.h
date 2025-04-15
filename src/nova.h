#pragma once

// Default window properties
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFAULT_CAPTION "Game"

#include <string>
#include <raylib.h>
#include <stdexcept>
#include <map>
#include <cmath>
#include <random>


// Default color for modal
const Color NOVA_MODAL_WINDOW_COLOR_DEFAULT = Color{20, 20, 20, 255};
const Color NOVA_MODAL_WINDOW_COLOR_LIGHT   = Color{250, 250, 250, 255};
const Color NOVA_MODAL_WINDOW_COLOR_NIGHT   = Color{20, 50, 20, 255};


class NovaWindow;





/********************************/
/** EXTRAS                      */
/********************************/





// Class for randomization
class NovaRandomDevice {
    public:

    std::random_device rd;
    std::mt19937 gen;

    NovaRandomDevice(): rd(), gen(rd()){}

    int randomInt(int s, int e);
    float randomFloat(float s, float e);
    int randomIndex(std::string str);

    template <typename T>
    int randomIndex(std::vector<T> v){
        int start = 0;
        int end = v.size() - 1;

        return randomInt(start, end);
    }

    // Template functions cannot be implemented seperately
    template <typename T>
    T randomItem(std::vector<T> v){
        int s = 0;
        int e = v.size() - 1;
        
        return v.at(randomInt(s, e));
    }


    // Shuffler function
    template <typename T>
    std::vector<T> shuffle(std::vector<T> source, std::vector<T> values){
        std::vector<T> shuffled;

        for (int i = 0; i < source.size(); i++){
            shuffled.push_back(values.at(randomIndex<T>(values)));
        }

        return shuffled;
    }
};

// Class required for checking positions. 
class NovaAxis {
    private:
    friend class NovaWindow;

    int width, height;
    NovaAxis(int width, int height): width(width), height(height){}

    public:

    NovaAxis(){}

    inline bool overflowX(float x){ return x < 0 || x > width; }
    inline bool overflowY(float y){ return y < 0 || y > height; }
    inline bool overflow(float x, float y) { return overflowX(x) || overflowY(y); }


    inline bool atTop(float y){ return y < 0; }
    inline bool atBottom(float y){ return y > height; }
    inline bool atLeft(float x){ return x < 0; }
    inline bool atRight(float x){ return x > width; }
    inline bool atMiddle(float x){ return ((int) x) == width / 2; }
    inline bool atMiddleY(float y){ return ((int) y) == height / 2; }
};






/********************************/
/** WINDOW                      */
/********************************/





// Class representing a game window
class NovaWindow {
    private:
    Camera2D camera; // Camera for 2D rendering

    public:
    int width, height; // Window dimensions
    std::string caption; // Window title

    // Constructor to initialize the window and audio device
    NovaWindow(int w = DEFAULT_WIDTH, int h = DEFAULT_HEIGHT, const std::string& c = DEFAULT_CAPTION)
        : width(w), height(h), caption(c) {
        InitWindow(width, height, caption.c_str());
        InitAudioDevice();

        camera = { 0 };
        camera.zoom = 1.0f;
        camera.target = { 0, 0 };
        camera.rotation = 0;
        camera.offset = { 0, 0 };
    }

    // Destructor to clean up resources
    ~NovaWindow(){
        CloseAudioDevice();
        CloseWindow();
    }

    // Window control methods
    bool open();
    void start();
    void uiMode();
    void end();

    // Camera control methods
    void centerCamera(float x, float y);
    Vector2* target();
    float getCameraZoom();
    void setCameraZoom(float zoom);
    void setCameraRotation(float rotation);
    float getCameraRotation();

    // Axis
    NovaAxis axis();
};




/********************************/
/** SHAPES & OBJECTS            */
/********************************/





// Base class for all objects
class NovaObject4 {
    public:
    float x, y;
    float width, height;
    float rotation;

    NovaObject4(float x, float y, float width, float height, float rotation): x(x), y(y), width(width), height(height), rotation(rotation){}
};

// Class representing a rectangle
class NovaRectangle : public NovaObject4 {
    public:
    Color color; // Color of the rectangle

    // Constructor to initialize rectangle properties
    NovaRectangle(float x, float y, float width, float height, Color color, float rotation = 0.0f)
        : NovaObject4(x, y, width, height, rotation), color(color) {}
    
    // Check collision with another rectangle
    [[deprecated("WILL BE REMOVED IN V1.5! Use NovaRenderDevice::checkCollision instead.")]] bool checkCollision(NovaRectangle other);
};

// Class representing a circle
class NovaCircle {
    public:
    float x, y; // Position
    float radius; // Radius of the circle
    Color color; // Color of the circle

    // Constructor to initialize circle properties
    NovaCircle(float x, float y, float radius, Color color): x(x), y(y), radius(radius), color(color) {}
    
    // Collision detection methods
    [[deprecated("WILL BE REMOVED IN V1.5! Use NovaRenderDevice::checkCollision instead.")]] bool checkCollision(NovaObject4 other);
    [[deprecated("WILL BE REMOVED IN V1.5! Use NovaRenderDevice::checkCollision instead.")]] bool checkCollision(NovaCircle other);
};

// Class representing a renderable image
class NovaRenderImage : public NovaObject4 {    
    public:
    Texture texture; // Texture of the image
    const std::string path; // File path of the image
    
    // Constructor to load the image texture
    NovaRenderImage(float x, float y, std::string path, float rotation = 0.0f):
    NovaObject4(x, y, 0, 0, rotation), texture(LoadTexture(path.c_str())), path(path) {
        width = texture.width;
        height = texture.height;
    }

    // Collision detection methods
    [[deprecated("WILL BE REMOVED IN V1.5! Use NovaRenderDevice::checkCollision instead.")]] bool checkCollision(NovaRenderImage image);
    [[deprecated("WILL BE REMOVED IN V1.5! Use NovaRenderDevice::checkCollision instead.")]] bool checkCollision(NovaCircle circle);
    [[deprecated("WILL BE REMOVED IN V1.5! Use NovaRenderDevice::checkCollision instead.")]] bool checkCollision(NovaRectangle rectangle);

    // Destructor to unload the texture
    void dispose(){
        UnloadTexture(texture);
    }
};





/********************************/
/** ANIMATIONS                  */
/********************************/







// Class representing a spritesheet
class NovaSpritesheet {
    public:
    NovaRenderImage image; // Renderable image
    const float frameWidth, frameHeight; // Frame dimensions
    float rows, columns; // Number of rows and columns in the spritesheet
    float row, column; // Current frame position
    float x, y; // Position of the spritesheet

    // Constructor to initialize spritesheet properties
    NovaSpritesheet(std::string path, float x, float y, float frameWidth, float frameHeight):
    x(x), y(y), image(x, y, path), frameWidth(frameWidth), frameHeight(frameHeight),
    row(0), column(0){
        recalculateRows();
        recalculateColumns();
    }

    // Recalculate rows and columns based on frame dimensions
    void recalculateRows();
    void recalculateColumns();

    // Render the current frame
    void render();

    void dispose() { image.dispose(); }
};

// Class representing an animation, derived from NovaSpritesheet
class NovaAnimation : public NovaSpritesheet {
    protected:
    float frameTime; // Time per frame

    public:
    float maxFrameTime; // Maximum time per frame
    bool loop; // Whether the animation loops

    // Constructor to initialize animation properties
    NovaAnimation(std::string path, float x, float y, float frameWidth, float frameHeight):
    NovaSpritesheet(path, x, y, frameWidth, frameHeight), maxFrameTime(1.0f), loop(false){}

    // Play the animation
    void play();
    void dispose() { image.dispose(); }
};




/********************************/
/** RENDERING                   */
/********************************/






// Class for rendering shapes and images
class NovaRenderDevice {
    public:

    // Fill the screen with a color
    static void fill(Color color);
    
    // Draw rectangles
    static void rect(float left, float top, float width, float height, Color color);
    static void rect(NovaRectangle rect);

    // Draw circles
    static void circle(float centerX, float centerY, float radius, Color color);
    static void circle(NovaCircle circle);

    // Draw other shapes
    static void line(float x1, float y1, float x2, float y2, Color c);
    static void point(float x, float y, Color c);
    static void poly(float x, float y, float sides, float radius, Color c, float rotation = 0.0f);

    // Draw images
    static void image(NovaRenderImage image);
    
    // Check if an image is loaded
    static bool imageLoaded(NovaRenderImage image);

    // Set framerate limit
    static void framerateLimit(int limit);
    static float deltaTime();

    // Draw text
    static void text(std::string text, float x, float y, int fontSize, Color color);

    // Modern collision

    static bool checkCollision(NovaObject4 obj, NovaObject4 obj2);
    static bool checkCollision(NovaObject4 obj, NovaCircle circ);
};




/********************************/
/** INPUT                       */
/********************************/






// Class for handling input devices
class NovaInputDevice {
    public:

    // Keyboard input methods
    static bool keyHit(int key);
    static bool keyHeld(int key);
    static bool keyUp(int key);

    // Mouse input methods
    static bool mouseButtonHit(int btn);
    static bool mouseButtonHeld(int btn);
    static bool mouseButtonUp(int btn);

    // Mouse UI methods
    static bool mouseHover(float left, float top, float width, float height);
    static bool mouseClick(float left, float top, float width, float height);
    
    // Mouse scroll methods
    static float getScroll();
    static int getScrollEx();
};





/********************************/
/** AUDIO                       */
/********************************/




// Class for handling sound effects
class NovaSound {
    public:
    Sound sound; // Sound object
    const std::string path; // File path of the sound

    // Set volume (0 to 100)
    void volume(int volume);

    // Set volume (0.0f to 1.0f)
    void volume(float volume);

    // Check if the sound is loaded
    bool loaded();

    // Constructor to load the sound
    NovaSound(std::string path):
    path(path), sound(LoadSound(path.c_str())){}

    // Play the sound
    void play();
};

// Class for handling music
class NovaMusic {
    public:
    Music music; // Music object
    bool loop; // Whether the music loops
    std::string path; // File path of the music

    // Set volume (0 to 100)
    void volume(int volume);

    // Set volume (0.0f to 1.0f)
    void volume(float volume);

    // Constructor to load the music
    NovaMusic(std::string path, bool loop = true):
    path(path), loop(loop), music(LoadMusicStream(path.c_str())){}

    // Update the music stream
    void update();

    // Play the music
    void play();

    // Destructor to unload the music stream
    ~NovaMusic(){
        UnloadMusicStream(music);
    }
};




/********************************/
/** INPUT MANAGER               */
/********************************/




class NovaBinding {
    public:
    static const int KEYBIND   = 0;
    static const int MOUSEBIND = 1;
    

    int type;
    int code;


    NovaBinding(int type, int code): type(type), code(code){}
    NovaBinding(){}
    
    bool held();
    bool hit();
    bool up();
};


class NovaInputManager {
    public:
    std::map<std::string, NovaBinding> bindings;

    NovaInputManager(): bindings(){}

    void bindKey(std::string name, int code);
    void bindMouse(std::string name, int code);

    bool held(std::string name);
    bool hit(std::string name);
    bool up(std::string name);
};









