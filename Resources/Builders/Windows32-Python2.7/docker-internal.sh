#!/bin/bash
set -ex

mkdir /tmp/build
cd /tmp/build

wget http://orthanc.osimis.io/ThirdPartyDownloads/Python/python-2.7.17-win32.tar.bz2
tar xvfj python-2.7.17-win32.tar.bz2

cmake /source \
      -DCMAKE_BUILD_TYPE=$1 \
      -DSTATIC_BUILD=ON \
      -DPYTHON_VERSION=2.7 \
      -DPYTHON_WINDOWS_ROOT=/tmp/build/python-2.7.17-win32/ \
      -DCMAKE_TOOLCHAIN_FILE=/source/Resources/Orthanc/Resources/MinGW-W64-Toolchain32.cmake \
      -DCMAKE_INSTALL_PREFIX=/target 

make -j`nproc` VERBOSE=1

if [ "$1" == "Release" ]; then
    i686-w64-mingw32-strip ./libOrthancPython.dll
fi

make install
