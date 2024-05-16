#!/bin/bash

set -e

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters: Must provide the target folder"
    exit -1
fi

# Determine the absolute path to the directory containing the script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

TARGET=$1
echo "Will publish libraries in folder: ${TARGET}"

mkdir -p ${TARGET}

VERSION=`grep "set(PLUGIN_VERSION" ${DIR}/../../CMakeLists.txt | cut -d '"' -f 2`
echo "Version of the Python plugin: ${VERSION}"

set -x


## Windows 32

bash ${DIR}/MinGW32-Python2.7/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python2.7-${VERSION}.dll

bash ${DIR}/MinGW32-Python3.7/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python3.7-${VERSION}.dll

bash ${DIR}/MinGW32-Python3.8/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python3.8-${VERSION}.dll

bash ${DIR}/MinGW32-Python3.9/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python3.9-${VERSION}.dll

bash ${DIR}/MinGW32-Python3.10/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python3.10-${VERSION}.dll

bash ${DIR}/MinGW32-Python3.11/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python3.11-${VERSION}.dll

bash ${DIR}/MinGW32-Python3.12/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win32-Python3.12-${VERSION}.dll


## Windows 64

bash ${DIR}/MinGW64-Python2.7/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python2.7-${VERSION}.dll

bash ${DIR}/MinGW64-Python3.7/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python3.7-${VERSION}.dll

bash ${DIR}/MinGW64-Python3.8/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python3.8-${VERSION}.dll

bash ${DIR}/MinGW64-Python3.9/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python3.9-${VERSION}.dll

bash ${DIR}/MinGW64-Python3.10/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python3.10-${VERSION}.dll

bash ${DIR}/MinGW64-Python3.11/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python3.11-${VERSION}.dll

bash ${DIR}/MinGW64-Python3.12/docker-compile.sh Release
cp ${DIR}/../../docker-build/lib/libOrthancPython.dll ${TARGET}/OrthancPython-Win64-Python3.12-${VERSION}.dll
