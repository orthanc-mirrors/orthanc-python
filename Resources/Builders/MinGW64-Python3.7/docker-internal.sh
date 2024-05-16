#!/bin/bash
set -ex

mkdir /tmp/source-writeable

cp -r /source/CMakeLists.txt /tmp/source-writeable/
cp -r /source/Sources /tmp/source-writeable/
cp -r /source/Resources /tmp/source-writeable/

mkdir /tmp/build
cd /tmp/build

wget https://orthanc.uclouvain.be/downloads/third-party-downloads/Python/python-3.7.7-win64.zip
unzip python-3.7.7-win64.zip

cmake /tmp/source-writeable/ \
      -DCMAKE_BUILD_TYPE=$1 \
      -DSTATIC_BUILD=ON \
      -DUSE_LEGACY_BOOST=ON \
      -DPYTHON_VERSION=3.7 \
      -DPYTHON_WINDOWS_ROOT=/tmp/build/python-3.7.7-win64/ \
      -DCMAKE_TOOLCHAIN_FILE=/source/Resources/Orthanc/Toolchains/MinGW-W64-Toolchain64.cmake \
      -DCMAKE_INSTALL_PREFIX=/target 

make -j`nproc`

if [ "$1" == "Release" ]; then
    x86_64-w64-mingw32-strip ./libOrthancPython.dll
fi

make install
