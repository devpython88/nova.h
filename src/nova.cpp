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
