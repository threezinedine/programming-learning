cmake_minimum_required(VERSION 3.20)

project(NTTLang)

file(
    GLOB_RECURSE 
    SOURCE_FILES
    "src/*.cpp"
)

file(
    GLOB_RECURSE
    HEADER_FILES
    "src/*.h"
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    BASE_DIR=${CMAKE_SOURCE_DIR}
)