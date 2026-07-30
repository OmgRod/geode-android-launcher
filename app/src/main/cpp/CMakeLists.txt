cmake_minimum_required(VERSION 3.21)

project(launcherfix)

add_library(launcherfix SHARED
    launcher-fix.cpp
    patcher.cpp
    GeometryDashVRBridge.cpp
)

target_compile_features(launcherfix PUBLIC cxx_std_20)
set_target_properties(launcherfix PROPERTIES CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)

set_target_properties(launcherfix PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    UNITY_BUILD ON
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
)

target_link_libraries(launcherfix PRIVATE log android fmt::fmt)

string(REPLACE "-fuse-ld=gold" "-fuse-ld=lld" CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY}")
string(REPLACE "-fuse-ld=gold" "-fuse-ld=lld" CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
