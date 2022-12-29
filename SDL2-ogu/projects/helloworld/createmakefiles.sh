#!/bin/bash
cmake . -B helloworld -DCMAKE_MODULE_PATH=../.. -DCMAKE_TOOLCHAIN_FILE=../../aarch64.cmake 

