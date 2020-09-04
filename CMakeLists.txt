# reference: http://www.open3d.org/docs/release/tutorial/C++/cplusplus_interface.html
cmake_minimum_required(VERSION 3.10)
project(open3d_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


if(WIN32)
    find_package(Open3D HINTS ${CMAKE_INSTALL_PREFIX}/CMake)
else()
    find_package(Open3D HINTS ${CMAKE_INSTALL_PREFIX}/lib/CMake)
    list(APPEND Open3D_LIBRARIES dl)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${Open3D_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Open3D_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Open3D_EXE_LINKER_FLAGS}")


find_package(gflags REQUIRED)
include_directories(${gflags_INCLUDE_DIR})

# Set OS-specific things here
if(WIN32)
    if (ENABLE_GUI)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
        # Filament is built with /MT[d], but by default CMake automatically
        # sets "/MD" and "/MDd". They can't coexist, so we need to replace them.
        string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
        string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
        string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    endif()
elseif(CYGWIN)
elseif(APPLE)
elseif(UNIX)
    add_definitions(-DUNIX)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-unused-result)
    add_definitions(-O3)
endif(WIN32)

# Open3D
if (Open3D_FOUND)
    message(STATUS "Found Open3D ${Open3D_VERSION}")
    message(STATUS "open3d_include -> ${Open3D_INCLUDE_DIRS}")
    message(STATUS "open3d_libs -> ${Open3D_LIBRARIES}")

    # link_directories must be before add_executable
    link_directories(${Open3D_LIBRARY_DIRS})
    include_directories(${Open3D_INCLUDE_DIRS})


    add_executable(camera_pose_trajectory camera_pose_trajectory.cpp)
    target_link_libraries(camera_pose_trajectory gflags ${Open3D_LIBRARIES})
    #target_include_directories(camera_pose_trajectory PUBLIC ${Open3D_INCLUDE_DIRS})

    # Hot fix windows dll not found issue, assumming we're using the Release build
    option(BUILD_SHARED_LIBS "Whether Open3D was build as shared library" OFF)
    if(WIN32 AND BUILD_SHARED_LIBS)
        message("Will copy Open3D.dll to ${CMAKE_CURRENT_BINARY_DIR}/Release")
        add_custom_command(TARGET camera_pose_trajectory POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                                ${CMAKE_INSTALL_PREFIX}/bin/Open3D.dll
                                ${CMAKE_CURRENT_BINARY_DIR}/Release)
    endif()
    if(WIN32 AND ENABLE_GUI)
        message("Will copy SDL2.dll to ${CMAKE_CURRENT_BINARY_DIR}/Release")
e       add_custom_command(TARGET camera_pose_trajectory POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                                ${CMAKE_INSTALL_PREFIX}/lib/SDL2.dll
                                ${CMAKE_CURRENT_BINARY_DIR}/Release)
    endif()

else ()
    message(SEND_ERROR "Open3D not found")
endif ()
