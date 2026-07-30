cmake_minimum_required(VERSION 3.21)

project(launcherfix)

add_library(launcherfix SHARED
    launcher-fix.cpp
    patcher.cpp
    GeometryDashVRBridge.cpp

    vr/VRManager.cpp
    vr/VRRenderer.cpp
    vr/HookManager.cpp

    vr/OpenXR/OpenXRManager.cpp
)

target_include_directories(launcherfix PRIVATE
    .
    vr
    vr/OpenXR
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
    UNITY_BUILD OFF
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
)

string(REPLACE "-fuse-ld=gold" "-fuse-ld=lld" CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY}")
string(REPLACE "-fuse-ld=gold" "-fuse-ld=lld" CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")

include(cmake/CPM.cmake)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(OPENXR_BUILD_LOADER ON CACHE BOOL "" FORCE)

set(DYNAMIC_LOADER OFF CACHE BOOL "Build OpenXR as a static library" FORCE)

CPMAddPackage("gh:KhronosGroup/OpenXR-SDK#release-1.1.61")
CPMAddPackage("gh:g-truc/glm#1.0.3")

target_link_libraries(launcherfix PRIVATE 
    log 
    android 
    fmt::fmt
    OpenXR::openxr_loader 
    glm::glm 
    EGL 
    GLESv3
)
