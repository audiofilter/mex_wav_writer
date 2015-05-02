cmake_minimum_required(VERSION 2.8.4)

if (POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

# For mex-it and Cmake modules
set(MEX_IT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../mex-it")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MEX_IT_DIR})

SET(CMAKE_BUILD_TYPE "DEBUG")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -fPIC")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -DMX_COMPAT_32 -DMATLAB_MEX_FILE")

find_package(OCTAVE)
if (OCTAVE_FOUND)
  message( STATUS "Found Octave")
	include_directories(${OCTAVE_INCLUDE_DIRS} ${MEX_IT_DIR}/..)
	octave_add_oct(wav_writer SOURCES wav_writer.cpp wavefile.cpp EXTENSION "mex")
	SET(LIBRARY_OUTPUT_PATH ..)
else()
  message( STATUS "No Octave - Can't build a mex, done!")
endif( OCTAVE_FOUND )


