cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME cpp-bencode)
project(PROJECT_NAME)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Headers
  "include/bencode/object.hpp"
  "include/bencode/common.hpp"
  "include/bencode/encoder.hpp"
)

set(Sources
  "src/object.cpp"
  "src/encoder.cpp"
)

add_library(${PROJECT_NAME} ${Headers} ${Sources})

target_include_directories(
  ${PROJECT_NAME}
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include/bencode
    INTERFACE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (BENCODE_BUILD_TESTING)
  add_subdirectory(test)
endif()