
#include "nova.h"

// Check if the window is open
bool NovaWindow::open()
{
    return !WindowShouldClose();
}

// Start drawing and set up 2D camera mode
void NovaWindow::start()
{
    BeginDrawing();
    BeginMode2D(camera);
}

// Switch to UI mode (end 2D camera mode)
void NovaWindow::uiMode()
{
    EndMode2D();
}

// End drawing and clean up
void NovaWindow::end()
{
    EndMode2D();
    EndDrawing();
}

// Center the camera on a specific position
void NovaWindow::centerCamera(float x, float y)
{
    camera.target.x = x - (GetScreenWidth() / 2);
    camera.target.y = y - (GetScreenHeight() / 2);
}

// Get the camera's target position
Vector2 *NovaWindow::target()
{
    return &camera.target;
}

// Get the camera's zoom level
float NovaWindow::getCameraZoom()
{
    return camera.zoom;
}

// Set the camera's zoom level
void NovaWindow::setCameraZoom(float zoom)
{
    camera.zoom = zoom;
}

// Set the camera's rotation
void NovaWindow::setCameraRotation(float rotation)
{
    camera.rotation = rotation;
}

// Get the camera's rotation
float NovaWindow::getCameraRotation()
{
    return camera.rotation;
}

NovaAxis NovaWindow::axis()
{
    return NovaAxis(width, height);
}

// RENDER DEVICE

// Fill the screen with a specific color
void NovaRenderDevice::fill(Color color)
{
    ClearBackground(color);
}

// Draw a rectangle with specified dimensions and color
void NovaRenderDevice::rect(float left, float top, float width, float height, Color color)
{
    DrawRectangle(left, top, width, height, color);
}

// Draw a rectangle using a NovaRectangle object
void NovaRenderDevice::rect(NovaRectangle rect)
{
    DrawRectanglePro(Rectangle{rect.x, rect.y, rect.width, rect.height}, Vector2{rect.width / 2, rect.height / 2}, rect.rotation, rect.color);
}

// Draw a circle with specified center, radius, and color
void NovaRenderDevice::circle(float centerX, float centerY, float radius, Color color)
{
    DrawCircle(centerX, centerY, radius, color);
}

// Draw a circle using a NovaCircle object
void NovaRenderDevice::circle(NovaCircle circle)
{
    DrawCircle(circle.x, circle.y, circle.radius, circle.color);
}

void NovaRenderDevice::line(float x1, float y1, float x2, float y2, Color c)
{
    DrawLine(x1, y1, x2, y2, c);
}

void NovaRenderDevice::point(float x, float y, Color c)
{
    DrawLine(x, y, x, y, c);
}

void NovaRenderDevice::poly(float x, float y, float sides, float radius, Color c, float rotation)
{
    DrawPoly(Vector2{x, y}, sides, radius, rotation, c);
}

// Draw an image with rotation and position
void NovaRenderDevice::image(NovaRenderImage image)
{
    DrawTextureEx(image.texture, Vector2{image.x, image.y}, image.rotation, 1.0f, WHITE);
}

// Check if an image is loaded
bool NovaRenderDevice::imageLoaded(NovaRenderImage image)
{
    return image.texture.id == 0;
}

// Set the frame rate limit
void NovaRenderDevice::framerateLimit(int limit)
{
    SetTargetFPS(limit);
}

// Get the time elapsed since the last frame
float NovaRenderDevice::deltaTime()
{
    return GetFrameTime();
}

// TEXT

// Draw text on the screen
void NovaRenderDevice::text(std::string text, float x, float y, int fontSize, Color color)
{
    DrawText(text.c_str(), x, y, fontSize, color);
}

bool NovaRenderDevice::checkCollision(NovaObject4 obj, NovaObject4 obj2)
{
    return CheckCollisionRecs(Rectangle{obj.x, obj.y, obj.width, obj.height}, Rectangle{obj2.x, obj2.y, obj2.width, obj2.height});
}

bool NovaRenderDevice::checkCollision(NovaObject4 obj, NovaCircle circ)
{
    return CheckCollisionCircleRec(Vector2{circ.x, circ.y}, circ.radius, Rectangle{obj.x, obj.y, obj.width, obj.height});
}

// SPRITESHEET

// Recalculate the number of rows in the spritesheet
void NovaSpritesheet::recalculateRows()
{
    rows = image.height / frameHeight;
}

// Recalculate the number of columns in the spritesheet
void NovaSpritesheet::recalculateColumns()
{
    columns = image.width / frameWidth;
}

// Render the current frame of the spritesheet
void NovaSpritesheet::render()
{
    DrawTexturePro(
        image.texture,
        Rectangle{
            frameWidth * column,
            frameHeight * row,
            frameWidth,
            frameHeight
        },
        Rectangle{
            x,
            y,
            frameWidth,
            frameHeight
        },
        Vector2{frameWidth / 2, frameHeight / 2},
        image.rotation,
        WHITE
    );
}

// INPUT

// Check if a key was pressed
bool NovaInputDevice::keyHit(int key)
{
    return IsKeyPressed(key);
}

// Check if a key is being held down
bool NovaInputDevice::keyHeld(int key)
{
    return IsKeyDown(key);
}

// Check if a key was released
bool NovaInputDevice::keyUp(int key)
{
    return IsKeyUp(key);
}

// Check if a mouse button was pressed
bool NovaInputDevice::mouseButtonHit(int btn)
{
    return IsMouseButtonPressed(btn);
}

// Check if a mouse button is being held down
bool NovaInputDevice::mouseButtonHeld(int btn)
{
    return IsMouseButtonDown(btn);
}

// Check if a mouse button was released
bool NovaInputDevice::mouseButtonUp(int btn)
{
    return IsMouseButtonUp(btn);
}

bool NovaInputDevice::mouseHover(float left, float top, float width, float height)
{
    NovaRectangle hitbox(GetMouseX(), GetMouseY(), 1, 1, RED);

    return NovaRenderDevice::checkCollision(hitbox, NovaRectangle(left, top, width, height, RED));
}

bool NovaInputDevice::mouseClick(float left, float top, float width, float height)
{
    return NovaInputDevice::mouseHover(left, top, width, height) && NovaInputDevice::mouseButtonHeld(MOUSE_BUTTON_LEFT);
}

// Get the mouse scroll wheel movement
float NovaInputDevice::getScroll()
{
    return GetMouseWheelMove();
}

// Get the mouse scroll wheel movement as an integer
int NovaInputDevice::getScrollEx()
{
    return (int) (std::round(GetMouseWheelMove()));
}

// BACK TO SPRITESHEET
void NovaAnimation::play()
{
    if (firstTime){
        firstTime = false;
        column = 0;
    }

    if ((frameTime -= GetFrameTime()) <= 0.0f){
        frameTime = maxFrameTime;
        if (column < columns - 1){
            column++;
        } else if (loop && column >= columns - 1){
            column = 0;
        }
    }    
}


// AUDIO

// Set the sound volume using an integer percentage
void NovaSound::volume(int volume)
{
    SetSoundVolume(sound, ((float) volume) / 100.0f); // Convert integer to valid 1.0f volume
}

// Set the sound volume using a float value
void NovaSound::volume(float volume)
{
    if (volume > 1.0f || volume < 0.0f){
        throw new std::runtime_error("Sound volume mustn't be over 1.0f or below 0.0f");
    }

    SetSoundVolume(sound, volume);
}

// Check if the sound is loaded
bool NovaSound::loaded()
{
    return IsSoundValid(sound);
}

// Play the sound if it's not already playing
void NovaSound::play()
{
    if (!IsSoundPlaying(sound)){
        PlaySound(sound);
    }
}

// MUSIC

// Set the music volume using an integer percentage
void NovaMusic::volume(int volume)
{
    SetMusicVolume(music, volume / 100.0f);
}

// Set the music volume using a float value
void NovaMusic::volume(float volume)
{
    SetMusicVolume(music, volume);
}

// Update the music stream and handle looping
void NovaMusic::update()
{
    UpdateMusicStream(music);
    if (loop && !IsMusicStreamPlaying(music)){
        PlayMusicStream(music);
    }
}

// Play the music stream
void NovaMusic::play()
{
    PlayMusicStream(music);
}

bool NovaBinding::held()
{
    if (type == KEYBIND) return IsKeyDown(code);

    return IsMouseButtonDown(code);
}

bool NovaBinding::hit()
{
    if (type == KEYBIND) return IsKeyPressed(code);

    return IsMouseButtonPressed(code);
}

bool NovaBinding::up()
{
    if (type == KEYBIND) return IsKeyUp(code);

    return IsMouseButtonUp(code);
}

void NovaInputManager::bindKey(std::string name, int code)
{
    NovaBinding bind(NovaBinding::KEYBIND, code);
    bindings[name] = bind;
}

void NovaInputManager::bindMouse(std::string name, int code)
{
    NovaBinding bind(NovaBinding::MOUSEBIND, code);
    bindings[name] = bind;
}

bool NovaInputManager::held(std::string name)
{
    auto it = bindings.find(name);
    if (it != bindings.end()){
        return bindings[name].held();
    }
    return false;
}

bool NovaInputManager::hit(std::string name)
{
    auto it = bindings.find(name);
    if (it != bindings.end()){
        return bindings[name].hit();
    }
    return false;
}

bool NovaInputManager::up(std::string name)
{
    auto it = bindings.find(name);
    if (it != bindings.end()){
        return bindings[name].up();
    }
    return false;
}

int NovaRandomDevice::randomInt(int s, int e)
{
    // Distributor
    std::uniform_int_distribution<> dist(s, e);

    return dist(gen);
}

float NovaRandomDevice::randomFloat(float s, float e)
{
    // Float distributor
    std::uniform_real_distribution<> dist(s, e);

    return dist(gen);
}

int NovaRandomDevice::randomIndex(std::string str)
{
    // Get start
    int start = 0;
    
    // Get end
    int end = str.size() - 1;

    return randomInt(start, end);
}


/********************************/
/** OBJECT CHAIN                */
/********************************/

void NovaObjectChain::addChild(NovaObject4 *child)
{
    children.push_back(child);
}

void NovaObjectChain::removeChild(int index)
{
    children.erase(children.begin() + index);
}

void NovaObjectChain::addSubChain(NovaObjectChain *subchain)
{
    if (this == subchain){
        throw std::runtime_error("Cannot add chain as subchain to itself");
    }
    subchains.push_back(subchain);
}

void NovaObjectChain::removeSubChain(int index)
{
    subchains.erase(subchains.begin() + index);
}

void NovaObjectChain::rechain()
{
    for (NovaObject4* obj : children){
        // Reposition object
        rechainObject(obj);
    }


    // Handle subchains
    for (NovaObjectChain* chain : subchains){
        rechainObject(chain->parent);
        chain->rechain();
    }

    // Update position
    lastParentPos = Vector2{parent->x, parent->y};
}

void NovaObjectChain::rechainObject(NovaObject4 *obj)
{
    // Get delta
    float deltaX = parent->x - lastParentPos.x;
    float deltaY = parent->y - lastParentPos.y;
    
    // Move the object
    obj->x += deltaX;
    obj->y += deltaY;
}


// Nova logger


void NovaLogger::log(std::string level, std::string text)
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowc = std::chrono::system_clock::to_time_t(now);

    std::string out;
    
    out += "[";
    out += std::ctime(&nowc);
    out.pop_back();
    out += "]";

    out += "::";
    out += level;
    out += "::> ";
    out += text;

    std::cout << out << "\n";
}

void NovaLogger::info(std::string text)
{
    log("info", text);
}

void NovaLogger::fatal(std::string text)
{
    log("fatal", text);
}
void NovaLogger::error(std::string text)
{
    log("error", text);
}
void NovaLogger::warn(std::string text)
{
    log("warn", text);
}