# build_SDL2-ogu.sh

This script automatically does what JohnnyonFlame has [explained](https://github.com/JohnnyonFlame/SDL-ge2d/issues/1#issuecomment-1273836347) he's doing to compile his port of [SDL2](https://www.libsdl.org/) for the [Odroid-Go Ultra](https://wiki.odroid.com/odroid_go_ultra/odroid_go_ultra):

- clone the SDL2 sources from [JonnyonFlame's repository](https://github.com/JohnnyonFlame/SDL-ge2d/tree/2.0.22)
- download opengl-meson
- apply the necessary fixes to the opengl-meson header files for SDL2 compilation
- compile SDL2 itself

And finally:

- create an easy-to-use SDL2-ogu.tar.gz SDK package for the OGU containing
  - the static and dynamic SDL2 libraries
  - the SDL2 header files
  - cmake SDL2 module and aarch64 toolchain files
  - some example projects for the OGU
  
## Usage

Prior to using the build_SDL2-ogu.sh, cmake and git need to be installed on the OGU:

```
sudo apt-get install cmake
sudo apt-get install git
```

After that, do:

```
git clone https://github.com/chn-dev/SDL2-ogu
cd SDL2-ogu
./build_SDL2-ogu.sh
```

If everything went fine, the script will have created the SDL2-ogu package with the file name "SDL2-ogu_2.0.22_yyyyMMdd.tar.gz", whereby "yyyyMMdd" denotes the date at the time of its creation.

## Final Words

In case of questions or comments, you can contact me at [chnowak@web.de](mailto:chnowak@web.de), or go to [http://www.chn-dev.net/](http://www.chn-dev.net/).
