#!/bin/bash

#declare -a ANDROID_ABIS=(armeabi armeabi-v7a arm64-v8a x86)
declare -a ANDROID_ABIS=(armeabi-v7a arm64-v8a x86)
#declare -a ANDROID_ABIS=(armeabi-v7a)
#declare -a GLES_VERSIONS=(GLES1 GLES2)
declare -a GLES_VERSIONS=(GLES1)

API_LEVEL=21

BASE_NAME=OpenSceneGraph
VERSION=3.4.0
FULL_NAME=$BASE_NAME-$VERSION

ANDROID_BASE_PATH=${HOME}/Android
ANDROID_SDK_ROOT=$ANDROID_BASE_PATH/Sdk
ANDROID_NDK_ROOT=$ANDROID_SDK_ROOT/ndk-bundle

################################################################################

MAKE_PROGRAM=$ANDROID_NDK_ROOT/prebuilt/linux-x86_64/bin/make
CMAKE_PROGRAM=$ANDROID_SDK_ROOT/cmake/3.10.2.4988404/bin/cmake

################################################################################

for GLES_VERSION in "${GLES_VERSIONS[@]}"; do

    for ANDROID_ABI in "${ANDROID_ABIS[@]}"; do

        ARCHITECTURE=arm
        
        if [ "$ANDROID_ABI" == "arm64-v8a" ]; then
            ARCHITECTURE=arm64
        elif [ "$ANDROID_ABI" == "x86" ]; then
            ARCHITECTURE=x86
        fi

        rm -r -f temp
        svn export $FULL_NAME temp
        cd temp
        mkdir 3rdparty
        mkdir 3rdparty/build
        mkdir 3rdparty/build/freetype
        mkdir 3rdparty/build/libpng
        rm -r -f build
        mkdir build
        cd build

        INSTALL_PREFIX=$ANDROID_BASE_PATH/osg-$VERSION/$GLES_VERSION/$ANDROID_ABI
        FREETYPE_DIR=$ANDROID_BASE_PATH/freetype-2.6.3/$ARCHITECTURE
            
        if [ "$ANDROID_ABI" != "x86" ]; then
            $CMAKE_PROGRAM .. \
                -DCMAKE_MAKE_PROGRAM=$MAKE_PROGRAM \
                -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
                -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX \
                -DDYNAMIC_OPENTHREADS=OFF \
                -DDYNAMIC_OPENSCENEGRAPH=OFF \
                -DOPENGL_PROFILE="$GLES_VERSION" \
                -DANDROID_NDK=$ANDROID_NDK_ROOT \
                -DANDROID_TOOLCHAIN=clang \
                -DANDROID_ABI=$ANDROID_ABI \
                -DANDROID_CPP_FEATURES="rtti exceptions" \
                -DANDROID_NATIVE_API_LEVEL=$API_LEVEL \
                -DFREETYPE_DIR=$FREETYPE_DIR \
                -DANDROID_ARM_MODE=arm
        else
            $CMAKE_PROGRAM .. \
                -DCMAKE_MAKE_PROGRAM=$MAKE_PROGRAM \
                -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
                -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX \
                -DDYNAMIC_OPENTHREADS=OFF \
                -DDYNAMIC_OPENSCENEGRAPH=OFF \
                -DOPENGL_PROFILE="$GLES_VERSION" \
                -DANDROID_NDK=$ANDROID_NDK_ROOT \
                -DANDROID_TOOLCHAIN=clang \
                -DANDROID_ABI=$ANDROID_ABI \
                -DANDROID_CPP_FEATURES="rtti exceptions" \
                -DANDROID_NATIVE_API_LEVEL=$API_LEVEL \
                -DFREETYPE_DIR=$FREETYPE_DIR
        fi
        
#             -DOSG_BUILD_PLATFORM_ANDROID=ON \
#             -DOSG_CPP_EXCEPTIONS_AVAILABLE=OFF \
#             -DOSG_GL1_AVAILABLE=OFF \
#             -DOSG_GL2_AVAILABLE=OFF \
#             -DOSG_GL3_AVAILABLE=OFF \
#             -DOSG_GLES1_AVAILABLE=ON \
#             -DOSG_GLES2_AVAILABLE=OFF \
#             -DOSG_GL_LIBRARY_STATIC=OFF \
#             -DOSG_GL_DISPLAYLISTS_AVAILABLE=OFF \
#             -DOSG_WINDOWING_SYSTEM=None \
#             -DOSG_GL_MATRICES_AVAILABLE=OFF \
#             -DOSG_GL_VERTEX_FUNCS_AVAILABLE=OFF \
#             -DOSG_GL_VERTEX_ARRAY_FUNCS_AVAILABLE=OFF \
#             -DOSG_GL_FIXED_FUNCTION_AVAILABLE=OFF \
#             -DANDROID_DEBUG=OFF \
#             -DANDROID_PLATFORM=android-$API_LEVEL \
#             -DANDROID_NDK_REVISION=$API_LEVEL \
#             -DANDROID_STL="gnustl_static" \
            
        $MAKE_PROGRAM -j 4
        $MAKE_PROGRAM install
        
        if [ "$ANDROID_ABI" == "arm64-v8a" ]; then
            mkdir $INSTALL_PREFIX/lib
            cp -r -f $INSTALL_PREFIX/lib64/* $INSTALL_PREFIX/lib
        fi

        cd ../..

    done
    
done
