#!/usr/bin/python3

#
# This maintenance script updates the content of the "Orthanc" folder
# to match the latest version of the Orthanc source code.
#

import multiprocessing
import os
import stat
import subprocess
import urllib.request

TARGET = os.path.join(os.path.dirname(__file__), 'Orthanc')
ORTHANC_JAVA_VERSION = '1.0'
PLUGIN_SDK_VERSION = '1.10.0'
ORTHANC_CORE_REPOSITORY = 'https://orthanc.uclouvain.be/hg/orthanc/raw-file'
ORTHANC_JAVA_REPOSITORY = 'https://orthanc.uclouvain.be/hg/orthanc-java/raw-file'

FILES = [
    ('OrthancFramework/Resources/CMake/AutoGeneratedCode.cmake', 'CMake'),
    ('OrthancFramework/Resources/CMake/Compiler.cmake', 'CMake'),
    ('OrthancFramework/Resources/CMake/DownloadOrthancFramework.cmake', 'CMake'),
    ('OrthancFramework/Resources/CMake/DownloadPackage.cmake', 'CMake'),
    ('OrthancFramework/Resources/CMake/GoogleTestConfiguration.cmake', 'CMake'),
    ('OrthancFramework/Resources/EmbedResources.py', 'CMake'),
    ('OrthancFramework/Resources/Toolchains/LinuxStandardBaseToolchain.cmake', 'Toolchains'),
    ('OrthancFramework/Resources/Toolchains/MinGW-W64-Toolchain32.cmake', 'Toolchains'),
    ('OrthancFramework/Resources/Toolchains/MinGW-W64-Toolchain64.cmake', 'Toolchains'),
    ('OrthancFramework/Resources/Toolchains/MinGWToolchain.cmake', 'Toolchains'),
    ('OrthancServer/Plugins/Samples/Common/ExportedSymbolsPlugins.list', 'Plugins'),
    ('OrthancServer/Plugins/Samples/Common/OrthancPluginCppWrapper.cpp', 'Plugins'),
    ('OrthancServer/Plugins/Samples/Common/OrthancPluginCppWrapper.h', 'Plugins'),
    ('OrthancServer/Plugins/Samples/Common/OrthancPluginException.h', 'Plugins'),
    ('OrthancServer/Plugins/Samples/Common/OrthancPluginsExports.cmake', 'Plugins'),
    ('OrthancServer/Plugins/Samples/Common/VersionScriptPlugins.map', 'Plugins'),
]


def Download(x):
    repository = x[0]
    branch = x[1]
    source = x[2]
    target = os.path.join(TARGET, x[3])
    print(target)

    try:
        os.makedirs(os.path.dirname(target))
    except:
        pass

    url = '%s/%s/%s' % (repository, branch, source)

    with open(target, 'wb') as f:
        try:
            f.write(urllib.request.urlopen(url).read())
        except:
            print('ERROR %s' % url)
            raise


commands = []

for f in FILES:
    commands.append([
        ORTHANC_CORE_REPOSITORY,
        'default',
        f[0],
        os.path.join(f[1], os.path.basename(f[0]))
    ])


commands.append([
    ORTHANC_JAVA_REPOSITORY,
    'OrthancJava-%s' % ORTHANC_JAVA_VERSION,
    'Resources/Orthanc/Sdk-%s/orthanc/OrthancCPlugin.h' % PLUGIN_SDK_VERSION,
    'Sdk-%s/orthanc/OrthancCPlugin.h' % PLUGIN_SDK_VERSION,
])


commands.append([
    ORTHANC_JAVA_REPOSITORY,
    'OrthancJava-%s' % ORTHANC_JAVA_VERSION,
    'CodeGeneration/CodeModel.json',
    'Sdk-%s/CodeModel.json' % PLUGIN_SDK_VERSION,
])


commands.append([
    ORTHANC_JAVA_REPOSITORY,
    'OrthancJava-%s' % ORTHANC_JAVA_VERSION,
    'CodeGeneration/CodeModel.json.license',
    'Sdk-%s/CodeModel.json.license' % PLUGIN_SDK_VERSION,
])


pool = multiprocessing.Pool(10)  # simultaneous downloads
pool.map(Download, commands)
