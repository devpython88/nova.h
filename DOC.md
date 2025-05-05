## This is a complete guide to `nova.h`

### It goes over all of nova's constants, variables, functions and classes

## Compilation

Nova now has dist-linux.sh
and dist-win32.bat

Both of them are versatile, You can choose your generator and its executable

Guide on how to compile:
1. Clone the repository
    `git clone https://github.com/devpython88/nova.h.git`
    `cd <name-of-directory-it-got-cloned-in>`
2. Run the corresponding file
    For macOS (Experimental) and Linux: `bash dist-linux.sh`
    For windows: `dist-win32.bat`
3. Finish
    Directories for macOS and Linux: `build-linx/dist/include` and `build-linx/dist/lib`
    For windows: `build/dist/include` and `build/dist/lib`


## Table of contents

> NOTE: v1.2 has deprecated the old .checkCollision methods for all objects, Set to be removed in 1.5
> Use NovaRenderDevice::checkCollision(NovaObject4, NovaObject4/NovaCircle) instead.

## Hot (new) 🔥

- [Nova Event](#novaevent)
- [Nova Signal](#novasignal-novah)
- [Nova Color](#novacolor)
- [Nova Types](#nova-types)
- (Updated) [Object Base Class](#novaobject4)

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
- [Randomization](#novarandomdevice)
- [Nova File](#novafileh)
- [NovaFS and Win32FS](#novafs--win32fs)
- [NovaObjectChain](#novaobjectchain)
- [NovaTypewriter](#novatypewriter-novastrh)
- [NovaTimer](#novatimer-novatimeh)
- [NovaVec](#novavec)
- [NovaStopwatch](#novastopwatch-novatimeh)
- [NovaFileWatcher](#novafilewatcher-novafileh)
- [NovaLogger](#novalogger-novah)
- [NovaJSON](#novajson-novajsonh)


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
All previous object collision functions were deprecated in v1.2 and now removed in v1.5
NovaRenderDevice has two function, both are checkCollision but one takes two objects, and the other takes a object and a circle

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
anim.setMaxFrameTime(2.0f);
anim.getMaxFrameTime();
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




## NovaRandomDevice
This class allows for easy randomization.
Constructor: ()

Methods (not static):
`.randomInt(start, end)`: Get random integer
`.randomFloat(start, end)`: Get random float
`.randomIndex(std::string)`, `.randomIndex<T>(std::vector<T>)`: Get random index from vector or string
`.randomItem<T>(std::vector<T>)`: Get random item
`std::vector<T> shuffle<T>(std::vector<T> src, std::vector<T> vals)`: Puts a random element from values in each non-empty slot of `src`

## NovaObject4
Base class for all objects (excluding NovaCircle)

Has `.x`, `.y`, `.width`, `.height`
This class also has a zIndex integer var. If you check for collision and the zindexes arent equal, it will return false.
Great for mechanics like terraria and blashpemouses back and forth system.

No methods


## `novafile.h`
Nova isn't just for game development.
You could also use it for things like Randomization, Integration into raylib

But now you can even use it for file operation.

This *MASSIVE* (low taper faddeee) update adds file operation.
That work without even filesystem.
Currently experimental, They are to be improved as the project continues
They are available in `novafile.h`.

`NovaFile`:
Constructor: (std::string pathWithoutExtension, std::string extension)

- `fullPath()`: Get path with extension (automatically handles empty extension)
- `close()`: Close file (NEEDED)
- `operator <<(std::string)`: Append line to `.contents` and to the file (no auto new line)

Static methods:
 
- `fetchContents(std::string path)`: Get file contents



## NovaFS & Win32FS

NovaFS (in `novafile.h`) is used for file system operations.


`NovaFS`:
- `mkdir(std::string path)` (Cross Platform): Create directory (Putting `/` on windows automatically gets handled)
- `rm(std::string path, bool force = false, bool recursive = false)` (macOS/POSIX): Remove a file/directory
- `cp(std::string path, bool force = false, bool recursive = false)` (macOS/POSIX): Copy a file/directory
- `mv(std::string path, bool force = false, bool recursive = false)` (macOS/POSIX): Move a file/directory



`NovaFS::Win32FS`:
- `rmdir(std::string path)`: Remove a directory recursively
- `copy(std::string path, std::string dest)`: Copy a file
- `move(std::string path, std::string dest)`: Move a file
- `xcopy(std::string path, std::string dest)`: Copy a Directory





## NovaObjectChain
Ever wanted hierarchy in game libraries? Welp, here it is

<b>How to use:</b>

First, create a NovaObjectChain object, The constructor requires a pointer to a parent object: 
`NovaObjectChain chain(&player);`

Next, add some children to the chain: 
`chain.addChild(&weapon);`

You can also add subchains to chains, Which is what makes this a hierarchy, a.k.a object tree: 
`chain.addSubChain(&subchain);`

To remove subchains or children, use `.removeSubChain` and `.removeChild`. Both of these assume you know the index of the object in the lists

And in the main loop, Make sure to call `chain.rechain()` to sync the children and subchains with the parent.
Note 1: If a subchains moves faster than the parent, it moves a little more faster because the parent is also constantly moving
Note 2: To move a child, You just use the object, You dont have to get the child from the chain, SImply use the child itself



## NovaTimer (novatime.h)
This class is for timers

<b>How to use:</b>

First, create a timer: `NovaTimer timer(<duration>)`
The duration is measured in seconds.

Then in the main loop, Use `.update` to update the timer
You can use `.elapsed()` to get the amount of time that has passed.
`.reset` to reset the timer
`.done()` to get if the timer has finished
And finally `.pause()` and `.unpause()` to pause/unpause the timer


## NovaTypewriter (novastr.h)
This class is primarily made for dialogues or cutscenes
All it does is create a typewriter effect for text.

Constructor: `(std::string targetText, float duration)`

- `targetText`:The text to writer
- `duration`: Duration in seconds between each character

Methods:
- `.pause()`, `.unpause()`: pause or unpause
- `.update()`: Update (In main loop)
- `.reset()`: Restart
- `.getCurrentText`: Get the text that has been written so far


## NovaVec
There are now vecs in nova.
NovaVec2, NovaVec3 and NovaVec4

You can use +=, -=, *=, /=, +, -, *, and / on them




## NovaStopwatch (`novatime.h`)
This is a stopwatch.
Unlike NovaTimer, this one doesnt have a end to it, it can go forever.

How to use:
Constructor: `()`

functions:
`get<T>()`: Get the time in a timescale, the availaible timescales in novatime.h are: seconds_t, minutes_t, milliseconds_t
`pause()`, `unpause()`: Pause and unpause
`tick()`: Update the timer


## NovaFileWatcher (`novafile.h`)
This class watches over a file, It is used just in case you want to see if a file has changed since the last use
> Note: Please use with care, because reopening a file every frame slows the game down.

How to use:
Constructor: `(pathToFile)`

Methods:
`isDifferent()`: Returns bool whether its different or not
`reload()`: Reload the file

Fields:
`.capturedContent`: Contains the contents of the file since the last reload


## NovaLogger (nova.h)

This class only has static methods but it is not a ordinary logger.
it prints the date, time, day and level of the log

Static methods:
`log(level, text)`: USe when you need a custom log level
`info(text)`: Information log
`error(text)`: Regular error  log
`fatal(text)`: Fatal error log
`warn(text)`: Warning log

## NovaJSON (novajson.h)

This is built on json.hpp by nlohmann

How to use:
Constructor: `()`

Methods:
`loadFile(filePath)`: Load json from a file
`writeFile(filePath, indent = 4)`: Write json to a file, with a custom optional indentation level
`set<T>(std::string name, T value)`: Set `name` in json, to `val` of type `T`
`get<T>(std::string name)`: Throws `novajson_null_val_error` if key is not found, and throws `novajson_type_mismatch_error` if the key is found but not of the type that is required, else returns the value as `T`

How to add arrays:
```cpp
nlohmann::json myarr = nlohmann::json::array();
myarr.push_back("hello");

myjson.set<nlohmann::json>("Array", myarr);

nlohmann::json arr = myjson.get<nlohmann::json>("Array");
```

Strings:
```cpp
myjson.loadFile("somefile.json");
std::string str = myjson.get<std::string>("name");
```



## NovaString (`novastr.h`)
This new class is a subclass of `std::string`

which means you can replace your existing `std::string`'s with this class and they'll still work.

How to use:
Constructors:
- `()`: Default
- `(std::string)`: Default
- `(const char*)`: Default

Methods:
(Even though all functions use `std::string`, you can still use the `NovaString`)
- `bool hasPrefix(std::string)`: Starts with specified string 
- `bool hasPrefix(std::string)`: Ends with specified string
- `std::string replace_(std::string old, std::string new)`: Replace `old` with `new` in copy of string then return that copy
- `std::vector<std::string> split(char delimiter)`: Split string


# Hot (new) 🔥

## NovaSignal (nova.h)
This class also adds two things:

### CALLBACK(f)
    This macro turns anything into a void return and 0 arg function
### CONDITION_VAR(c)
    This macro turns a condition into a callable function, Basically storing a literal condition instead of just its output
    You can get the output by just calling it


This class can emit a function signal, or have a condition to emit the function

How to use:
Constructor: `()`

Fields:
`callback`: The funtion that its binding to, Use the `CALLBACK` macro to turn a literal function into a `std::function`

Methods:
`emit()`: Call the function no matter what
`bindTo(std::function<void(void)>)`: Bind to a condition, use `CONDITION_VAR` to turn a condition into a callable function
`emitOnCondition()`: Emit only when condition




## NovaEvent

This is a new much cleaner way of input

Static fields:
NovaEvent::Key contains key constants
NovaEvent::Mouse contains mouse constants

How to use:
Constructor: `()`

Methods:
`fetch()`: Call every frame to fetch events

Fields:
`.mousePos: NovaVec2`: Mouse position
`.mouseScroll: NovaVec2`: Mouse scroll xy, NovaInputDevice doesnt provide xy scroll, only y scroll
`.lastKeyHit`: Last key pressed


## Nova Types
there are now int types for nova
`UnsignedInt8/16/32/64`
`Int8/16/32/64"


## NovaColor
There is now a color class
Constructor: `(UnsignedInt8 red, UnsignedInt8 green, UnsignedInt8 blue, UnsignedInt8 alpha)`
Fields:
`UnsignedInt8 red, green, blue, alpha`