
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
    if (integratedCamera) BeginMode2D(camera);
}

// Switch to UI mode (end 2D camera mode)
void NovaWindow::uiMode()
{
    if (integratedCamera) EndMode2D();
}

// End drawing and clean up
void NovaWindow::end()
{
    if (integratedCamera) EndMode2D();
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




// CAMERA



NovaVec2 NovaCamera::getViewportSize(){
    return NovaVec2(GetScreenWidth() / zoom, GetScreenHeight() / zoom);
}

void NovaCamera::start(){
    refreshCamera();

    shakeCamera();

    BeginMode2D(camera);
}

void NovaCamera::shakeCamera(){
    // Shake
    
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - timeWhenShake;
    if (elapsed.count() < .05f) return;

    if (!shaking && currentShakePower > 0.0f){
        currentShakePower *= 0.9f;
    }


    timeWhenShake = now;

    // Which axis to shake on
    int axis = GetRandomValue(1, 2);
    if (axis == 1){
        int position = GetRandomValue(1, 2);
        if (position == 1) camera.target.x -= currentShakePower;
        if (position == 2) camera.target.x += currentShakePower;
    } else {
        int position = GetRandomValue(1, 2);
        if (position == 1) camera.target.y -= currentShakePower;
        if (position == 2) camera.target.y += currentShakePower;
    }
}

void NovaCamera::end(){
    EndMode2D();
}

NovaVec2 NovaCamera::getViewportRelativePosition(float x, float y){
    return NovaVec2(x / zoom, y / zoom);
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
    if (!rect.visible) return;
    DrawRectanglePro(Rectangle{rect.x, rect.y, rect.width, rect.height}, Vector2{rect.origin.x, rect.origin.y}, rect.rotation, rect.color);
}

// Draw a circle with specified center, radius, and color
void NovaRenderDevice::circle(float centerX, float centerY, float radius, Color color)
{
    DrawCircle(centerX, centerY, radius, color);
}

// Draw a circle using a NovaCircle object
void NovaRenderDevice::circle(NovaCircle circle)
{
    if (!circle.visible) return;
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
    if (!image.visible) return;

    float calculatedWidth = image.width;
    float calculatedHeight = image.height;

    if (image.flipX) calculatedWidth *= -1;
    if (image.flipY) calculatedHeight *= -1;

    DrawTexturePro(
        image.host->rTexture,
        Rectangle{0, 0, calculatedWidth, calculatedHeight},
        Rectangle{image.x, image.y, image.width * image.scale.x, image.height * image.scale.y},
        Vector2{image.origin.x, image.origin.y,},
        image.rotation,
        WHITE
    );
}

void NovaRenderDevice::texture(NovaRawTexture texture, float x, float y, Color tint)
{
    DrawTexture(texture.rTexture, x, y, tint);
}

// Check if an image is loaded
bool NovaRenderDevice::imageLoaded(NovaRenderImage image)
{
    return image.host->getTextureID() != 0;
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
    if (!obj.canCollide || !obj2.canCollide || obj.zIndex != obj2.zIndex) return false;
    return CheckCollisionRecs(Rectangle{obj.x, obj.y, obj.width, obj.height}, Rectangle{obj2.x, obj2.y, obj2.width, obj2.height});
}

bool NovaRenderDevice::checkCollision(NovaObject4 obj, NovaCircle circ)
{
    if (!circ.canCollide || !obj.canCollide) return false;
    return CheckCollisionCircleRec(Vector2{circ.x, circ.y}, circ.radius, Rectangle{obj.x, obj.y, obj.width, obj.height});
}


bool NovaRenderDevice::checkCollisionEx(NovaSpritesheet sheet, NovaObject4 obj)
{
    NovaObject4 sheetToObj = sheet;
    sheetToObj.width = sheet.frameWidth;
    sheetToObj.height = sheet.frameHeight;

    return checkCollision(
        sheetToObj,
        obj    
    );
}

bool NovaRenderDevice::checkCollisionEx(NovaSpritesheet sheet, NovaSpritesheet sheet2)
{
    NovaObject4 sheetToObj = sheet2;
    sheetToObj.width = sheet.frameWidth;
    sheetToObj.height = sheet.frameHeight;

    return checkCollisionEx(
        sheet,
        sheetToObj
    );
}

void NovaRenderDevice::gridLines(NovaVec2 cellSize, NovaVec2 cells, Color color)
{
    float lineWidth = cellSize.x * cells.x; // This way, 16 * 3 = 48
    float lineHeight = cellSize.y * cells.y;

    float lineStartY = 0.0f;
    
    for (int i = 0; i < cells.y; i++){
        DrawLine(0.0f, lineStartY, lineWidth, lineStartY, color);
        lineStartY += cellSize.y;
    }
    
    float lineStartX = 0.0f;
    
    for (int i = 0; i < cells.x; i++){
        DrawLine(lineStartX, 0.0f, lineStartX, lineHeight, color);
        lineStartX += cellSize.x;
    }
}

void NovaRenderDevice::gridBoxes(NovaVec2 cellSize, NovaVec2 cells, Color lineColor, Color boxColor)
{
    
    float boxX = 0.0f;
    float boxY = 0.0f;
    float boxWidth = cells.x * cellSize.x;
    float boxHeight = cells.y * cellSize.y;
    
    rect(boxX, boxY, boxWidth, boxHeight, boxColor);
    gridLines(cellSize, cells, lineColor); // draw the grid lines after the box to make it look like individual cells
}


// UI

// Initialize global ui properties

bool NovaRenderDevice::useDefaultFont = true;
NovaVec2 NovaRenderDevice::padding = NovaVec2(10, 10);
Font NovaRenderDevice::font = {};
std::string NovaRenderDevice::fontName = "";
int NovaRenderDevice::spacing = 10;

// Buttons

UIEvent NovaRenderDevice::uiButton(std::string text, NovaVec2 position, Color background, Color foreground, int fontSize)
{
    // Return value
    UIEvent returnValue = UIEvent::None;
    

    // Get Button size
    NovaVec2 buttonSize = getTextPixelSize(text, fontSize);
    // Add padding
    buttonSize += padding * NovaVec2(2, 2);

    // Handle background colors
    NovaColor resultColor(background.r, background.g, background.b, background.a);

    // Handle hover
    if (NovaInputDevice::mouseHover(position.x, position.y, buttonSize.x, buttonSize.y)){
        returnValue = UIEvent::Hover;
        // Brighten color
        resultColor.brighten(20, 20, 20, 0);
    }

    // Handle click
    if (NovaInputDevice::mouseClick(position.x, position.y, buttonSize.x, buttonSize.y)){
        returnValue = UIEvent::Click;
        // Brighten color
        resultColor.brighten(40, 40, 40, 0);
    }
    

    // Get text display position
    NovaVec2 displayPosition(position);
    displayPosition += padding;

    // Draw Button
    rect(position.x, position.y, buttonSize.x, buttonSize.y, Color{resultColor.r, resultColor.g, resultColor.b, resultColor.a});

    // Draw Text (default font)
    if (useDefaultFont) DrawText(text.c_str(), displayPosition.x, displayPosition.y, fontSize, foreground);

    // Draw text (custom font)
    else DrawTextEx(font, text.c_str(), Vector2{displayPosition.x, displayPosition.y}, fontSize, spacing, WHITE);

    // Return button event
    return returnValue;
}

void NovaRenderDevice::uiTextInput(std::string *target, NovaVec2 position, Color background, Color foreground, int fontSize, bool focused)
{

    // Get input

    if (focused){
        char c = GetCharPressed();

        if ((c >= 32) && (c <= 126)){
            *target += c;
        }

        // Handle backspace
        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && target->size() >= 1){
            *target = target->substr(0, target->size() - 1); // -1 = 0 indexed length, so -2 = length without last char
        }
    }
    
    // Get entry size
    NovaVec2 entrySize = getTextPixelSize(*target, fontSize);
    // Add padding
    entrySize += padding * NovaVec2(2, 2);

    // Make a default width
    entrySize.x = std::max(225, (int) entrySize.x); // Make it so when there are less characters, the entry fixates to 225 width

    // Handle background colors
    NovaColor resultColor(background.r, background.g, background.b, background.a);


    // Handle hover
    if (NovaInputDevice::mouseHover(position.x, position.y, entrySize.x, entrySize.y)){
        // Brighten color
        resultColor.brighten(20, 20, 20, 0);
    }
    

    // Get text display position
    NovaVec2 displayPosition(position);
    displayPosition += padding;

    // Draw Entry
    rect(position.x, position.y, entrySize.x, entrySize.y, Color{resultColor.r, resultColor.g, resultColor.b, resultColor.a});

    // Draw Text (default font)

    if (useDefaultFont) DrawText(target->c_str(), displayPosition.x, displayPosition.y, fontSize, foreground);

    // Draw Text (custom font)
    else DrawTextEx(font, target->c_str(), Vector2{displayPosition.x, displayPosition.y}, fontSize, spacing, WHITE);


    // Draw line cursor

    if (focused){
        // draw
        DrawText("|", displayPosition.x + getTextPixelSize(*target, fontSize).x, displayPosition.y, fontSize, WHITE);
    }
}

NovaVec2 NovaRenderDevice::getTextPixelSize(std::string text, int fontSize)
{
    if (useDefaultFont) return NovaVec2(MeasureText(text.c_str(), fontSize), fontSize);
    return NovaVec2(MeasureTextEx(font, text.c_str(), fontSize, spacing).x, fontSize);
}

NovaVec2 NovaRenderDevice::getWidgetSize(std::string text, int fontSize)
{
    NovaVec2 size = getTextPixelSize(text, fontSize);
    size += padding * NovaVec2(2, 2);
    return size;
}

// LABEL


void NovaRenderDevice::uiLabel(std::string text, NovaVec2 pos, int fontSize, Color color)
{
    if (useDefaultFont){
        DrawText(text.c_str(), pos.x, pos.y, fontSize, color);
        return;
    }

    DrawTextEx(font, text.c_str(), Vector2{pos.x, pos.y}, fontSize, spacing, color);
}

// SPRITESHEET

// Recalculate the number of rows in the spritesheet
void NovaSpritesheet::recalculateRows()
{
    rows = height / frameHeight;
}

// Recalculate the number of columns in the spritesheet
void NovaSpritesheet::recalculateColumns()
{
    columns = width / frameWidth;
}

// Render the current frame of the spritesheet
void NovaSpritesheet::render()
{
    if (!visible) return;

    float calculatedWidth = frameWidth;
    float calculatedHeight = frameHeight;

    if (flipX) calculatedWidth *= -1;
    if (flipY) calculatedHeight *= -1;

    DrawTexturePro(
        host->rTexture,
        Rectangle{
            frameWidth * column,
            frameHeight * row,
            calculatedWidth,
            calculatedHeight
        },
        Rectangle{
            x,
            y,
            frameWidth * scale.x,
            frameHeight * scale.y
        },
        Vector2{origin.x, origin.y},
        rotation,
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
    return NovaInputDevice::mouseHover(left, top, width, height) && NovaInputDevice::mouseButtonHit (MOUSE_BUTTON_LEFT);
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
        frameTime = framerate;
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


// Color

void NovaColor::brighten(UnsignedInt8 rVal, UnsignedInt8 gVal, UnsignedInt8 bVal, UnsignedInt8 aVal){
    r = std::min(255, r + rVal);
    g = std::min(255, g + gVal);
    b = std::min(255, b + bVal);
    a = std::min(255, a + aVal);
}

void NovaColor::darken(UnsignedInt8 rVal, UnsignedInt8 gVal, UnsignedInt8 bVal, UnsignedInt8 aVal){
    r = std::max(0, r - rVal);
    g = std::max(0, g - gVal);
    b = std::max(0, b - bVal);
    a = std::max(0, a - aVal);
}

    

// Randomization

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

std::string NovaLogger::getTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowc = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&nowc);
}

void NovaLogger::log(std::string level, std::string text)
{

    std::string out;
    
    out += "[";
    out += getTime();
    out.pop_back();
    out += "]";

    out += "::";
    out += level;
    out += "::> ";
    out += text;

    std::cout << out << "\n";
}

std::string NovaLogger::getLogFormat(std::string level, std::string text)
{
    
    std::string out;
    
    out += "[";
    out += getTime();
    out.pop_back();
    out += "]";

    out += "::";
    out += level;
    out += "::> ";
    out += text;

    return out;
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



// Nova signal


void NovaSignal::emit()
{
    callback();
}

void NovaSignal::bindTo(std::function<bool(void)> condition)
{
    bindedCondition = condition;
}

void NovaSignal::emitOnCondition()
{
    if (bindedCondition) if (bindedCondition() && callback) callback(); // Inlining stat +10
}

// Nova event

void NovaEvent::fetch()
{
    mousePos = NovaVec2(GetMouseX(), GetMouseY());
    Vector2 mScroll_ = GetMouseWheelMoveV();
    mouseScroll = NovaVec2(mScroll_.x, mScroll_.y);
    lastKeyHit = GetKeyPressed();
}

NovaVec2 NovaGrid::snap(float x, float y)
{
    return NovaVec2(((x + (cellSize.x / 2)) / cellSize.x) * cellSize.x,
                        ((y + (cellSize.y / 2)) / cellSize.y) * cellSize.y);
}


// NOVA OBJECT 4


void NovaObject4::move(NovaVec2 delta)
{
    x += delta.x;
    y += delta.y;
}

void NovaObject4::move(float deltaX, float deltaY)
{
    x += deltaX;
    y += deltaY;
}

void NovaObject4::roam(float speed, NovaRandomDevice* rd)
{
    float deltaX = 0.0f;
    float deltaY = 0.0f;

    if (rd->randomInt(0, 1) == 1){ // move horizontally 
        deltaX = std::round(rd->randomFloat(-speed, speed) / speed) * speed;
    } else {
        deltaY = std::round(rd->randomFloat(-speed, speed) / speed) * speed;
    }

    move(deltaX, deltaY);
}

void NovaObject4::moveTo(NovaVec2 target, float speed)
{
    // Move in x axis 
    if (x < target.x) x += speed;
    if (x > target.x) x -= speed;

    // Move in y axis
    if (y < target.y) y += speed;
    if (y > target.y) y -= speed;
}

void NovaObject4::roamTo(NovaVec2 target, float speed, NovaRandomDevice *rd)
{
    int axis = rd->randomInt(1, 2); // 1 = x, 2 = y
    // Move in x axis 
    if (axis == 1){
        if (x < target.x) x += speed;
        if (x > target.x) x -= speed;
        return; // Exit function if moved in x axis
    }

    // Move in y axis
    if (y < target.y) y += speed;
    if (y > target.y) y -= speed;
}

void NovaObject4::cache()
{
    visible = false;
    canCollide = false;
}

void NovaObject4::grab()
{
    visible = true;
    canCollide = true;
}

void NovaObject4::updateMovement(){
    NovaVec2 dest(NovaVec2(x, y) + velocity);

    if (x < dest.x) x += acceleration.x;
    if (x > dest.x) x -= acceleration.x;
    if (y < dest.y) y += acceleration.y;
    if (y > dest.y) y -= acceleration.y;
}


// RAW TEXTURE

NovaVec2 NovaRawTexture::getSize()
{
    return NovaVec2(rTexture.width, rTexture.height);
}

int NovaRawTexture::getTextureID()
{
    return rTexture.id;
}

int NovaRawTexture::getMipmaps()
{
    return rTexture.mipmaps;
}

PopupEvent NovaPopup::show()
{
    if (!visible) return PopupEvent::Closed;

    // Get position for close button
    NovaVec2 closeButtonPosition((x + width) - 32, y);


    // Get text position
    NovaVec2 textPosition(x + 10, y + 10);

    // draw dialog
    NovaRenderDevice::rect(x, y, width, height, background);

    // Draw title
    NovaRenderDevice::text(title, textPosition.x, textPosition.y, 18, BLACK);

    // Draw close button
    if (NovaRenderDevice::uiButton("X", closeButtonPosition, RED, WHITE, 20) == UIEvent::Click){
        visible = false;
        return PopupEvent::Closed;
    } 
    
    return PopupEvent::Open;
}



// MENUS


MenuResult NovaMenu::show(){
    // Draw menu button and set opened to true if pressed
    auto result = NovaRenderDevice::uiButton(label, position, BLACK, WHITE, fontSize);
    if (result == UIEvent::Click){
        opened = !opened; // if false then becomes true, vice versa
    }

    // Draw Menu options if shown

    if (opened){
        return drawOptions();
    }

    // Return a failed option select
    return MenuResult{"", false};
}

MenuResult NovaMenu::drawOptions()
{
    NovaVec2 pos = dropdownPosition;
    std::string clicked = "";
    bool alreadyClicked = false;
    for (std::string option : options){
        auto result = NovaRenderDevice::uiButton(option, pos, BLACK, WHITE, fontSize);
        if (result == UIEvent::Click && !alreadyClicked){
            clicked = option;
            alreadyClicked = true;
        }
        pos.y += NovaRenderDevice::getWidgetSize(option, fontSize).y;
    }
    
    return MenuResult{clicked, alreadyClicked};
}









// Scenes



std::map<std::string, NovaScene*> NovaScenes::scenes = std::map<std::string, NovaScene*>();
std::string NovaScenes::current = "";

void NovaScenes::add(std::string sceneName, NovaScene* scene){
    scenes[sceneName] = scene;

    scene->load();

    if (current == "") current = sceneName; // Avoid corruption and errors
}

void NovaScenes::go(std::string sceneName){
    if (!has(sceneName)){
        throw new std::runtime_error("Scene does not exist: " + sceneName);
    }

    if (current != "") scenes[current]->unload();
    current = sceneName;
}

bool NovaScenes::has(std::string sceneName){
    return scenes.find(sceneName) != scenes.end();
}

void NovaScenes::remove(std::string sceneName){
    if (has(sceneName)){
        scenes[sceneName]->unload();
        delete scenes[sceneName];
    }
}

void NovaScenes::show(){
    if (!has(current)){
        throw new std::runtime_error("The current scene does not exist: " + current);
    }

    NovaScene* scene = scenes[current];
    scene->update(GetFrameTime());
    scene->draw();
}