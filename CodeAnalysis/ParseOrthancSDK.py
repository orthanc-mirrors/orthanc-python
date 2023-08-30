#!/usr/bin/env python

##
## Python plugin for Orthanc
## Copyright (C) 2020-2023 Osimis S.A., Belgium
## Copyright (C) 2021-2023 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
##
## This program is free software: you can redistribute it and/or
## modify it under the terms of the GNU Affero General Public License
## as published by the Free Software Foundation, either version 3 of
## the License, or (at your option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Affero General Public License for more details.
## 
## You should have received a copy of the GNU Affero General Public License
## along with this program. If not, see <http://www.gnu.org/licenses/>.
##


import argparse
import clang.cindex
import os
import pprint
import pystache
import sys


ROOT = os.path.dirname(os.path.realpath(sys.argv[0]))


##
## Configuration of the custom primitives that are manually
## implemented (not autogenerated)
##

CUSTOM_FUNCTIONS = set([
    'OrthancPluginCreateDicom',
    'OrthancPluginCreateImageAccessor',                # Replaced by "orthanc.CreateImageFromBuffer()"
    'OrthancPluginFreeMemoryBuffer',
    'OrthancPluginFreeString',
    'OrthancPluginLookupDictionary',
    'OrthancPluginRegisterFindCallback',
    'OrthancPluginRegisterIncomingHttpRequestFilter',  # Implemented through v2
    'OrthancPluginRegisterIncomingHttpRequestFilter2',
    'OrthancPluginRegisterMoveCallback',
    'OrthancPluginRegisterOnChangeCallback',
    'OrthancPluginRegisterOnStoredInstanceCallback',
    'OrthancPluginRegisterRestCallback',               # Implemented using OrthancPlugins::RegisterRestCallback
    'OrthancPluginRegisterRestCallbackNoLock',         # Implemented using OrthancPlugins::RegisterRestCallback
    'OrthancPluginRegisterWorklistCallback',
    'OrthancPluginRegisterIncomingCStoreInstanceFilter',
])

CUSTOM_METHODS = [
    {
        'class_name' : 'OrthancPluginFindQuery',
        'method_name' : 'GetFindQueryTagGroup',
        'implementation' : 'GetFindQueryTagGroup',
        'sdk_function' : 'OrthancPluginGetFindQueryTag',
    },
    {
        'class_name' : 'OrthancPluginFindQuery',
        'method_name' : 'GetFindQueryTagElement',
        'implementation' : 'GetFindQueryTagElement',
        'sdk_function' : 'OrthancPluginGetFindQueryTag',
    },
    {
        'class_name' : 'OrthancPluginWorklistAnswers',
        'method_name' : 'WorklistAddAnswer',
        'implementation' : 'WorklistAddAnswer',
        'sdk_function' : 'OrthancPluginWorklistAddAnswer',
    },
    {
        'class_name' : 'OrthancPluginDicomInstance',
        'method_name' : 'GetInstanceData',
        'implementation' : 'GetInstanceData',
        'sdk_function' : 'OrthancPluginGetInstanceData',
    },    
    {
        'class_name' : 'OrthancPluginImage',
        'method_name' : 'GetImageBuffer',
        'implementation' : 'GetImageBuffer',
        'sdk_function' : 'OrthancPluginGetImageBuffer',
    },    
]

for method in CUSTOM_METHODS:
    CUSTOM_FUNCTIONS.add(method['sdk_function'])


##
## Parse the command-line arguments
##

parser = argparse.ArgumentParser(description = 'Parse the Orthanc SDK.')
parser.add_argument('--libclang',
                    default = 'libclang-4.0.so.1',
                    help = 'manually provides the path to the libclang shared library')
parser.add_argument('--source',
                    default = os.path.join(os.path.dirname(__file__),
                                           '../Resources/Orthanc/Sdk-1.10.0/orthanc/OrthancCPlugin.h'),
                    help = 'Input C++ file')
parser.add_argument('--target', 
                    default = os.path.join(os.path.dirname(__file__),
                                           '../Sources/Autogenerated'),
                    help = 'Target folder')

args = parser.parse_args()



if len(args.libclang) != 0:
    clang.cindex.Config.set_library_file(args.libclang)

index = clang.cindex.Index.create()

tu = index.parse(args.source, [ ])

TARGET = os.path.realpath(args.target)



def ToUpperCase(name):
    s = ''
    for i in range(len(name)):
        if name[i].isupper():
            if len(s) == 0:
                s += name[i]
            elif name[i - 1].islower():
                s += '_' + name[i]
            elif (i + 1 < len(name) and
                  name[i - 1].islower() and
                  name[i + 1].isupper()):
                s += '_' + name[i]
            else:
                s += name[i]
        else:
            s += name[i].upper()
    return s



with open(os.path.join(ROOT, 'Enumeration.mustache'), 'r') as f:
    TEMPLATE = f.read()


classes = {}
enumerations = {}
globalFunctions = []
countAllFunctions = 0
countSupportedFunctions = 0

def IsSourceStringType(t):
    return (t.kind == clang.cindex.TypeKind.POINTER and
            t.get_pointee().kind == clang.cindex.TypeKind.CHAR_S and
            t.get_pointee().is_const_qualified())

def IsTargetStaticStringType(t):
    return (t.kind == clang.cindex.TypeKind.POINTER and
            t.get_pointee().kind == clang.cindex.TypeKind.CHAR_S and
            t.get_pointee().is_const_qualified())

def IsTargetDynamicStringType(t):
    return (t.kind == clang.cindex.TypeKind.POINTER and
            t.get_pointee().kind == clang.cindex.TypeKind.CHAR_S and
            not t.get_pointee().is_const_qualified())

def IsIntegerType(t):
    return (t.kind == clang.cindex.TypeKind.INT or
            t.spelling in [ 'int8_t', 'int16_t', 'int32_t', 'int64_t',
                            'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t'])

def IsFloatType(t):
    return t.kind == clang.cindex.TypeKind.FLOAT

def IsEnumerationType(t):
    return (t.kind == clang.cindex.TypeKind.TYPEDEF and
            t.spelling in enumerations)

def IsTargetMemoryBufferType(t):
    return (t.kind == clang.cindex.TypeKind.POINTER and
            not t.get_pointee().is_const_qualified() and
            t.get_pointee().spelling == 'OrthancPluginMemoryBuffer')    

def IsSourceMemoryBufferType(t):
    return (t.kind == clang.cindex.TypeKind.POINTER and
            t.get_pointee().kind == clang.cindex.TypeKind.VOID and
            t.get_pointee().is_const_qualified())

def IsClassType(t):
    return (t.kind == clang.cindex.TypeKind.POINTER and
            ((t.get_pointee().is_const_qualified() and
              t.get_pointee().spelling.startswith('const ') and
              t.get_pointee().spelling[len('const '):] in classes) or
             (not t.get_pointee().is_const_qualified() and
              t.get_pointee().spelling in classes)))

def IsSimpleSourceType(t):
    return (IsSourceStringType(t) or
            IsFloatType(t) or
            IsIntegerType(t) or
            IsEnumerationType(t) or
            IsSourceMemoryBufferType(t))

def IsVoidType(t):
    return t.kind == clang.cindex.TypeKind.VOID

def IsSupportedTargetType(t):
    return (IsVoidType(t) or
            IsIntegerType(t) or
            IsEnumerationType(t) or
            # Constructor of a class
            (t.kind == clang.cindex.TypeKind.POINTER and
             not t.get_pointee().is_const_qualified() and
             t.get_pointee().spelling in classes) or
            # "const char*" or "char*" outputs
            (t.kind == clang.cindex.TypeKind.POINTER and
             #not t.get_pointee().is_const_qualified() and
             t.get_pointee().kind == clang.cindex.TypeKind.CHAR_S))

def IsBytesArgument(args, index):
    return (index + 1 < len(args) and
            args[index].type.kind == clang.cindex.TypeKind.POINTER and
            args[index].type.get_pointee().kind == clang.cindex.TypeKind.VOID and
            args[index].type.get_pointee().is_const_qualified() and
            args[index + 1].type.spelling == 'uint32_t')

def CheckOnlySupportedArguments(args):
    j = 0
    while j < len(args):
        if IsBytesArgument(args, j):
            j += 2
        elif IsSimpleSourceType(args[j].type):
            j += 1
        else:
            return False
    return True


ORTHANC_TO_PYTHON_NUMERIC_TYPES = {
    # https://docs.python.org/3/c-api/arg.html#numbers
    'int' : {
        'type' : 'int',
        'format' : 'i',
        },
    'uint8_t' : {
        'type' : 'unsigned char',
        'format' : 'b',
        },
    'int32_t' : {
        'type' : 'long int',
        'format' : 'l',
        },
    'uint16_t' : {
        'type' : 'unsigned short',
        'format' : 'H',
        },
    'uint32_t' : {
        'type' : 'unsigned long',
        'format' : 'k',
        },
    'uint64_t' : {
        'type' : 'unsigned long long',
        'format' : 'K',
        },
    'float' : {
        'type' : 'float',
        'format' : 'f',
        }
    }


def GenerateFunctionBodyTemplate(cFunction, result_type, args):
    if not cFunction.startswith('OrthancPlugin'):
        raise Exception()
    
    func = {
        'c_function' : cFunction,
        'short_name' : cFunction[len('OrthancPlugin'):],
        'args' : [],
    }
    
    if IsIntegerType(result_type):
        func['return_long'] = True
    elif IsTargetDynamicStringType(result_type):
        func['return_dynamic_string'] = True
    elif IsTargetStaticStringType(result_type):
        func['return_static_string'] = True
    elif IsVoidType(result_type):
        func['return_void'] = True
    elif result_type.spelling == 'OrthancPluginErrorCode':
        func['return_error'] = True
    elif IsClassType(result_type):
        func['return_object'] = result_type.get_pointee().spelling
    elif IsTargetMemoryBufferType(result_type):
        func['return_bytes'] = True
    elif IsEnumerationType(result_type):
        func['return_enumeration'] = result_type.spelling
    else:
        raise Exception('Not supported: %s' % result_type.spelling)

    i = 0
    while i < len(args):
        a = {
            'name' : 'arg%d' % i,
            }

        if (IsIntegerType(args[i].type) or
            IsFloatType(args[i].type)):
            t = ORTHANC_TO_PYTHON_NUMERIC_TYPES[args[i].type.spelling]
            a['python_type'] = t['type']
            a['python_format'] = t['format']
            a['initialization'] = ' = 0'
            a['orthanc_cast'] = 'arg%d' % i
            func['args'].append(a)
        elif IsSourceStringType(args[i].type):
            a['python_type'] = 'const char*'
            a['python_format'] = 's'
            a['initialization'] = ' = NULL'
            a['orthanc_cast'] = 'arg%d' % i
            func['args'].append(a)
        elif IsEnumerationType(args[i].type):
            a['python_type'] = 'long int'
            a['python_format'] = 'l'
            a['initialization'] = ' = 0'
            a['orthanc_cast'] = 'static_cast<%s>(arg%d)' % (args[i].type.spelling, i)
            func['args'].append(a)
        elif IsBytesArgument(args, i):
            a['python_type'] = 'Py_buffer'
            # In theory, one should use "y*" (this is the recommended
            # way to accept binary data). However, this is not
            # available in Python 2.7
            a['python_format'] = 's*'
            a['orthanc_cast'] = 'arg%d.buf, arg%d.len' % (i, i)
            a['release'] = 'PyBuffer_Release(&arg%d);' % i
            func['args'].append(a)
            i += 1
        elif IsSourceMemoryBufferType(args[i].type):
            a['python_type'] = 'Py_buffer'
            a['python_format'] = 's*'
            a['orthanc_cast'] = 'arg%d.buf' % i
            a['release'] = 'PyBuffer_Release(&arg%d);' % i
            func['args'].append(a)
        else:
            raise Exception('Not supported: %s, %s' % (cFunction, args[i].spelling))

        i += 1
        
    func['tuple_format'] = '"%s", %s' % (
        ''.join(map(lambda x: x['python_format'], func['args'])),
        ', '.join(map(lambda x: '&' + x['name'], func['args'])))

    if len(func['args']) > 0:
        func['count_args'] = len(func['args'])
        func['has_args'] = True
        func['call_args'] = ', ' + ', '.join(map(lambda x: x['orthanc_cast'], func['args']))

    return func
             

for node in tu.cursor.get_children():
    if node.kind == clang.cindex.CursorKind.ENUM_DECL:
        if node.type.spelling.startswith('OrthancPlugin'):
            name = node.type.spelling

            values = []
            for item in node.get_children():
                if (item.kind == clang.cindex.CursorKind.ENUM_CONSTANT_DECL and
                    item.spelling.startswith(name + '_')):
                    values.append({
                        'key' : ToUpperCase(item.spelling[len(name)+1:]),
                        'value' : item.enum_value
                    })

            path = 'sdk_%s.impl.h' % name
            shortName = name[len('OrthancPlugin'):]

            with open(os.path.join(TARGET, path), 'w') as f:
                f.write(pystache.render(TEMPLATE, {
                    'name' : name,
                    'short_name' : shortName,
                    'values' : values,
                }))

            enumerations[name] = {
                'name' : name,
                'path' : path,
            }

    elif node.kind == clang.cindex.CursorKind.FUNCTION_DECL:
        if node.spelling.startswith('OrthancPlugin'):
            #if node.spelling != 'OrthancPluginWorklistGetDicomQuery':
            #    continue
            shortName = node.spelling[len('OrthancPlugin'):]
            
            # Check that the first argument is the Orthanc context
            args = list(filter(lambda x: x.kind == clang.cindex.CursorKind.PARM_DECL,
                               node.get_children()))

            if (len(args) == 0 or
                args[0].type.kind != clang.cindex.TypeKind.POINTER or
                args[0].type.get_pointee().spelling != 'OrthancPluginContext'):
                print('Not in the Orthanc SDK: %s()' % node.spelling)
                continue

            # Discard the context from the arguments
            countAllFunctions += 1
            args = args[1:]

            if node.spelling in CUSTOM_FUNCTIONS:
                print('Ignoring custom function that is manually implemented: %s()' % node.spelling)
                countSupportedFunctions += 1                

            elif not IsSupportedTargetType(node.result_type):
                print('*** UNSUPPORTED OUTPUT: %s' % node.spelling)
            
            elif (len(args) == 1 and
                  IsClassType(args[0].type) and
                  node.spelling.startswith('OrthancPluginFree')):
                print('Destructor: %s' % node.spelling)
                className = args[0].type.get_pointee().spelling
                classes[className]['destructor'] = node.spelling
                countSupportedFunctions += 1

            elif CheckOnlySupportedArguments(args):
                if IsClassType(node.result_type):
                    print('Constructor: %s' % node.spelling)
                else:
                    print('Simple global function: %s => %s' % (node.spelling, node.result_type.spelling))

                body = GenerateFunctionBodyTemplate(node.spelling, node.result_type, args)
                globalFunctions.append(body)
                countSupportedFunctions += 1

            elif (len(args) >= 2 and
                  IsTargetMemoryBufferType(args[0].type) and
                  CheckOnlySupportedArguments(args[1:])):
                print('Simple global function, returning bytes: %s' % node.spelling)

                body = GenerateFunctionBodyTemplate(node.spelling, args[0].type, args[1:])
                globalFunctions.append(body)
                countSupportedFunctions += 1
                
            elif (IsClassType(args[0].type) and
                  CheckOnlySupportedArguments(args[1:])):
                className = args[0].type.get_pointee().spelling

                print('Simple method of class %s: %s' % (className, node.spelling))
                if node.spelling in CUSTOM_FUNCTIONS:
                    raise Exception('Cannot overwrite an autogenerated method: %s()' % node.spelling)
                
                if className.startswith('const '):
                    className = className[len('const '):]
                
                method = GenerateFunctionBodyTemplate(node.spelling, node.result_type, args[1:])
                method['self'] = ', self->object_'
                classes[className]['methods'].append(method)
                countSupportedFunctions += 1

            elif (len(args) >= 2 and
                  IsTargetMemoryBufferType(args[0].type) and
                  IsClassType(args[1].type) and
                  CheckOnlySupportedArguments(args[2:])):
                className = args[1].type.get_pointee().spelling

                print('Simple method of class %s, returning bytes: %s' % (className, node.spelling))
                if node.spelling in CUSTOM_FUNCTIONS:
                    raise Exception('Cannot overwrite an autogenerated method: %s()' % node.spelling)
                
                if className.startswith('const '):
                    className = className[len('const '):]

                method = GenerateFunctionBodyTemplate(node.spelling, args[0].type, args[2:])
                method['self'] = ', self->object_'
                classes[className]['methods'].append(method)
                countSupportedFunctions += 1
            
            else:
                print('*** UNSUPPORTED INPUT: %s' % node.spelling)
            


    elif node.kind == clang.cindex.CursorKind.STRUCT_DECL:
        if (node.spelling.startswith('_OrthancPlugin') and
            node.spelling.endswith('_t') and
            node.spelling != '_OrthancPluginContext_t'):
            name = node.spelling[len('_') : -len('_t')]
            classes[name] = {
                'class_name' : name,
                'short_name' : name[len('OrthancPlugin'):],
                'methods' : [ ],
                'custom_methods' : [ ],
            }
                    



partials = {}

with open(os.path.join(ROOT, 'FunctionBody.mustache'), 'r') as f:
    partials['function_body'] = f.read()

renderer = pystache.Renderer(
    escape = lambda u: u,  # No escaping
    partials = partials,
)

with open(os.path.join(ROOT, 'Class.mustache'), 'r') as f:
    with open(os.path.join(ROOT, 'ClassMethods.mustache'), 'r') as g:
        classDefinition = f.read()
        classMethods = g.read()

        for method in CUSTOM_METHODS:
            classes[method['class_name']]['custom_methods'].append(method)

        for (key, value) in classes.items():
            with open(os.path.join(TARGET, 'sdk_%s.impl.h' % value['class_name']), 'w') as h:
                h.write(renderer.render(classDefinition, value))
            with open(os.path.join(TARGET, 'sdk_%s.methods.h' % value['class_name']), 'w') as h:
                h.write(renderer.render(classMethods, value))
        

def FlattenDictionary(source):
    result = []
    for (key, value) in source.items():
        result.append(value)
    return result


sortedClasses = sorted(FlattenDictionary(classes), key = lambda x: x['class_name'])
sortedEnumerations = sorted(FlattenDictionary(enumerations), key = lambda x: x['name'])
sortedGlobalFunctions = sorted(globalFunctions, key = lambda x: x['c_function'])

with open(os.path.join(ROOT, 'GlobalFunctions.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'sdk_GlobalFunctions.impl.h'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'global_functions' : globalFunctions,
        }))
            
with open(os.path.join(ROOT, 'sdk.cpp.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'sdk.cpp'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'classes' : sortedClasses,
            'enumerations' : sortedEnumerations,
            'global_functions' : globalFunctions,
        }))
            
with open(os.path.join(ROOT, 'sdk.h.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'sdk.h'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'classes' : sortedClasses,
        }))


print('')
print('Total functions in the SDK: %d' % countAllFunctions)
print('Total supported functions: %d' % countSupportedFunctions)
print('Coverage: %.0f%%' % (float(countSupportedFunctions) /
                            float(countAllFunctions) * 100.0))
