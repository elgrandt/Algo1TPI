cmake_minimum_required(VERSION 3.6)
project(salaDeReunion)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)


set(SOURCE_FILES main.cpp solucion.cpp Funciones_TPI.cpp ejercicios.h tests/pruebaAudioTEST.cpp tests/grabacionValidaTEST.cpp tests/elAcaparadorTEST.cpp tests/distanciasTEST.cpp tests/encontrarAparicionTEST.cpp tests/ardillizarTEST.cpp tests/silenciosTEST.cpp tests/sinSilenciosTEST.cpp tests/flashElPerezosoTEST.cpp tests/hayQuilombosTEST.cpp tests/compararSilenciosTEST.cpp tests/encontrarMejorUmbralTEST.cpp tests/pruebaAudioTEST.cpp)
add_executable(salaDeReunion ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "-g -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

target_link_libraries(salaDeReunion gtest gtest_main)
