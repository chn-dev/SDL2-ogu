# set cross-compiled system type, it's better not use the type which cmake cannot recognized.
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)
# for the reason of aarch64-linux-gnu-gcc DONOT need to be installed, make sure aarch64-linux-gnu-gcc and aarch64-linux-gnu-g++ can be found in $PATH: 
SET(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)
SET(CMAKE_AR /usr/bin/aarch64-linux-gnu-ar)
SET(CMAKE_RANLIB /usr/bin/aarch64-linux-gnu-ranlib)
set(CMAKE_ADDR2LINE /usr/bin/aarch64-linux-gnu-addr2line)
set(CMAKE_AR /usr/bin/aarch64-linux-gnu-ar)
set(CMAKE_CXX_COMPILER_AR /usr/bin/aarch64-linux-gnu-gcc-ar)
set(CMAKE_CXX_COMPILER_RANLIB /usr/bin/aarch64-linux-gnu-gcc-ranlib)
set(CMAKE_C_COMPILER_AR /usr/bin/aarch64-linux-gnu-gcc-ar)
set(CMAKE_C_COMPILER_RANLIB /usr/bin/aarch64-linux-gnu-gcc-ranlib)
set(CMAKE_LINKER /usr/bin/aarch64-linux-gnu-ld)
set(CMAKE_NM /usr/bin/aarch64-linux-gnu-nm)
set(CMAKE_OBJCOPY /usr/bin/aarch64-linux-gnu-objcopy)
set(CMAKE_OBJDUMP /usr/bin/aarch64-linux-gnu-objdump)
set(CMAKE_RANLIB /usr/bin/aarch64-linux-gnu-ranlib)
set(CMAKE_READELF /usr/bin/aarch64-linux-gnu-readelf)
set(CMAKE_STRIP /usr/bin/aarch64-linux-gnu-strip)
set(GIT_EXECUTABLE /usr/bin/git)

