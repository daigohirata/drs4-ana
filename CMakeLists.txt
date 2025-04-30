############# general settings #############

# CMake version
cmake_minimum_required(VERSION 3.10)
project(DRA4AnalysesTools
        DESCRIPTION "DRS4 analyses software"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only UNIX OSes
if (NOT UNIX)
    message(FATAL_ERROR "Non UNIX OSes are not supported")
endif ()

# APPLE stuff
if (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
endif ()

# Set default install path
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "default install path" FORCE)
endif ()

# install namespace
set(DRS4_ANALYSES_INSTALL_NAMESPACE drs4-ana)
set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib/${DRS4_ANALYSES_INSTALL_NAMESPACE})
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include/${DRS4_ANALYSES_INSTALL_NAMESPACE})

############## find packages #############

# Boost
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.69 REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libs: ${Boost_LIBRARIES}")

# ROOT を探す
find_package(ROOT REQUIRED COMPONENTS Tree RIO Core)
include_directories(${ROOT_INCLUDE_DIRS})
message(STATUS "ROOT version: ${ROOT_VERSION}")
message(STATUS "ROOT include dir: ${ROOT_INCLUDE_DIRS}")
message(STATUS "ROOT libs: ${ROOT_LIBRARIES}")

# DRS4-ana include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB DRS4_ANA_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")


############# sub directories #############
add_subdirectory(process)
