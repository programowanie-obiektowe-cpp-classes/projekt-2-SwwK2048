cmake_minimum_required(VERSION 3.20)
project(cpp-project CXX)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.1.0
)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(cpp-project ${SRC_FILES})
target_include_directories(cpp-project PUBLIC "${CMAKE_SOURCE_DIR}/include")
set_target_properties(cpp-project PROPERTIES CXX_STANDARD 23)

target_link_libraries(cpp-project PRIVATE fmt::fmt)

if(MINGW)
  target_link_libraries(cpp-project "-lstdc++exp")
endif()
