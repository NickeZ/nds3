cmake_minimum_required(VERSION 2.8.8)

project(nds3 C CXX)

# Include path for additional cmake modules
#-------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

# Get version from version.h
#---------------------------
set(versionfile ${CMAKE_CURRENT_SOURCE_DIR}/../include/nds3/version.h)
include(parse_version)

# User Options
#-------------
option(BUILD_SHARED_LIBS "Build as shared library" ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug"
        CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

# Set compiler flags
#-------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-as-needed")

# Set pre-processor definitions
#------------------------------
add_definitions(-DNDS3_DLL)
add_definitions(-DNDS3_DLL_EXPORTS)

# Specify include and source files
#---------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

file(
  GLOB
  nds_include_interface
  "${CMAKE_CURRENT_SOURCE_DIR}/../include/nds3/*.h"
)
file(
  GLOB
  nds_include_impl
  "${CMAKE_CURRENT_SOURCE_DIR}/../include/nds3/impl/*.h"
)
file(
  GLOB
  nds_sources
  "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp"
)

# Add the source files to the nds3 library
#-----------------------------------------
add_library(nds3 ${nds_sources} ${nds_include_interface} ${nds_include_impl})

# Add dependencies to the nds3 library
#-------------------------------------
find_package(Threads REQUIRED)
target_link_libraries(nds3 rt dl ${CMAKE_THREAD_LIBS_INIT})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(nds3 gcov)
endif()

# Settings for installers
#------------------------
set(CPACK_PACKAGE_NAME "nds3Core")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_VENDOR "Cosylab d.o.o.")
set(CPACK_PACKAGE_CONTACT "Niklas Claesson")
set(
  CPACK_PACKAGE_DESCRIPTION_SUMMARY
  "Nominal device support for control systems drivers (core libraries)"
)

set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_REQUIRES "libstdc++-devel, glibc-devel")

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "x86_64")

set(CPACK_RPM_PACKAGE_DEBUG 1)

set(
  CPACK_PACKAGE_FILE_NAME
  "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}"
)

execute_process(
  COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
  OUTPUT_VARIABLE DEB_HOST_MULTIARCH
  ERROR_QUIET
)

# Install into correct lib directory for rhel and debian based dists.
if(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set(LIBDEST "lib")
else()
  if(DEB_HOST_MULTIARCH STREQUAL "x86_64-linux-gnu\n")
    set(LIBDEST "lib/x86_64-linux-gnu")
  else()
    set(LIBDEST "lib64")
  endif()
endif()

install(
  TARGETS nds3
  PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  LIBRARY
    DESTINATION "${LIBDEST}"
    COMPONENT "Shared Library"
  ARCHIVE
    DESTINATION "${LIBDEST}"
    COMPONENT "Static Library"
)
install(
  FILES ${nds_include_interface}
  DESTINATION include/nds3
  COMPONENT "Included files"
)
install(
  FILES ${nds_include_impl}
  DESTINATION include/nds3/impl
  COMPONENT "Included files for control system developers"
)

include(CPack)
