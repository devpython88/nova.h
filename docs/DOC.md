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

2. Install raylib

    For macOS (homebrew): `brew install raylib`
    For APT: `sudo apt-get install libraylib-dev`
    For Arch Linux: `sudo pacman -S raylib`
    For DNF (Fedora): `sudo dnf install raylib-devel`
    For windows: Requires manual installation.

3. Run the corresponding file
    For macOS and Linux: `bash dist-mac-linx.sh`
    For windows: `dist-win32.bat`
4. Finish
    Directories for macOS and Linux: `build-linx/dist/include` and `build-linx/dist/lib`
    For windows: `build/dist/include` and `build/dist/lib`


## Table of contents

## Hot (new) 🔥

- [Scene management](#scene-management)
- [Notifying](#novanotifier-novamisch)
- [Animated Images](#animated-images)
    - [Raw Texture](#raw-texture) -- IMPORTANT UPDATE (Mustn't be ignored)
    - [NovaSpritesheet](#novaspritesheet) -- Update
    - [NovaAnimation](#novaanimation) -- Update

------------------------------------------------------------------

- [Window initialization](#window-initialization)
- [Object Base Class](#novaobject4)
- [Rendering and Game loop](#rendering-and-game-loop)
    - [Standalone shapes](#standalone-shapes)
    - [Collision](#collision)
- [Images](#images)
- [Built-in Camera](#camera)
- [Audio](#audio)
    - [Sounds](#sounds)
    - [Music](#music)
- [Keyboard and Mouse](#keyboard-and-mouse)
- [Input Manager](#input-manager)
- [Randomization](#novarandomdevice)
- [File management](#novafileh)
- [File system management](#novafs--win32fs)
- [Object hierarchies](#novaobjectchain)
- [Typewriter effects](#novatypewriter-novastrh)
- [Timers](#novatimer-novatimeh)
- [Math vectors](#novavec)
- [Stopwatches](#novastopwatch-novatimeh)
- [File watcher](#novafilewatcher-novafileh)
- [Verbose logging](#novalogger-novah)
- [JSON](#novajson-novajsonh)
- [Events](#novaevent)
- [Signals](#novasignal-novah)
- [Nova Color](#novacolor)
- [Nova Types](#nova-types)
- [Grid snapping](#novagrid)
- [Grid rendering](#novarenderdevice-grid)
- [Log files](#novalogfile-novafileh)
- [Copyright free assets](#copyright-free-assets)
- [Vehicles](#vehicles-novamisch)
- [Image Scaling](#image-scaling)
- [Cool Math Operations](#math-operations-novamisch)
- [Lists](#lists-novamisch)
- [Object groups](#novaobjectgroup-novamisch)
- [Data save and load](#novadatadevice-novamisch)
- [External camera](#camera-novah)

## [UI](#ui)

- ### [Buttons](#buttons)
- ### [Input](#input-boxes)
- ### [Labels](#labels)
- ### [Styling](#styling)
- ### [Dialogs](#dialogs)
- ### [Menus](#menus)


## Window initialization

To create a window in nova.h, You first need to import the nova.h header.
```cpp
#include <nova.h>

int main(){
    return 0;
}
```

In the main function, You have to create a NovaWindow instance.
NovaWindow(width, height, title): Creates a `width`x`height` window with title `title`


Use `.close()` to close the window

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

## Raw Texture
Before diving into [Images](#images), We need to learn about `NovaRawTexture`

NovaRawTexture is basically a Object Oriented `Texture2D`
It's main purpose is to be provided to images and animations.
That's so you can reuse a single Raw texture across many and many images/animations

To construct it: `(std::string path)`

To unload it: `.dispose()`

It also allows you to get the raylib texture's id and stuff like that.

## Images
In nova.h, Images are drawn using NovaRenderImage
constructor: NovaRenderImage(float x, float y, NovaRawTexture* tx)

After loading a image, You can use `NovaRenderDevice::image(NovaRenderImage)` to draw
or `::imageLoaded(NovaRenderImage)` to see if it is loaded or not.

To unload images, Just don't Since if your image uses a raw texture that is shared across multiple images and you unload this iimage, Then all those images will look corrupted
So don't But if it is a single texture then just unload the raw texture

For animations, Checkout [Animations](#animated-images)

## Animated Images
To animate a image, You have to use spritesheets.
But most libraries like: Raylib, SDL3, SFML only provide ways to cutout a frame from an animation.

But nova.h has two classes, one for manual animations and one for automatic.

### NovaSpritesheet
Constructor: (NovaRawTexture* tx, float x, float y, float frameWidth, float frameHeight)

The class used to have a internal NovaRenderImage, But now the class is a subclass of NovaRenderImage

If you changed the internal texture (which you probably shoudn't), You can use the NovaSpritesheet's `.recalculateRows` and `.recalculateColumns` function to recalculate the frames.

You can use its .row and .column properties to manage row and column (in 0, 1, 2 not multiples of the frameSize)

You can use its custom .render function to draw the current frame.

.rows and .columns properties are used to get the amount of rows and columns

### NovaAnimation
This class is a subclass of `NovaSpritesheet`
Meaning it also has a internal image, and row and column properties

How to make a valid animation:
Step 1. Create a instance
```cpp
NovaRawTexture tx("Player.png");
NovaAnimation anim(&tx, 20, 20, 8, 8);
```

Step 2. Set frame rate
```cpp
// frame rate
anim.setFramerate(24);
anim.getFramerate();
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

Fields:
`acceleration: NovaVec2`: XY Speed for velocity movements
`velocity: NovaVec2`: If you change this to not be 0, 0 Then every frame the object will move using acceleration towards the velocity, Be sure to call `updateMovement`

Methods:
`cache()`: Cache the object, make it invisible and [TITLE CARD], ahem. Invincible
`grab()`: Decache the object, make it visible and vincible
`move(float dx, float dy)`: Increase x and y with dx and dy
`move(NovaVec2 delta)`: Increase x and y by delta
`roam(float speed, NovaRandomDevice* rd)`: Randomly roam around
`moveTo(NovaVec2 target, float speed)`: Move towards target
`roamTo(NovaVec2 target, float speed, NovaRandomDevice* rd)`: Roam towards target, in other words randomly move targets target in x or y axis, for example instead of going a straight diagonal path, go a rough diagonal path
`updateMovement()`: Uses velocity and acceleration to move, Needs to be called if velocity movement is needed every frame
`centerPivot()`: Center the origin to the center of the object (Overriden by NovaRenderImage for scaling)


## `novafile.h`
Nova isn't just for game development.
You could also use it for things like Randomization, Integration into raylib

But now you can even use it for file operation.

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





## NovaGrid
This class is mainly used to snap objects to a grid

How to use:
Constructors:
- `(float cellSizeX, float cellSizeY)`: takes cell size individually
- `(NovaVec2 cellSize)`: takes a vector 2 

methods:
- `NovaVec2 snap(float x, float y)`: Snaps the x and y to the grid then returns a vector 2 containing the snapped position

## NovaRenderDevice grid
NovaRenderDevice now has some grid drawing functions.


- `gridLines(NovaVec2 cellSize, NovaVec2 cells, Color color)`: draws a grid only with lines, Takes cellsize and number of cells
- `gridBoxes(NovaVec2 cellSize, NovaVec2 cells, Color boxColor, Color lineColor)`: draws grid but each cell filled with a color instead of each cell being blank


## Copyright free assets
Now Nova has some copyright free assets for game stats, All of these were made by me so don't worry i wont copyright you 👍

These include: `Mana`, `Health`, `Breathe`, `Hunger`, `Thirst` and `Temperature`
You can check these out, they are spritesheets with different stages



## NovaObject4 update

NovaObject4 has gotten some more new features.

These include two move functions:

`move(float, float)` and `move(NovaVec2)`

and finally a roam function `roam(speed)`
This function just makes the object go in a random direction in random horizontal or vertical axis

## NovaAnimation update

maxFrameTime got removed

Instead now you use:
- `setFramerate(int)`: Sets the frame time in actual FPS
- `getFramerate(int)`: Gets the frame rate



## NovaLogFile (`novafile.h`)
This is just a normal `NovaFile` but it has log functions.
You can use it for multiplayer server logs and stuff.






## UI
Nova now has ui function in NovaRenderDevice

### Buttons:
To show buttons you use the `.uiButton` function from NovaRenderDevice.
`.uiButton(std::string text, NovaVec2 position, Color background, Color foreground, int fontSize)`: Simple button (Has hover and click effects)
This returns a enum class `UIEvent`
You can use the enum to check for click, hover and no action
`UIEvent::Click` and `UIEvent::Hover` and `UIEvent::None` when no action is performed

### Input boxes:
To show a functional input box, use `.uiInputBox`
`.uiInputBox(std::string* ptr_to_target, NovaVec2 position, Color background, Color foreground, int fontSize, bool focused = true)`
This function takes a pointer to a string, That pointer modifies the string, And that string is where the contents of the input box are
The end `focused` parameter is optional and controls whether to just show the input box or take input aswell

### Labels:
Labels are normal text display but can have fonts, Unlike `.text`
`.uiLabel(text, int fontSize, Color color)`: Shows the text with the font.

### Fonts and Padding:
To actually modify the UI element fonts and padding and spacing.

You can use the setters and getters
`.getSpacing(): int`
`.getPadding(): NovaVec2`
`.getFontName(): std::string`

`.setPadding(NovaVec2)`: Set padding through a vector
`.setPadding(float, float)`: Set padding through floats
`.setSpacing(int)`: Set the spacing
`.setFont(std::string)`: Set the font
`.unloadFont()`: Unload the font aswell as make it so Nova starts using the default font again.



### Dialogs
There are also simple modal dialogs.
They can be shown through `NovaPopup`
How to use:
Constructor: `(title std::string, float x, float y, float width, float height, Color bg)`

Methods:
`show()`: Show the dialog, Returns enum class `PopupEvent`, which can be either `::Open` or `::Closed` depending on if the close button was pressed

There is also a boolean field `visible` that controls if the dialog is visible or not


### Menus
Nova also has menus.

The class is `NovaMenu`

Constructor: `(std::string label, NovaVec2 position, int fontSize)`

Fields:
`position NovaVec2`: Position
`dropdownPosition Novavec2`: Position from where the dropdown list will show up
`label std::string`: Label
`fontSize int`: Font size
`opened bool`: Dropdown shown or not

Methods:
`addOption(label)`: Add option
`removeOption(index)`: Remove option

`MenuResult show()`:
Shows the menu bar, Handles opening and closing.
Returns MenuResult containing if option was clicked and which option was clicked

`MenuResult`:
`bool clicked` and `std::string option`





## Vehicles (novamisc.h)
Yes, nova now has built in vehicle physics and systems

First, lets see the fields and constructor of `NovaVehicleConfig`:
Fields:
`topSpeed`: Top speed in pixels
`accelerationSpeed`: Acceleration speed
`decelerationSpeed`: Deceleration speed
`maxDecelerationSpeed`: Maximum deceleration speed (control how quickly the vehicle can reverse)
`turnSpeed`: vehicle's wheel turn speed
Constructor: `(float topSpeed, float decelerationSpeed, float accelerationSpeed, float turnSpeed, float maxDecelerationSpeed)`


Now lets take a look at how you can actually make a vehicle:

Constructor: `NovaVehicle(NovaObject4* vehicleHost, const NovaVehicleConfig& config, int forwardKey, int backwardKey, int turnLeftKey, int turnRightKey)`
The constructor takes a pointer to a host object (The vehicle), A vehicle config for the stats, And finally the movement keys


Fields:
`NovaVehicleConfig vehicleConfig;`: The vehicle stats, Can be changed
`int forwardKey, backwardKey, turnLeftKey, turnRightKey;`: The movement keys, Can be changed
`NovaObject4* vehicleHost;`: The host, can be changed
`bool driving;`: Controls whether to handle acceleration and deceleration or not, If false then the vehicle only handles velocity (damping)

Methods:
`void drive();`: Call every frame to update rotation, velocity, handle acceleration and deceleration
`float getValidSpeed();`: Returns a valid speed instead of the barebones y velocity


Overall, This is great class that provides a quick and easy way to make vehicles






## Math Operations (novamisc.h)
This update adds some cool math operations,
Such as vector normalization and sign extraction.

Methods:
`normalize(float)`: Sign extraction
`normalize2(NovaVec2)`: Vector normalization
`normalize3(NovaVec3)`: Vector normalization
`normalize4(NovaVec4)`: Vector normalization
`round(float v, float step)`: Round `v` to the nearest `step`


## Image Scaling
To scale a image now, You can just have a `NovaRenderImage` and change its `scale` NovaVec2
Be sure to call `centerPivot()` afterwards to adjust the pivot for scaling.
For animations/spritesheets you can change the `scale` vector of their internal `NovaRenderImage`


## Image Vehicle Fix
Previously, I overlooked vehicles for images.
Which resulted in weird rotations for images when using vehicles
Now I have fixed it





## Lists (novamisc.h)
The class is called `NovaList`
It is a subclass of std::vector meaning even if you replace your normal vectors with `NovaList` They will still work just fine.

Constructor: `NovaList<T>()`

Methods:
`has_item(auto it)`: Checks if the `it` valued item is in the list, If your list consists of custom classes and those classes have a `==` operator overload, It will use that overload instead of the default `==` operator.
`pop_index(int index)`: Removes item at that index
`fill(int amount, auto genFunc)`: Takes a amount and a lambda/function, The function should take a `int i` parameter for the index, All it does it add the return value of the function to the array `amount` amount of times.



## Camera (nova.h)
To use this camera class `NovaCamera`
You will first have to set your window's `integratedCamera` property to `false` so that the window doesn't use the built-in camera.


Constructor: `NovaCamera()`
Fields:
`float zoom`: The amount of zoom
`float rotation`: How much the camera is rotated
`NovaVec2 target`: The point where the camera's top-left is.


Methods:
`NovaVec2 getViewportSize()`: Get the camera's viewport size, What this does is it returns the size of the camera's vision. So if the zoom is 2.0f then instead of the screen size, it returns the camera's view size
`float getViewportWidth()`: Same as above but only for width
`float getViewportHeight()`: Same as above but only for height
`void start()`: Start the camera mode
`void end()`: End the camera mode, You can draw your GUI after calling this since after ending the camera mode, The items will no longer be affected by the camera
`NovaVec2 getViewportRelativePosition(float x, float y)`: Make `x` and `y` relative to the camera view.
`void refresh()`: Update the internal raylib camera's properties to be the properties of the actual `NovaCamera`


## NovaDataDevice (novamisc.h)
This class is used for saving and loading json data as binary\


Methods:
`static void saveData(std::string file, NovaJSON j)`: Saves binary of the `j` to `file`
`static void saveData(std::string file, std::vector<NovaJSON> jsons)`: Saves binary of the `jsons` to `file`
`static NovaJSON loadData(std::string file)`: Load the JSON from `file`
`static std::vector<NovaJSON> loadDataEx(std::string file)`: Load the JSONs from `file`



## NovaObjectGroup (novamisc.h)

What this class does is it basically allows you to manipulate a list as if it were an object and apply the changes to all objects in it


Constructor: `()`

Methods:
`get(int index)`: Get object at index
`getAll(std::string)`: Get all objects with `tag`
`add(NovaObject4* obj, std::string tag)`: Add an object pointer with a tag
`forEach(auto itFunc)`: Iterate over all objects with the `itFunc`, The function must take `int i` and `GroupItem it`
`refresh()`: Call every frame, Update all object's velocity and acceleration to be `globalVelocity` and `globalAcceleration`
`collidesWith(NovaObject4 other)`: Check if any objects collide with `other`

Fields:
`NovaVec2 globalVelocity`: The global velocity for all objects
`NovaVec2 globalAcceleration`: The global acceleration for all objects.

# Hot (new) 🔥


## Scene management
Whenever you're making a game, You might run into the problem of scene management.
To fix it normally, You would have to build a scene manager.
But in nova.h, You can use the global scene manager
This class is also static meaning it requires no constructor

But first, Let's check out the `NovaScene` class:
### Nova Scene (nova.h)
This class is the base class for all scenes.
It has these 4 overridable functions:
`draw()`: Where you draw stuff
`update(float deltaTime)`: Where you update stuff
`load()`: Where you load textures and stuff
`unload()`: Where you dispose of textures and other stuff.

Constructor: `(NovaWindow* window)`

To make a scene, all you have to do is make a subclass of this class.
Add a `NovaWindow*` argument to pass to the class's costructor.
And that's basically it
After that just add your logic

------------------------
Lets get back to `NovaScenes`

Managing scenes:
`add(std::string, NovaScene*)`: Add a scene with a identifier
`remove(std::string)`: Remove a scene by its identifier (Throws std::runtime_error if failed)
`go(std::string)`: Select a scene (Throws std::runtime_error if failed)

Other functions:
`show()`: Call every frame to execute the current scene, throws std::runtime_error if the current scene doesn't exist
`has(std::string)`: Returns bool, Check if a scene exists



## NovaNotifier (novamisc.h)

This is a basic notifier, If you want to use it for the entire game, You can but note the fact it's very basic and must probably only be used for debugging purposes.

This class is static

Methods:
`notify(std::string)`: Change the current message and set it to be hidden after 2.5s
`draw()`: Draw the message and hide it if 2.5s has passed
`clear()`: Clear the current message and reset the timer

