#include "nova.h"

bool NovaWindow::open()
{
    return !WindowShouldClose();
}

void NovaWindow::start()
{
    BeginDrawing();
}

void NovaWindow::end()
{
    EndDrawing();
}

// RENDER DEVICE

void NovaRenderDevice::fill(Color color)
{
    ClearBackground(color);
}

void NovaRenderDevice::rect(float left, float top, float width, float height, Color color)
{
    DrawRectangle(left, top, width, height, color);
}

void NovaRenderDevice::rect(NovaRectangle rect)
{
    DrawRectanglePro(Rectangle{rect.x, rect.y, rect.width, rect.height}, Vector2{rect.width / 2, rect.height / 2}, rect.rotation, rect.color);
}

void NovaRenderDevice::circle(float centerX, float centerY, float radius, Color color)
{
    DrawCircle(centerX, centerY, radius, color);
}

void NovaRenderDevice::circle(NovaCircle circle)
{
    DrawCircle(circle.x, circle.y, circle.radius, circle.color);
}

void NovaRenderDevice::image(NovaRenderImage image)
{
    DrawTextureEx(image.texture, Vector2{image.x, image.y}, image.rotation, 1.0f, WHITE);
}

bool NovaRenderDevice::imageLoaded(NovaRenderImage image)
{
    return image.texture.id == 0;
}

void NovaRenderDevice::framerateLimit(int limit)
{
    SetTargetFPS(limit);
}

float NovaRenderDevice::deltaTime()
{
    return GetFrameTime();
}

// TEXT

void NovaRenderDevice::text(std::string text, float x, float y, int fontSize, Color color)
{
    DrawText(text.c_str(), x, y, fontSize, color);
}

// RECTANGLE

bool NovaRectangle::checkCollision(NovaRectangle other)
{
    return CheckCollisionRecs(Rectangle{x, y, width, height}, Rectangle{other.x, other.y, other.width, other.height});
}

// CIRCLE

bool NovaCircle::checkCollision(NovaRectangle other)
{
    return CheckCollisionCircleRec(Vector2{x, y}, radius, Rectangle{other.x, other.y, other.width, other.height});
}

bool NovaCircle::checkCollision(NovaCircle other)
{
    return CheckCollisionCircles(Vector2{x, y}, radius, Vector2{other.x, other.y}, other.radius);
}

// IMAGE

bool NovaRenderImage::checkCollision(NovaRenderImage image)
{
    return CheckCollisionRecs(Rectangle{x, y, width, height}, Rectangle{image.x, image.y, image.width, image.height});
}

bool NovaRenderImage::checkCollision(NovaCircle circle)
{
    return circle.checkCollision(NovaRectangle(x, y, width, height, WHITE));
}

bool NovaRenderImage::checkCollision(NovaRectangle rectangle)
{
    return rectangle.checkCollision(NovaRectangle(x, y, width, height, WHITE));
}

// SPRITESHEET

void NovaSpritesheet::recalculateRows()
{
    rows = image.height / frameHeight;
}

void NovaSpritesheet::recalculateColumns()
{
    columns = image.width / frameWidth;
}

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

bool NovaInputDevice::keyHit(int key)
{
    return IsKeyPressed(key);
}

bool NovaInputDevice::keyHeld(int key)
{
    return IsKeyDown(key);
}

bool NovaInputDevice::keyUp(int key)
{
    return IsKeyUp(key);
}

bool NovaInputDevice::mouseButtonHit(int btn)
{
    return IsMouseButtonPressed(btn);
}

bool NovaInputDevice::mouseButtonHeld(int btn)
{
    return IsMouseButtonDown(btn);
}

bool NovaInputDevice::mouseButtonUp(int btn)
{
    return IsMouseButtonUp(btn);
}

float NovaInputDevice::getScroll()
{
    return GetMouseWheelMove();
}

int NovaInputDevice::getScrollEx()
{
    return (int) (std::round(GetMouseWheelMove()));
}

// BACK TO SPRITESHEET

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

void NovaSound::volume(int volume)
{
    SetSoundVolume(sound, ((float) volume) / 100.0f); // Convert integer to valid 1.0f volume
}

void NovaSound::volume(float volume)
{
    if (volume > 1.0f || volume < 0.0f){
        throw new std::runtime_error("Sound volume mustn't be over 1.0f or below 0.0f");
    }

    SetSoundVolume(sound, volume);
}

bool NovaSound::loaded()
{
    return IsSoundValid(sound);
}

void NovaSound::play()
{
    if (!IsSoundPlaying(sound)){
        PlaySound(sound);
    }
}

// MUSIC

void NovaMusic::volume(int volume)
{
    SetMusicVolume(music, volume / 100.0f);
}

void NovaMusic::volume(float volume)
{
    SetMusicVolume(music, volume);
}

void NovaMusic::update()
{
    UpdateMusicStream(music);
    if (loop && !IsMusicStreamPlaying(music)){
        PlayMusicStream(music);
    }
}

void NovaMusic::play()
{
    PlayMusicStream(music);
}
