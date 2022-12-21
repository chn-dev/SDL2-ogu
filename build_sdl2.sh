#!/bin/bash

HOMEDIR=`pwd`

rm -rf SDL2-ogu
mkdir SDL2-ogu

# Retrieve SDL2 Sources
rm -rf SDL-ge2d
if [ ! -f SDL-ge2d.tar.gz ]; then
   echo "Cloning SDL2 sources from github..."
   git clone https://github.com/JohnnyonFlame/SDL-ge2d/ SDL-ge2d
   echo "Creating local backup archive of SDL2 sources..."
   tar -cf SDL-ge2d.tar SDL-ge2d
   gzip -9 SDL-ge2d.tar
else
   echo "Extracting SDL2 sources..."
   tar xzf SDL-ge2d.tar.gz
fi

cd SDL-ge2d
git checkout 2.0.22
cd ..

# Retrieve OpenGL-Meson
if [ ! -f opengl-meson.tar.gz ]; then
   echo "Retrieving opengl-meson from github..."
   wget -O opengl-meson.tar.gz https://codeload.github.com/CoreELEC/opengl-meson/tar.gz/7bddce621a0c1e0cc12cfc8b707e93eb37fc0f82
fi

echo "Extracting opengl-meson..."
rm -f opengl-meson
rm -rf opengl-meson-7bddce621a0c1e0cc12cfc8b707e93eb37fc0f82
tar xzf opengl-meson.tar.gz
ln -s opengl-meson-7bddce621a0c1e0cc12cfc8b707e93eb37fc0f82 opengl-meson 
echo "Fixing opengl-meson..."
cd opengl-meson
cp include/EGL_platform/platform_fbdev/* include/EGL/
cd ..

# Compile SDL2
echo "Running cmake on SDL2 sources..."
cd SDL-ge2d
cmake -B $HOMEDIR/SDL2-ogu \
    -DCMAKE_C_FLAGS=-I\ $HOMEDIR/opengl-meson/include \
    -DCMAKE_TOOLCHAIN_FILE=$HOMEDIR/aarch64.cmake \
    -DSDL_STATIC=ON \
        -DSDL_LIBC=ON \
        -DSDL_GCC_ATOMICS=ON \
        -DSDL_ALTIVEC=OFF \
        -DSDL_OSS=OFF \
        -DSDL_ALSA=ON \
        -DSDL_ALSA_SHARED=ON \
        -DSDL_JACK=OFF \
        -DSDL_JACK_SHARED=OFF \
        -DSDL_ESD=OFF \
        -DSDL_ESD_SHARED=OFF \
        -DSDL_ARTS=OFF \
        -DSDL_ARTS_SHARED=OFF \
        -DSDL_NAS=OFF \
        -DSDL_NAS_SHARED=OFF \
        -DSDL_LIBSAMPLERATE=OFF \
        -DSDL_LIBSAMPLERATE_SHARED=OFF \
        -DSDL_SNDIO=OFF \
        -DSDL_DISKAUDIO=OFF \
        -DSDL_DUMMYAUDIO=OFF \
        -DSDL_DUMMYVIDEO=OFF \
        -DSDL_WAYLAND=OFF \
        -DSDL_WAYLAND_QT_TOUCH=ON \
        -DSDL_WAYLAND_SHARED=OFF \
        -DSDL_COCOA=OFF \
        -DSDL_DIRECTFB=OFF \
        -DSDL_VIVANTE=OFF \
        -DSDL_DIRECTFB_SHARED=OFF \
        -DSDL_FUSIONSOUND=OFF \
        -DSDL_FUSIONSOUND_SHARED=OFF \
        -DSDL_PTHREADS=ON \
        -DSDL_PTHREADS_SEM=ON \
        -DSDL_DIRECTX=OFF \
        -DSDL_CLOCK_GETTIME=OFF \
        -DSDL_RPATH=OFF \
        -DSDL_RENDER_D3D=OFF \
        -DSDL_X11=OFF \
        -DSDL_OPENGLES=ON \
        -DSDL_OPENGL=OFF \
        -DSDL_VULKAN=OFF \
        -DSDL_PULSEAUDIO=ON \
        -DSDL_HIDAPI_JOYSTICK=OFF \
        -DSDL_MALI=ON \
    -DSDL_KMSDRM=OFF

echo "Building SDL2 sources..."
cd ..
cd SDL2-ogu
make

echo "Copying header files and libs..."
mkdir lib
mv *.so* lib
mv *.a lib
mkdir include/SDL2
mv include/*.h include/SDL2/
cp -R $HOMEDIR/SDL-ge2d/include/* ./include/SDL2/
cd ..

echo "Creating local archive of SDL2 headers and libs..."
rm -f SDL2-ogu.tar.gz
tar -cf SDL2-ogu.tar SDL2-ogu
gzip -9 SDL2-ogu.tar

echo "Ready."

