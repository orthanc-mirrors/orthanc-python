#!/usr/bin/python

#
# This maintenance script updates the content of the "Orthanc" folder
# to match the latest version of the Orthanc source code.
#

import multiprocessing
import os
import stat
import urllib2
import subprocess

TARGET = os.path.join(os.path.dirname(__file__), 'Orthanc')
PLUGIN_SDK_VERSION = '1.5.7'
REPOSITORY = 'https://hg.orthanc-server.com/orthanc/raw-file'

FILES = [
    'Core/Compatibility.h',
    'Plugins/Samples/Common/OrthancPluginCppWrapper.cpp',
    'Plugins/Samples/Common/OrthancPluginCppWrapper.h',
    'Plugins/Samples/Common/OrthancPluginException.h',
    'Plugins/Samples/Common/VersionScript.map',
    'Resources/CMake/BoostConfiguration.cmake',
    'Resources/CMake/Compiler.cmake',
    'Resources/CMake/DownloadPackage.cmake',
    'Resources/CMake/JsonCppConfiguration.cmake',
    'Resources/LinuxStandardBaseToolchain.cmake',
    'Resources/MinGW-W64-Toolchain32.cmake',
    'Resources/MinGW-W64-Toolchain64.cmake',
    'Resources/MinGWToolchain.cmake',
    'Resources/Patches/boost-1.69.0-linux-standard-base.patch',
]

SDK = [
    'orthanc/OrthancCPlugin.h',
]


def Download(x):
    branch = x[0]
    source = x[1]
    target = os.path.join(TARGET, x[2])
    print target

    try:
        os.makedirs(os.path.dirname(target))
    except:
        pass

    url = '%s/%s/%s' % (REPOSITORY, branch, source)
    print('Downloading %s' % url)

    with open(target, 'w') as f:
        f.write(urllib2.urlopen(url).read())

    print('Done %s' % url)
        


commands = []

for f in FILES:
    commands.append([ 'default', f, f ])

for f in SDK:
    commands.append([
        'Orthanc-%s' % PLUGIN_SDK_VERSION, 
        'Plugins/Include/%s' % f,
        'Sdk-%s/%s' % (PLUGIN_SDK_VERSION, f) 
    ])


pool = multiprocessing.Pool(10)  # simultaneous downloads
pool.map(Download, commands)


# Patch the SDK
subprocess.check_call([ 'patch', '-p0', '-i', os.path.join
                        (os.path.abspath(os.path.dirname(__file__)),
                         'OrthancCPlugin-%s.patch' % PLUGIN_SDK_VERSION) ],
                      cwd = os.path.join(os.path.dirname(__file__),
                                         'Orthanc',
                                         'Sdk-%s' % PLUGIN_SDK_VERSION, 'orthanc'))
