#!/bin/bash

set -ex

if [ "$1" != "Debug" -a "$1" != "Release" ]; then
    echo "Please provide build type: Debug or Release"
    exit -1
fi

if [ -t 1 ]; then
    # TTY is available => use interactive mode
    DOCKER_FLAGS='-i'
fi

ROOT_DIR=`dirname $(readlink -f $0)`/../../..

mkdir -p ${ROOT_DIR}/docker-build/

( cd ${ROOT_DIR}/Resources/Builders/ && \
        docker build \
               -f ./Dockerfile-MinGW-BuildEnvironment \
               -t mingw-python-build . )

docker run -t ${DOCKER_FLAGS} --rm \
    --user $(id -u):$(id -g) \
    -v ${ROOT_DIR}:/source:ro \
    -v ${ROOT_DIR}/docker-build:/target:rw \
    mingw-python-build \
    bash /source/Resources/Builders/MinGW32-Python3.7/docker-internal.sh $1

ls -lR ${ROOT_DIR}/docker-build/
