## This is a complete guide to `nova.h`

### It goes over all of nova's constants, variables, functions and classes


## Table of contents

> NOTE: v1.2 has deprecated the old .checkCollision methods for all objects, Set to be removed in 1.5
> Use NovaRenderDevice::checkCollision(NovaObject4, NovaObject4/NovaCircle) instead.

## Hot (new) 🔥

- [Randomization](#novarandomdevice)
- [Object Base Class](#novaobject4)

------------------------------------------------------------------

- [Window initialization](#window-initialization)
- [Rendering and Game loop](#rendering-and-game-loop)
    - [Standalone shapes](#standalone-shapes)
    - [Collision](#collision)
- [Images](#images)
- [Animated Images](#animated-images)
    - [NovaSpritesheet](#novaspritesheet)
    - [NovaAnimation](#novaanimation)
- [Camera](#camera)
- [Audio](#audio)
    - [Sounds](#sounds)
    - [Music](#music)
- [Keyboard and Mouse](#keyboard-and-mouse)
- [Input Manager](#input-manager)

## Window initialization

To create a window in nova.h, You first need to import the nova.h header.
```cpp
#include <nova.h>

int main(){
    return 0;
}
```

In the main function, You have to create a NovaWindow instance.
NovaWindow has two constructors:
- NovaWindow(): Creates a 640x480 window with title "Game"
- NovaWindow(width, height, title): Creates a `width`x`height` window with title `title`

NovaWindow automatically closes so you don't need to manually handle events

After this, You can compile the program:
`g++ -o mygame mygame.cpp -lraylib -lnova`
And run it. But wait.. Why did the window only show up for a fraction of a second?
Well you'll see why in [Rendering and Game loop](#rendering-and-game-loop)


## Rendering and Game loop
The reason the window only shows up for a tiny amount of time is because there is no game loop.
So lets create one shall we?

Add these lines after creating the window instance:
```cpp
while (window.open()){
    window.start(); // Start frame
    NovaRenderDevice::fill(WHITE); // Clears the screen with the color white
    window.end(); // End frame
}
```

This snippet creates a basic game loop that fills every frame with the color `WHITE`
> If you want to change the framerate, You can do so with `NovaRenderDevice::framerate(int fps)`
> If you want to get the delta time (frame time), You can do so with `NovaRenderDevice::deltaTime()`

Lets actually draw some shapes.
NovaRenderDevice has `Immediate Drawing Functions`, These function directly take the shape properties (e.g, x, y, height) and draw the shape.
Which means you don't have to use shape classes, But there are still shape classes.

This snippets draws a rectangle, Put it after filling the screen in the main loop.
You can adjust the values as needed
```cpp
//                     X   Y   W   H   COLOR
NovaRenderDevice::rect(20, 20, 50, 50, RED)
```

You can also use `::circle(float x, float y, float radius, Color color)` to draw a circle.

### Standalone shapes
Standalone shapes are shapes that are instances of a shape class.

Here are the current shapes:
- NovaRectangle(float, float, float, float, Color)
    > Can be drawn with `NovaRenderDevice::rect(NovaRectangle)`
- NovaCircle(float, float, float, Color)
    > Can be drawn with `NovaRenderDevice::circle(NovaCircle)`

### Collision
NovaRectangle has only one function that can collide with a rectangle
NovaCircle has two overloaded functions that can collide with a rectangle and a circle
NovaRenderImage has three overloaded functions that can collide with a rectangle and a circle and a NovaRenderImage

### Want to draw images, Checkout [Images](#images)

## Images
In nova.h, Images are drawn using NovaRenderImage
constructor: NovaRenderImage(float x, float y, std::string imagePath)

After loading a image, You can use `NovaRenderDevice::image(NovaRenderImage)` to draw
or `::imageLoaded(NovaRenderImage)` to see if it is loaded or not.
Images are automatically unloaded when game ends.

For animations, Checkout [Animations](#animated-images)

## Animated Images
To animate a image, You have to use spritesheets.
But most libraries like: Raylib, SDL3, SFML only provide ways to cutout a frame from an animation.

But nova.h has two classes, one for manual animations and one for automatic.

### NovaSpritesheet
Constructor: (std::string sheetPath, float x, float y, float frameWidth, float frameHeight)

The class has a public NovaRenderImage image internally.
You can use that to get things like if its loaded or not, or the width and height.

If you changed the image, You can use the NovaSpritesheet's `.recalculateRows` and `.recalculateColumns` function to recalculate the frames.

You can use its .row and .column properties to manage row and column (in 0, 1, 2 not multiples of the frameSize)

You can use its custom .render function to draw the current frame.

.rows and .columns properties are used to get the amount of rows and columns

### NovaAnimation
This class is a subclass of `NovaSpritesheet`
Meaning it also has a internal image, and row and column properties

How to make a valid animation:
Step 1. Create a instance
```cpp
NovaAnimation anim("Player.png", 20, 20, 8, 8);
```

Step 2. Set frame time (in seconds)
```cpp
// Frame time determens how much time it takes for the next frame to appear
anim.frameTime = 1.5f;
```

Step 3. (Optionally) Set the looping property
```cpp
anim.loop = true;
```

Step 4. Call `.play` before drawing logic
Step 5. Call `.render` in drawing logic

## Camera
nova.h's NovaWindow has a integrated camera.
When you call `.start` it starts the camera.
To enter UI mode (or end the camera mode in other words), You call the `.uiMode()` function

If you don't call it, `.end()` automatically does

To modify the camera's target, You can use the `Vector2*` pointer that `.target()` returns.
WARNING: This must only be used when you want to `modify` the camera target not `set` the camera target

To center a camera at a point, Offsets must be applied, So to fix that i added a `.centerCamera(float x, float y)` function.

To get or set the zoom, use `.setZoom(float)` and `.getZoom()`
To get or set the rotation, use `.setRotation(float)` and `.getRotation()`


## Audio

### Sounds
NovaSound can provide you with sound functions.
Constructor: `(std::string path)`
There are two volume overloads:
- volume(int): Volume between 0 and 100
- volume(float): Volume between 0f and 1f

To play the sound, call `.play()`

Sounds are automatically unloaded()


### Music
NovaMusic is for .mp3 music's

Constructor: `(std::string path)`

Volume functions are the same as sound

To play the music, call `.play()`

Modify its `.loop` property as needed
Make sure to call its `.update` function in game loop before drawing logic

## Keyboard and Mouse
NovaInputDevice is used for input.
Nova uses raylib constants (e.g, KEY_D, MOUSE_BUTTON_RIGHT)

- `NovaInputDevice::keyHit(int)`: Key pressed once
- `NovaInputDevice::keyHeld(int)`: Key held
- `NovaInputDevice::keyUp(int)`: Key not being pressed
- `NovaInputDevice::mouseButtonHit(int)`: Mouse pressed once
- `NovaInputDevice::mouseButtonHeld(int)`: Mouse held
- `NovaInputDevice::mouseButtonUp(int)`: Mouse not being pressed
- `int NovaInputDevice::getScrollEx()`: Get mouse scroll in integer
- `float NovaInputDevice::getScroll()`: Get mouse scroll in floating point.
- `NovaInputDevice::mouseHover(float x, float y, float width, float height)`: Mouse hovering the corresponding area
- `NovaInputDevice::mouseClick(float x, float y, float width, float height)`: Mouse clicking the corresponding area

## Input Manager
Nova has an INput manager
if you do not know wat an Input manager is, basically it is a little library of key bindings
and mouse bindings.

How to use:
Constructor: ()

Adding key binds: {instance}.bindKey(identifer: str, code: int)
Adding mouse binds: {instance}.bindMouse(identifier: str, code: int)

Checking bindings:
`.held(identifer)`: Check if binding held
`.hit(identifer)`: Check if binding hit
`.up(identifer)`: Check if binding not hit

## Axis
NovaAxis allows for positioning controls, It allows you to easily check if a position is at somewhere.
Example: Check if this position is top left

Constructor: Private, Use window.axis() to get the window axis

Functions:
`.atTop(y)`: Checks if y is at top
`.atLeft(x)`: Checks if x is at left
`.atBottom(y)`: Checks if y is at bottom
`.atRight(x)`: check if x is at right
`.atMiddle(x)`: Checks if x is middle
`.atMiddleY(y)`: Checks if y is at middle
`.overflowX(x)`: Checks if x is beyond the window boundaries (both sides)
`.overflowY(y)`: Checks if y is beyond the window boundaries (both sides)
`.overflow(x, y)`: Checks if either one of the positions, or both of the positions are beyond the window boundaries



# Hot (new) 🔥

## NovaRandomDevice
This class allows for easy randomization.
Constructor: ()

Methods (not static):
`.randomInt(start, end)`: Get random integer
`.randomFloat(start, end)`: Get random float
`.randomIndex(std::string)`, `.randomIndex<T>(std::vector<T>)`: Get random index from vector or string
`.randomItem<T>(std::vector<T>)`: Get random item
`std::vector<T> shuffle<T>(std::vector<T> src, std::vector<T> vals)`: Puts a random element from values in each non-empty slot of `src`

# NovaObject4
Base class for all objects (excluding NovaCircle)

Has `.x`, `.y`, `.width`, `.height`

No methods