cmake_minimum_required(VERSION 3.2)

SET(PNAME "uconfig")

PROJECT(${PNAME})

INCLUDE(../cmake/ModuleImport.cmake)
INCLUDE(../cmake/ModuleDepends.cmake)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
INCLUDE(../cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

SET(UNIQS_VERSION_MAJOR "1")
SET(UNIQS_VERSION_MINOR "0")
SET(UNIQS_VERSION_PATCH "1")
SET(UNIQS_VERSION "${UNIQS_VERSION_MAJOR}.${UNIQS_VERSION_MINOR}.${UNIQS_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${UNIQS_VERSION}")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include/openxlsx/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/uniqs_xlsx_reader/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../cfg/)
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include/sol/)

FILE(GLOB project_src_cpp "src/*.cpp")
FILE(GLOB project_src_h "src/*.h")
FILE(GLOB uniqs_xlsx_reader_cpp "uniqs_xlsx_reader/*.cpp")
FILE(GLOB uniqs_xlsx_reader_h "uniqs_xlsx_reader/*.h")
FILE(GLOB cfg_src_cpp "cfg/*.cpp")
FILE(GLOB cfg_src_h "cfg/*.h")
FILE(GLOB project_include "include/*.h")

IF (WIN32)
    LIST(APPEND project_src_cpp)
ENDIF(WIN32)

ADD_EXECUTABLE(${PNAME} ${project_src_cpp} ${project_src_h} ${uniqs_xlsx_reader_cpp} ${uniqs_xlsx_reader_h} ${cfg_src_cpp} ${cfg_src_h} ${project_include})
ModuleDependLibraryStatic(${PNAME} lua)
ModuleDependLibraryStatic(${PNAME} uconfiglua)
ModuleDependLibraryShared(${PNAME} OpenXLSX)
# TARGET_LINK_LIBRARIES(${PNAME} ../../lib/uconfiglua)
