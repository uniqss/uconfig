cmake_minimum_required(VERSION 3.2)

SET(PNAME "lua")

PROJECT(${PNAME})

INCLUDE(../cmake/ModuleImport.cmake)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
INCLUDE(../cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

SET(UNIQS_VERSION_MAJOR "1")
SET(UNIQS_VERSION_MINOR "0")
SET(UNIQS_VERSION_PATCH "1")
SET(UNIQS_VERSION "${UNIQS_VERSION_MAJOR}.${UNIQS_VERSION_MINOR}.${UNIQS_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${UNIQS_VERSION}")

FILE(GLOB project_src_cpp "src/*.c")
FILE(GLOB project_src_h "src/*.h")
FILE(GLOB project_include "include/*.h")

IF (WIN32)
    LIST(APPEND project_src_cpp)
ENDIF(WIN32)

LIST(FILTER project_src_cpp EXCLUDE REGEX "lua.c$")
LIST(FILTER project_src_cpp EXCLUDE REGEX "luac.c$")
LIST(FILTER project_src_cpp EXCLUDE REGEX "wmain.c$")

# ADD_LIBRARY(${PNAME} SHARED ${project_src_cpp} ${project_src_h} ${project_include})
ADD_LIBRARY(${PNAME} STATIC ${project_src_cpp} ${project_src_h} ${project_include})

#SET(UNIQS_LIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../lib/)

#find_library(LIB_event event HINTS ${UNIQS_LIB_ROOT})
#message("find_library path: ${UNIQS_LIB_ROOT} find_result:${LIB_event}")

#find_library(LIB_core event_core HINTS ${UNIQS_LIB_ROOT})
#message("find_library path: ${UNIQS_LIB_ROOT}  find_result:${LIB_core}")

#find_library(LIB_extra event_extra HINTS ${UNIQS_LIB_ROOT})
#message("find_library path: ${UNIQS_LIB_ROOT}  find_result:${LIB_extra}")

SET(EXTRALIBS "")
if (${MSVC})
    #SET(EXTRALIBS "Iphlpapi")
endif()

#TARGET_LINK_LIBRARIES(${PNAME} PUBLIC ${LIB_event} ${LIB_core} ${LIB_extra} ${EXTRALIBS})
TARGET_LINK_LIBRARIES(${PNAME} PUBLIC ${EXTRALIBS})
