# Copyright (C) 2016-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# All rights reserved.
#
# Author: Volker Krause <volker.krause@kdab.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

find_program(QMLLINT_EXECUTABLE qmllint)
if (QMLLINT_EXECUTABLE)
    if(NOT QMLLINT_IS_WORKING)
        # Try to fix common problems on Debian-based distros -- they provide /usr/bin/qmllint, which is a symlink to
        # /usr/lib/x86_64-linux-gnu/qt4/bin/qmllint (or the Qt5 version of it). The actual executable is part of different
        # package, so might not even be installed => double-check whether qmllint is working by executing it
        execute_process(COMMAND ${QMLLINT_EXECUTABLE} --version RESULT_VARIABLE _qmllint_result OUTPUT_QUIET ERROR_QUIET)
        if (_qmllint_result EQUAL 0)
            set(QMLLINT_IS_WORKING TRUE CACHE BOOL "Whether the found qmllint executable is actually usable" FORCE)
        endif()
    endif()
    if(QMLLINT_IS_WORKING)
        set(QmlLint_FOUND TRUE)
    endif()
endif()

macro(qml_find_plugin_dir)
    find_package(Qt5Core)
    get_target_property(QT_QMAKE_EXECUTABLE ${Qt5Core_QMAKE_EXECUTABLE} IMPORTED_LOCATION)
    if(NOT QT_QMAKE_EXECUTABLE)
        message(FATAL_ERROR "qmake is not found.")
    endif()

    # execute the command "qmake -query QT_INSTALL_PLUGINS" to get the path of plugins dir.
    execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_QML/raw
            OUTPUT_VARIABLE QML_PLUGIN_DIR_RAW
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )
    if(NOT QML_PLUGIN_DIR_RAW)
        message(FATAL_ERROR "Qt5 plugin directory cannot be detected.")
    endif()
    set(QML_PLUGIN_INSTALL_DIR ${QML_PLUGIN_DIR_RAW})
endmacro()

qml_find_plugin_dir()

add_custom_target(qmllint COMMAND echo "qmllint" )

# validate a list of qml files
function(qml_lint)
    set(BLACKLIST Tooltip.qml Authentication.qml MessageBoxDialog.qml Prompt.qml Alert.qml Reload.qml Confirmation.qml)
    if (NOT QMLLINT_EXECUTABLE OR NOT QmlLint_FOUND)
        return()
    endif()

    foreach(_file ${ARGN})
        get_filename_component(_file_abs ${_file} ABSOLUTE)
        get_filename_component(_file_name ${_file} NAME)

        if (NOT ${_file_name} IN_LIST BLACKLIST)
            add_custom_command(
                    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_file_name}.qmllint
    #                COMMAND ${QMLLINT_EXECUTABLE} ${_file_abs}
                    COMMAND ${QMLLINT_EXECUTABLE} ${_file_abs} -U -i ${QML_IMPORT_PATH}/MellowPlayer/cpp.qmltypes -I ${QML_IMPORT_PATH} -I ${QML_PLUGIN_INSTALL_DIR}
                    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/${_file_name}.qmllint
                    MAIN_DEPENDENCY ${_file_abs}
            )
            add_custom_target(qmllint-${_file_name} DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_file_name}.qmllint)
            add_dependencies(qmllint qmllint-${_file_name})
        endif()
    endforeach()
endfunction()
