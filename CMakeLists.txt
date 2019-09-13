cmake_minimum_required(VERSION 3.1)
project(mono_bind)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_STANDARD 11)

find_package(Mono REQUIRED)

if(MONO_FOUND)
    message("Found Mono ${MONO_VERSION}")
else()
    message(FATAL_ERROR "Could not find Mono!")
endif()

function(csharp_dep target csproj)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${MSBUILD_EXECUTABLE} ${csproj} -property:OutDir=${CMAKE_BINARY_DIR} -property:OutputPath=${CMAKE_BINARY_DIR} -property:IntermediateOutputPath=${CMAKE_BINARY_DIR}/obj/)
endfunction()

add_definitions(-DMONO_PATH_STR=R\"_\(${MONO_ROOT}/Home\)_\")
include_directories(include 3rdparty/catch2 ${MONO_INCLUDE_DIR})

add_executable(HelloWorld example/HelloWorld/HelloHost/HelloHost.cpp)
target_link_libraries(HelloWorld ${MONO_LIBRARIES})
csharp_dep(HelloWorld ${CMAKE_SOURCE_DIR}/example/HelloWorld/Hello/Hello.csproj)

add_executable(Test test/Test/Test.cpp)
target_link_libraries(Test ${MONO_LIBRARIES})
csharp_dep(Test ${CMAKE_SOURCE_DIR}/test/TestLib/TestLib.csproj)
