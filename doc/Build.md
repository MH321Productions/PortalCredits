# Building PortalCredits

PortalCredits has a two-step building process:

1. Generate the resources
2. Compile the program


## Resource Generation

### Song

To generate the resources, you first need to provide your own song (bc of
copyright concerns, see [README](../README.md) for more information). You can
use
- The song from the
[official Soundtrack](https://store.steampowered.com/app/323170/) 
- The song from [YouTube Music](https://www.youtube.com/watch?v=qflJJO3V6aE)
- A record from the game directly (make sure that the record starts at the exact 
frame the outlines are visible)

You then have to convert the Audio/Video file to the OGG/Vorbis format. There 
are a bunch of different converters out there, I myself recommend
[FFmpeg](https://ffmpeg.org):

    ffmpeg -y -i "Input.mp4" -vn -acodec libvorbis "Output.ogg"

### Generator Script

Now you can run the generator script. It is located in the ```src/Script/```
directory. You have to run the script from there, because it uses relative 
directories. The syntax is:

    GenerateResources.py <path/to/Song.ogg> [-game]

The optional flag ```-game``` is used when you provide a game record song to
correctly calculate the timings.

The script generates the resource files (located in ```src/Generated/```) which
are later compiled into the executable.

## Compilation

To create a build directory, run

    mkdir build
    cd build

### Compilation on Linux

For Linux, run

    cmake ../
    make


### Compilation on MinGW

For MinGW, run

    cmake ../ -G "MinGW Makefiles"
    mingw32-make

The MinGW build produces a more "unstable" build, which causes visual problems
when resizing the console window (They can be removed by moving the window, 
though). Therefore, the MSVC build is preferred.

### Compilation on MSVC

For MSVC, run

    cmake ../ -G "<Your Visual Studio Version here>"

This produces a VS project, which you then can compile.