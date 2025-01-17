#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2020-2023 Osimis S.A., 2024-2025 Orthanc Team SRL, 2021-2025 Sebastien Jodogne, ICTEAM UCLouvain
# SPDX-License-Identifier: AGPL-3.0-or-later

##
## Python plugin for Orthanc
## Copyright (C) 2020-2023 Osimis S.A., Belgium
## Copyright (C) 2024-2025 Orthanc Team SRL, Belgium
## Copyright (C) 2021-2025 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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
import json
import os
import pystache
import re
import sys

ROOT = os.path.dirname(os.path.realpath(sys.argv[0]))


##
## Extract the default SDK version
##

with open(os.path.join(os.path.dirname(__file__), '..', 'OrthancSDKVersion.cmake'), 'r') as f:
    m = re.match('^set\(ORTHANC_SDK_VERSION "([^"]+)"\)$', f.read(), re.MULTILINE)
    assert(m != None)
    PLUGIN_SDK_VERSION = m.group(1)


##
## Parse the command-line arguments
##

parser = argparse.ArgumentParser(description = 'Generate Python code to wrap the Orthanc SDK.')
parser.add_argument('--model',
                    default = os.path.join(os.path.dirname(__file__),
                                           '../Resources/Orthanc/Sdk-%s/CodeModel.json' % PLUGIN_SDK_VERSION),
                    help = 'Input code model, as generated by the orthanc-java project')
parser.add_argument('--classes',
                    default = os.path.join(os.path.dirname(__file__),
                                           '../Resources/Orthanc/Sdk-%s/ClassDocumentation.json' % PLUGIN_SDK_VERSION),
                    help = 'Input description of classes, as defined in the orthanc-java project')
parser.add_argument('--target',
                    default = os.path.join(os.path.dirname(__file__),
                                           '../Sources/Autogenerated'),
                    help = 'Target folder')

args = parser.parse_args()



##
## Configuration of the custom primitives that are manually
## implemented (not autogenerated)
##

TARGET = os.path.realpath(args.target)


with open(os.path.join(ROOT, 'CustomMethods.json'), 'r') as f:
    CUSTOM_METHODS = json.loads(f.read())

with open(os.path.join(ROOT, 'CustomFunctions.json'), 'r') as f:
    CUSTOM_FUNCTIONS = json.loads(f.read())


partials = {}

with open(os.path.join(ROOT, 'FunctionBody.mustache'), 'r') as f:
    partials['function_body'] = f.read()

with open(os.path.join(ROOT, 'FunctionDocumentation.mustache'), 'r') as f:
    partials['function_documentation'] = f.read()

renderer = pystache.Renderer(
    escape = lambda u: u,  # No escaping
    partials = partials,
)



with open(args.model, 'r') as f:
    model = json.loads(f.read())

with open(args.classes, 'r') as f:
    classes_description = json.loads(f.read())


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


def ToLowerCase(name):
    s = ''
    for i in range(len(name)):
        if (name[i].isupper() and
            len(s) != 0):
            s += '_'
        s += name[i].lower()
    return s


def GetShortName(name):
    if not name.startswith('OrthancPlugin'):
        raise Exception()
    else:
        return name[len('OrthancPlugin'):]



ORTHANC_TO_PYTHON_NUMERIC_TYPES = {
    # https://docs.python.org/3/c-api/arg.html#numbers
    # https://en.wikipedia.org/wiki/C_data_types
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


def DocumentFunction(f):
    documentation = {}
    description = f['documentation'].get('description', [])
    if len(description) > 0:
        documentation['short_description'] = description[0].split('.') [0]
    documentation['description'] = map(lambda x: { 'text' : x }, description)

    args_declaration = []
    args_documentation = []
    for a in f['args']:
        arg_name = ToLowerCase(a['sdk_name'])
        if a['sdk_type'] == 'const char *':
            arg_type = 'str'
        elif a['sdk_type'] == 'float':
            arg_type = 'float'
        elif a['sdk_type'] in [ 'const_void_pointer_with_size', 'const void *' ]:
            arg_type = 'bytes'
        elif a['sdk_type'] == 'enumeration':
            arg_type = GetShortName(a['sdk_enumeration'])
        elif a['sdk_type'] == 'const_object':
            arg_type = GetShortName(a['sdk_class'])
        elif a['sdk_type'] in [ 'int32_t', 'uint32_t', 'uint8_t', 'uint16_t', 'uint64_t' ]:
            arg_type = 'int'
        elif a['sdk_type'] == 'Callable':
            # This is only used to generate the documentation file "orthanc.pyi"
            arg_type = a['callable_type']
        else:
            raise Exception('Argument type not implemented: %s' % a['sdk_type'])
        args_declaration.append('%s: %s' % (arg_name, arg_type))
        args_documentation.append({
            'name' : arg_name,
            'type' : arg_type,
            'text' : f['documentation']['args'] [a['sdk_name']],
        })

    documentation['args_declaration'] = ', '.join(args_declaration)
    documentation['args'] = args_documentation
    documentation['has_args'] = len(args_documentation) > 0
    documentation['has_return'] = True

    if f['return_sdk_type'] == 'enumeration':
        if f['return_sdk_enumeration'] == 'OrthancPluginErrorCode':
            documentation['has_return'] = False
            documentation['return_type'] = 'None'
        else:
            documentation['return_type'] = GetShortName(f['return_sdk_enumeration'])
    elif f['return_sdk_type'] == 'object':
        documentation['return_type'] = GetShortName(f['return_sdk_class'])
    elif f['return_sdk_type'] == 'void':
        documentation['has_return'] = False
        documentation['return_type'] = 'None'
    elif f['return_sdk_type'] == 'OrthancPluginMemoryBuffer *':
        documentation['return_type'] = 'bytes'
    elif f['return_sdk_type'] in [ 'char *', 'const char *' ]:
        documentation['return_type'] = 'str'
    elif f['return_sdk_type'] in [ 'int32_t', 'uint32_t', 'uint16_t', 'int64_t' ]:
        documentation['return_type'] = 'int'
    elif f['return_sdk_type'] == 'Dictionary':
        # This is only used to generate the documentation file "orthanc.pyi"
        documentation['return_type'] = 'dict'
    else:
        raise Exception('Return type not implemented: %s' % f['return_sdk_type'])

    if documentation['has_return']:
        documentation['return_text'] = f['documentation']['return']

    return documentation


def FormatFunction(f):
    answer = {
        'c_function' : f['c_function'],
        'short_name' : GetShortName(f['c_function']),
        'has_args' : len(f['args']) > 0,
        'count_args' : len(f['args']),
    }

    tuple_format = ''
    tuple_target = []
    call_args = []
    args = []

    for arg in f['args']:
        # https://docs.python.org/3/c-api/arg.html
        if arg['sdk_type'] in [ 'const void *', 'const_void_pointer_with_size' ]:
            args.append({
                'name' : arg['name'],
                'python_type' : 'Py_buffer',
                'release' : 'PyBuffer_Release(&%s);' % arg['name'],
            })
            tuple_format += 's*'
        elif arg['sdk_type'] == 'const char *':
            args.append({
                'name' : arg['name'],
                'python_type' : 'const char*',
                'initialization' : ' = NULL',
            })
            tuple_format += 's'
        elif arg['sdk_type'] == 'enumeration':
            args.append({
                'name' : arg['name'],
                'python_type' : 'long int',
                'initialization' : ' = 0',
            })
            tuple_format += 'l'
        elif arg['sdk_type'] == 'const_object':
            args.append({
                'name' : arg['name'],
                'python_type' : 'PyObject*',
                'initialization' : ' = NULL',
                'check_object_type' : arg['sdk_class'],
            })
            tuple_format += 'O'
        elif arg['sdk_type'] in ORTHANC_TO_PYTHON_NUMERIC_TYPES:
            t = ORTHANC_TO_PYTHON_NUMERIC_TYPES[arg['sdk_type']]
            args.append({
                'name' : arg['name'],
                'python_type' : t['type'],
                'initialization' : ' = 0',
            })
            tuple_format += t['format']
        else:
            print('Ignoring function with unsupported argument type: %s(), type = %s' % (f['c_function'], arg['sdk_type']))
            return None

        tuple_target.append('&' + arg['name'])

        if arg['sdk_type'] == 'const void *':
            call_args.append(arg['name'] + '.buf')
        elif arg['sdk_type'] == 'const_void_pointer_with_size':
            call_args.append(arg['name'] + '.buf')
            call_args.append(arg['name'] + '.len')
        elif arg['sdk_type'] == 'enumeration':
            call_args.append('static_cast<%s>(%s)' % (arg['sdk_enumeration'], arg['name']))
        elif arg['sdk_type'] == 'const_object':
            call_args.append('%s == Py_None ? NULL : reinterpret_cast<sdk_%s_Object*>(%s)->object_' % (
                arg['name'], arg['sdk_class'], arg['name']))
        else:
            call_args.append(arg['name'])

    answer['args'] = args

    if f['return_sdk_type'] == 'void':
        answer['return_void'] = True
    elif f['return_sdk_type'] in [ 'int32_t', 'uint32_t', 'int64_t' ]:
        answer['return_long'] = True
    elif f['return_sdk_type'] == 'OrthancPluginMemoryBuffer *':
        answer['return_bytes'] = True
    elif f['return_sdk_type'] == 'enumeration':
        if f['return_sdk_enumeration'] == 'OrthancPluginErrorCode':
            answer['return_error'] = True
        else:
            answer['return_enumeration'] = f['return_sdk_enumeration']
    elif f['return_sdk_type'] == 'char *':
        answer['return_dynamic_string'] = True
    elif f['return_sdk_type'] == 'const char *':
        answer['return_static_string'] = True
    elif f['return_sdk_type'] == 'object':
        answer['return_object'] = f['return_sdk_class']
    else:
        print('Ignoring function with unsupported return type: %s(), type = %s' % (f['c_function'], f['return_sdk_type']))
        return None

    answer['tuple_format'] = ', '.join([ '"' + tuple_format + '"' ] + tuple_target)

    if 'documentation' in f:
        answer['documentation'] = DocumentFunction(f)

    if len(call_args) > 0:
        answer['call_args'] = ', ' + ', '.join(call_args)

    return answer



globalFunctions = []
customFunctions = []

for f in model['global_functions']:
    g = FormatFunction(f)
    if g != None:
        globalFunctions.append(g)

for f in CUSTOM_FUNCTIONS:
    f['documentation'] = DocumentFunction(f)
    customFunctions.append(f)


enumerations = []

with open(os.path.join(ROOT, 'Enumeration.mustache'), 'r') as f:
    ENUMERATION_TEMPLATE = f.read()

for e in model['enumerations']:
    values = []
    for value in e['values']:
        values.append({
            'key' : ToUpperCase(value['key']),
            'value' : value['value'],
            'documentation' : value['documentation'],
        })

    enumerations.append({
        'name' : e['name'],
        'short_name' : GetShortName(e['name']),
        'path' : 'sdk_%s.impl.h' % e['name'],
        'values' : values,
        'documentation' : e['documentation'],
    })

    path = 'sdk_%s.impl.h' % e['name']

    with open(os.path.join(TARGET, path), 'w') as f:
        f.write(pystache.render(ENUMERATION_TEMPLATE, {
            'name' : e['name'],
            'short_name' : GetShortName(e['name']),
            'values' : values,
        }))


classes = []

countDestructors = 0

for c in model['classes']:
    methods = []

    for m in c['methods']:
        g = FormatFunction(m)
        if g != None:
            g['self'] = ', self->object_'
            methods.append(g)

    custom_methods = []

    if c['name'] in CUSTOM_METHODS:
        for custom_method in CUSTOM_METHODS[c['name']]:
            custom_method['self'] = True   # Indicates that this is a method
            custom_method['documentation'] = DocumentFunction(custom_method)
            custom_methods.append(custom_method)

    classes.append({
        'description' : classes_description[c['name']],
        'class_name' : c['name'],
        'short_name' : GetShortName(c['name']),
        'methods' : methods,
        'custom_methods' : sorted(custom_methods, key = lambda x: x['short_name']),
    })

    if 'destructor' in c:
        countDestructors += 1
        classes[-1]['destructor'] = c['destructor']




with open(os.path.join(ROOT, 'Class.mustache'), 'r') as f:
    with open(os.path.join(ROOT, 'ClassMethods.mustache'), 'r') as g:
        classDefinition = f.read()
        classMethods = g.read()

        for c in classes:
            with open(os.path.join(TARGET, 'sdk_%s.impl.h' % c['class_name']), 'w') as h:
                h.write(renderer.render(classDefinition, c))
            with open(os.path.join(TARGET, 'sdk_%s.methods.h' % c['class_name']), 'w') as h:
                h.write(renderer.render(classMethods, c))


sortedClasses = sorted(classes, key = lambda x: x['class_name'])
sortedEnumerations = sorted(enumerations, key = lambda x: x['name'])
sortedGlobalFunctions = sorted(globalFunctions, key = lambda x: x['c_function'])
sortedCustomFunctions = sorted(customFunctions, key = lambda x: x['short_name'])

with open(os.path.join(ROOT, 'GlobalFunctions.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'sdk_GlobalFunctions.impl.h'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'global_functions' : sortedGlobalFunctions,
            'custom_functions' : sortedCustomFunctions,
        }))

with open(os.path.join(ROOT, 'sdk.cpp.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'sdk.cpp'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'classes' : sortedClasses,
            'enumerations' : sortedEnumerations,
            'global_functions' : sortedGlobalFunctions,
            'custom_functions' : sortedCustomFunctions,
        }))

with open(os.path.join(ROOT, 'sdk.h.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'sdk.h'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'classes' : sortedClasses,
        }))

with open(os.path.join(ROOT, 'PythonDocumentation.mustache'), 'r') as f:
    with open(os.path.join(TARGET, 'orthanc.pyi'), 'w') as h:
        h.write(renderer.render(f.read(), {
            'classes' : sortedClasses,
            'enumerations' : sortedEnumerations,
            'global_functions' : sortedGlobalFunctions,
            'custom_functions' : sortedCustomFunctions,
        }))



##
## Print statistics
##

countWrappedMethods = 0
countCustomMethods = 0
for c in sortedClasses:
    countWrappedMethods += len(c['methods'])
    countCustomMethods += len(c['custom_methods'])

print('\nNumber of automatically wrapped global functions: %d' % len(sortedGlobalFunctions))
print('Number of automatically wrapped methods: %d' % countWrappedMethods)
print('Number of automatically wrapped destructors: %d' % countDestructors)
print('Number of manually implemented (custom) global functions: %d' % len(sortedCustomFunctions))
print('Number of manually implemented (custom) methods: %d' % countCustomMethods)

totalWrapped = (len(sortedGlobalFunctions) + countWrappedMethods + countDestructors)
print('\nTotal number of automatically wrapped functions (including destructors): %d' % totalWrapped)
print('NB: This number must correspond to "ParseOrthancSDK.py" in "orthanc-java"')

total = totalWrapped + len(sortedCustomFunctions) + countCustomMethods
print('\n=> Total number of functions or methods in the Python SDK: %d\n' % total)
