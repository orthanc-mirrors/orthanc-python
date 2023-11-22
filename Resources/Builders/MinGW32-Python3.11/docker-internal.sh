#!/bin/bash
set -ex

mkdir /tmp/source-writeable

cp -r /source/CMakeLists.txt /tmp/source-writeable/
cp -r /source/Sources /tmp/source-writeable/
cp -r /source/Resources /tmp/source-writeable/

mkdir /tmp/build
cd /tmp/build

wget https://orthanc.uclouvain.be/downloads/third-party-downloads/Python/python-3.11.2-win32.zip
unzip python-3.11.2-win32.zip

if [ "$1" == "Release" ]; then
    LIBRARY_NAME=python311.lib
else
    LIBRARY_NAME=python311_d.lib
fi

cmake /tmp/source-writeable/ \
      -DCMAKE_BUILD_TYPE=$1 \
      -DSTATIC_BUILD=ON \
      -DPYTHON_VERSION=3.11 \
      -DPYTHON_LIBRARY_NAME=${LIBRARY_NAME} \
      -DPYTHON_WINDOWS_ROOT=/tmp/build/python-3.11.2-win32/ \
      -DCMAKE_TOOLCHAIN_FILE=/source/Resources/Orthanc/Toolchains/MinGW-W64-Toolchain32.cmake \
      -DCMAKE_INSTALL_PREFIX=/target 

make -j`nproc`

if [ "$1" == "Release" ]; then
    i686-w64-mingw32-strip ./libOrthancPython.dll
fi

make install
