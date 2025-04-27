#pragma once

// Default window properties
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFAULT_CAPTION "Game"
#define SIGNAL(f) std::function<void(void)>(f)

#include <iostream>
#include <raylib.h>
#include <stdexcept>
#include <map>
#include <cmath>
#include <chrono>
#include <ctime> 
#include <random>
#include <functional>


// Default color for modal
const Color NOVA_MODAL_WINDOW_COLOR_DEFAULT = Color{20, 20, 20, 255};
const Color NOVA_MODAL_WINDOW_COLOR_LIGHT   = Color{250, 250, 250, 255};
const Color NOVA_MODAL_WINDOW_COLOR_NIGHT   = Color{20, 50, 20, 255};


class NovaWindow;





/********************************/
/** EXTRAS                      */
/********************************/








class NovaVec2 {
public:
    float x, y;


    NovaVec2() = default;
    NovaVec2(float x, float y) : x(x), y(y) {}
    
    NovaVec2 operator+(NovaVec2 v) const { return {v.x + x, v.y + y}; }
    NovaVec2 operator-(NovaVec2 v) const { return {v.x - x, v.y - y}; }
    NovaVec2 operator*(NovaVec2 v) const { return {v.x * x, v.y * y}; }
    NovaVec2 operator/(NovaVec2 v) const { return {v.x / x, v.y / y}; }
    
    void operator+=(NovaVec2 v) { x += v.x; y += v.y; }
    void operator-=(NovaVec2 v) { x -= v.x; y -= v.y; }
    void operator*=(NovaVec2 v) { x *= v.x; y *= v.y; }
    void operator/=(NovaVec2 v) { x /= v.x; y /= v.y; }
};

class NovaVec3 {
    public:
    float x, y, z;

    NovaVec3() = default;
    NovaVec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    NovaVec3 operator+(NovaVec3 v) const { return {v.x + x, v.y + y, v.z + z}; }
    NovaVec3 operator-(NovaVec3 v) const { return {v.x - x, v.y - y, v.z - z}; }
    NovaVec3 operator*(NovaVec3 v) const { return {v.x * x, v.y * y, v.z * z}; }
    NovaVec3 operator/(NovaVec3 v) const { return {v.x / x, v.y / y, v.z / z}; }

    void operator+=(NovaVec3 v) { x += v.x; y += v.y; z += v.z; }
    void operator-=(NovaVec3 v) { x -= v.x; y -= v.y; z -= v.z; }
    void operator*=(NovaVec3 v) { x *= v.x; y *= v.y; z *= v.z; }
    void operator/=(NovaVec3 v) { x /= v.x; y /= v.y; z /= v.z; }
};


class NovaVec4 {
public:
    float x, y, z, w;

    NovaVec4() = default;
    NovaVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    
    NovaVec4 operator+(NovaVec4 v) const { return {v.x + x, v.y + y, v.z + z, v.w + w}; }
    NovaVec4 operator-(NovaVec4 v) const { return {v.x - x, v.y - y, v.z - z, v.w - w}; }
    NovaVec4 operator*(NovaVec4 v) const { return {v.x * x, v.y * y, v.z * z, v.w * w}; }
    NovaVec4 operator/(NovaVec4 v) const { return {v.x / x, v.y / y, v.z / z, v.w / w}; }
    
    void operator+=(NovaVec4 v) { x += v.x; y += v.y; z += v.z; w += v.w; }
    void operator-=(NovaVec4 v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }
    void operator*=(NovaVec4 v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; }
    void operator/=(NovaVec4 v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; }
};


class NovaEvent {
    public:
    class Key {
        public:
        // Letters A-Z
        static const int A = KEY_A;
        static const int B = KEY_B;
        static const int C = KEY_C;
        static const int D = KEY_D;
        static const int E = KEY_E;
        static const int F = KEY_F;
        static const int G = KEY_G;
        static const int H = KEY_H;
        static const int I = KEY_I;
        static const int J = KEY_J;
        static const int K = KEY_K;
        static const int L = KEY_L;
        static const int M = KEY_M;
        static const int N = KEY_N;
        static const int O = KEY_O;
        static const int P = KEY_P;
        static const int Q = KEY_Q;
        static const int R = KEY_R;
        static const int S = KEY_S;
        static const int T = KEY_T;
        static const int U = KEY_U;
        static const int V = KEY_V;
        static const int W = KEY_W;
        static const int X = KEY_X;
        static const int Y = KEY_Y;
        static const int Z = KEY_Z;

        // Numbers 0-9
        static const int Zero = KEY_ZERO;
        static const int One = KEY_ONE;
        static const int Two = KEY_TWO;
        static const int Three = KEY_THREE;
        static const int Four = KEY_FOUR;
        static const int Five = KEY_FIVE;
        static const int Six = KEY_SIX;
        static const int Seven = KEY_SEVEN;
        static const int Eight = KEY_EIGHT;
        static const int Nine = KEY_NINE;

        // Special characters
        static const int Space = KEY_SPACE;
        static const int Enter = KEY_ENTER;
        static const int Backspace = KEY_BACKSPACE;
        static const int Tab = KEY_TAB;
        static const int Escape = KEY_ESCAPE;
        static const int Apostrophe = KEY_APOSTROPHE; // '
        static const int Comma = KEY_COMMA;      // ,
        static const int Minus = KEY_MINUS;      // -
        static const int Period = KEY_PERIOD;     // .
        static const int Slash = KEY_SLASH;      // /
        static const int Semicolon = KEY_SEMICOLON;   // ;
        static const int Equal = KEY_EQUAL;       // =
        static const int LeftBracket = KEY_LEFT_BRACKET;  // [
        static const int Backslash = KEY_BACKSLASH;     // Backslash
        static const int RightBracket = KEY_RIGHT_BRACKET; // ]
        static const int Grave = KEY_GRAVE;         // ` (grave accent)

        // Modifier keys
        static const int LeftShift = KEY_LEFT_SHIFT;
        static const int RightShift = KEY_RIGHT_SHIFT;
        static const int LeftControl = KEY_LEFT_CONTROL;
        static const int RightControl = KEY_RIGHT_CONTROL;
        static const int LeftAlt = KEY_LEFT_ALT;
        static const int RightAlt = KEY_RIGHT_ALT;
        static const int LeftSuper = KEY_LEFT_SUPER;
        static const int RightSuper = KEY_RIGHT_SUPER;
        static const int CapsLock = KEY_CAPS_LOCK;
        static const int NumLock = KEY_NUM_LOCK;
        static const int ScrollLock = KEY_SCROLL_LOCK;

    };

    class Mouse {
        public:
        static const int Left = MOUSE_BUTTON_LEFT;
        static const int Middle = MOUSE_BUTTON_MIDDLE;
        static const int Right = MOUSE_BUTTON_RIGHT;
        static const int Back = MOUSE_BUTTON_BACK;
        static const int Forward = MOUSE_BUTTON_FORWARD;
        static const int Side = MOUSE_BUTTON_SIDE;
    };




    NovaVec2 mousePos, mouseScroll;
    int lastKeyHit;
    

    NovaEvent() = default;

    void fetch();

};

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
    bool visible, canCollide;

    NovaObject4(float x, float y, float width, float height, float rotation): x(x), y(y),
    width(width), height(height), rotation(rotation),
    visible(true), canCollide(true){}
    NovaObject4() {}
};

// Class representing a rectangle
class NovaRectangle : public NovaObject4 {
    public:
    Color color; // Color of the rectangle

    // Constructor to initialize rectangle properties
    NovaRectangle(float x, float y, float width, float height, Color color, float rotation = 0.0f)
        : NovaObject4(x, y, width, height, rotation), color(color) {}
    NovaRectangle() {}
    
};

// Class representing a circle
class NovaCircle {
    public:
    float x, y; // Position
    float radius; // Radius of the circle
    Color color; // Color of the circle
    bool visible, canCollide;

    // Constructor to initialize circle properties
    NovaCircle(float x, float y, float radius, Color color): x(x), y(y), radius(radius), color(color) ,
        visible(true), canCollide(true) {}
    NovaCircle() {}
    
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

    NovaRenderImage() : path("") {}

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
    int rows, columns; // Number of rows and columns in the spritesheet
    int row, column; // Current frame position
    float x, y; // Position of the spritesheet

    // Constructor to initialize spritesheet properties
    NovaSpritesheet(std::string path, float x, float y, float frameWidth, float frameHeight):
    x(x), y(y), image(x, y, path), frameWidth(frameWidth), frameHeight(frameHeight),
    row(0), column(0){
        recalculateRows();
        recalculateColumns();
    }

    NovaSpritesheet() : frameWidth(0), frameHeight(0) {}

    // Recalculate rows and columns based on frame dimensions
    void recalculateRows();
    void recalculateColumns();

    // Render the current frame
    void render();

    void dispose() { image.dispose(); }
};

// Class representing an animation, derived from NovaSpritesheet
class NovaAnimation : public NovaSpritesheet {
    private:
    bool firstTime;

    protected:
    float frameTime; // Time per frame
    float maxFrameTime; // Maximum time per frame
    
    public:
    bool loop; // Whether the animation loops

    // Constructor to initialize animation properties
    NovaAnimation(std::string path, float x, float y, float frameWidth, float frameHeight):
    NovaSpritesheet(path, x, y, frameWidth, frameHeight), maxFrameTime(1.0f), loop(false),
    frameTime(maxFrameTime), firstTime(true){
        column = 0;
        row = 0;
    }

    inline void setMaxFrameTime(float maxFrameTime_){ maxFrameTime = maxFrameTime_; frameTime = maxFrameTime; }
    inline float getMaxFrameTime() { return maxFrameTime; }

    NovaAnimation() {}

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

    NovaSound() : path("") {}

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

    NovaMusic() {}

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






/********************************/
/** OBJECT CHAIN                */
/********************************/


class NovaObjectChain {
    public:
    std::vector<NovaObject4*> children;
    std::vector<NovaObjectChain*> subchains;
    NovaObject4* parent;
    Vector2 lastParentPos;

    NovaObjectChain(){}
    NovaObjectChain(NovaObject4* parent): parent(parent), children(), lastParentPos({parent->x, parent->y}){}

    void addChild(NovaObject4* child);
    void removeChild(int index);

    void addSubChain(NovaObjectChain* subchain);
    void removeSubChain(int index);

    void rechain();
    void rechainObject(NovaObject4* obj);
};


/********************************/
/** LOGGER                      */
/********************************/



class NovaLogger {
    public:
    
    static void log(std::string level, std::string text);
    static void info(std::string text);
    static void fatal(std::string text);
    static void error(std::string text);
    static void warn(std::string text);
    
};







/********************************/
/** SIGNAL                      */
/********************************/

class NovaSignal {
    public: 
    std::function<void(void)> callback;


    NovaSignal() = default;

    void emit();
};








