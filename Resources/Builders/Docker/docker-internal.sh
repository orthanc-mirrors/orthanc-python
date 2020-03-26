#!/bin/bash
set -ex

mkdir /tmp/build
cd /tmp/build

cmake /source \
      -DCMAKE_BUILD_TYPE=$1 \
      -DPYTHON_VERSION=3.7 \
      -DSTATIC_BUILD=ON \
      -DCMAKE_INSTALL_PREFIX=/target 

make -j`nproc`

if [ "$1" == "Release" ]; then
    strip ./libOrthancPython.so
fi

make install
