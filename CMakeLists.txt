cmake_minimum_required(VERSION 3.16)
project(SFMLApp)

set(CMAKE_CXX_STANDARD 14)

#Matias Cam
set(SFML_INCLUDE_DIR "C:/Users/Matias/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "C:/Users/Matias/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib")
set(SFML_DIR "C:/Users/Matias/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

#Jorge Nicho
#set(SFML_INCLUDE_DIR "/home/rewieer/Libraries/SFML-2.5.1/include")
#set(SFML_LIBRARY_DIR "/home/rewieer/Libraries/SFML-2.5.1/lib")
#set(SFML_DIR "/home/theflilux/Descargas/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(SFMLApp main.cpp mazeHelper.cpp mazeHelper.h wallFollowing.cpp) #kruskall.cpp prim.cpp
target_link_libraries (SFMLApp sfml-graphics sfml-window sfml-system)