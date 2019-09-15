#!/bin/bash

declare -a ARCHITECTURES=(arm arm64 x86)

API_LEVEL=21

BASE_NAME=freetype
VERSION=2.6.3
FULL_NAME=$BASE_NAME-$VERSION

ANDROID_BASE_PATH=${HOME}/Android
ANDROID_SDK_ROOT=$ANDROID_BASE_PATH/Sdk
ANDROID_NDK_ROOT=$ANDROID_SDK_ROOT/ndk-bundle

################################################################################

export CC=clang
export CXX=clang++

# MAKE_PROGRAM=$android_sdk_path/cmake/3.6.3155560/bin/ninja
MAKE_PROGRAM=$ANDROID_NDK_ROOT/prebuilt/linux-x86_64/bin/make
# MAKE_PROGRAM=make

################################################################################

for ARCHITECTURE in "${ARCHITECTURES[@]}"; do

    export NDK_TOOLCHAIN=$ANDROID_BASE_PATH/toolchains/ndk-standalone-$API_LEVEL-$ARCHITECTURE

    rm -r $NDK_TOOLCHAIN
    $ANDROID_NDK_ROOT/build/tools/make_standalone_toolchain.py \
        --arch $ARCHITECTURE \
        --api $API_LEVEL \
        --install-dir $NDK_TOOLCHAIN

    export PATH=$NDK_TOOLCHAIN/bin:$PATH
    export HOST=$ARCHITECTURE-linux-androideabi
    
    if [ "$ARCHITECTURE" == "arm64" ]; then
        export HOST=aarch64-linux-androideabi
    fi

    export SYSROOT=$NDK_TOOLCHAIN/sysroot

    export CPPFLAGS="--sysroot=$SYSROOT -I$SYSROOT/usr/include -I$NDK_TOOLCHAIN/include"
    export LDFLAGS="-L$SYSROOT/usr/lib -L$NDK_TOOLCHAIN/lib"

    ####################

    rm -r -f temp
    svn export $FULL_NAME temp
    cd temp

    ####################

    ./configure --host=$HOST --prefix=$ANDROID_BASE_PATH/$FULL_NAME/$ARCHITECTURE --without-zlib --with-png=no --with-harfbuzz=no
    $MAKE_PROGRAM -j 4
    $MAKE_PROGRAM install

    cp -r $ANDROID_BASE_PATH/$FULL_NAME/$ARCHITECTURE/include/freetype2/* $ANDROID_BASE_PATH/$FULL_NAME/$ARCHITECTURE/include

    ####################

    cd ..

done
