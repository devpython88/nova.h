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

// RECTANGLE

// Check collision between two rectangles
bool NovaRectangle::checkCollision(NovaRectangle other)
{
    return CheckCollisionRecs(Rectangle{x, y, width, height}, Rectangle{other.x, other.y, other.width, other.height});
}

// CIRCLE

// Check collision between a circle and a rectangle
bool NovaCircle::checkCollision(NovaRectangle other)
{
    return CheckCollisionCircleRec(Vector2{x, y}, radius, Rectangle{other.x, other.y, other.width, other.height});
}

// Check collision between two circles
bool NovaCircle::checkCollision(NovaCircle other)
{
    return CheckCollisionCircles(Vector2{x, y}, radius, Vector2{other.x, other.y}, other.radius);
}

// IMAGE

// Check collision between two images
bool NovaRenderImage::checkCollision(NovaRenderImage image)
{
    return CheckCollisionRecs(Rectangle{x, y, width, height}, Rectangle{image.x, image.y, image.width, image.height});
}

// Check collision between an image and a circle
bool NovaRenderImage::checkCollision(NovaCircle circle)
{
    return circle.checkCollision(NovaRectangle(x, y, width, height, WHITE));
}

// Check collision between an image and a rectangle
bool NovaRenderImage::checkCollision(NovaRectangle rectangle)
{
    return rectangle.checkCollision(NovaRectangle(x, y, width, height, WHITE));
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
            column * frameWidth,
            row * frameHeight,
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

// Play the animation by updating the frame
void NovaAnimation::play()
{
    if ((frameTime -= GetFrameTime()) <= 0.0f){
        frameTime = maxFrameTime;
        column++;
        if (column >= columns && loop){
            column = 0;
            return;
        }

        column = columns - 1;
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
