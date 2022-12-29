# SDL2-ogu

SDL2-ogu is [JonnyonFlame's](https://forum.odroid.com/viewtopic.php?f=221&t=45184) port of [SDL2](https://github.com/JohnnyonFlame/SDL-ge2d/tree/2.0.22) for the [Odroid-Go Ultra](https://wiki.odroid.com/odroid_go_ultra/odroid_go_ultra), pre-compiled and packaged nicely. The package contains all necessary static+dynamic libraries, include files, cmake files and examples. It can be used to compile SDL2 applications on the device itself as well as to cross-compile them on an Ubuntu Linux PC very easily.

## How To Use SDL2-ogu

The package contains

- the SDL2 include files in SDL2-ogu/SDL2/include
- the SDL2 static (*.a) and dynamic (*.so) libraries in SDL2-ogu/SDL2/lib
- the cmake SDL2 module file (SDL2-ogu/FindSDL2.cmake)
- the aarch64 toolchain file (SDL2-ogu/aarch64.cmake)

This means that you should be able to build any existing SDL2 project which comes with a CMakeLists.txt file without any further adjustments.

Copy the SDL2-ogu package (for example: "SDL2-ogu_2.0.22_20221229.tar.gz") anywhere on your OGU and extract it:

```
tar xzvf SDL2-ogu_2.0.22_20221229.tar.gz
```

After that, the Makefile for the "helloworld" example project can be created with:

```
cd SDL2-ogu/projects/helloworld
cmake . -B helloworld -DCMAKE_MODULE_PATH=../.. -DCMAKE_TOOLCHAIN_FILE=../../aarch64.cmake
```

The "-DCMAKE_MODULE_PATH" specifies the path where the FindSDL2.cmake file is located, and the "-DCMAKE_TOOLCHAIN_FILE" parameter specifies the location of the aarch64.cmake toolchain file so that the correct (cross-)compiler is used.

The Makefile is written to SDL2-ogu/projects/helloworld/helloworld/Makefile, so the project can compiled with:

```
make -C helloworld
```

If everything goes well, the "helloworld" binary is written to SDL2-ogu/projects/helloworld/helloworld/helloworld".

Before you start it, it is highly recommended to stop emulationstation on the OGU:

```
sudo systemctl stop emulationstation
```

It is also necessary to set some environment variables so that SDL2 uses the correct LCD screen orientation:

```
export SDL_MALI_ORIENTATION=1
export SDL_MALI_ROTATION=0
```

Then cd to the helloworld binary's directory and start it:

```
cd helloworld
./helloworld
```

That's it!

There's also a helloworld.sh script which sets the environment variables, goes to the helloworld directory and starts the helloworld binary.

## Cross-Compiling for the OGU

If you're using an Ubuntu Linux PC (I'm using [LXLE](https://www.lxle.net/) 20.04), you can use the SDL2-ogu package as-is to cross-compile for the OGU. The steps for compilation are the same as when compiling directly on the device itself (see above). However, the cross-compiler for the arm64 architecture needs to be installed first:

```
sudo apt-get install crossbuild-essential-arm64
```

## Final Words

In case of questions or comments, you can contact me at [chnowak@web.de](mailto:chnowak@web.de).
