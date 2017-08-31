cmake_minimum_required(VERSION 2.6)

project(nds3examples C CXX)

set(VERSION "1.0.0")

# User Options
#-------------
option(BUILD_SHARED_LIBS "Build as shared libraries" ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug"
        CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

# Set compiler flags
#-------------------
set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic"
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

# Set pre-processor definitions
#------------------------------
add_definitions(-DNDS3_DLL)

# Specify include and source files
#---------------------------------
include_directories(
  ${ADDITIONAL_INCLUDE}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
)

add_library(
  oscilloscope
  "${CMAKE_CURRENT_SOURCE_DIR}/../oscilloscope/oscilloscope.cpp"
)
add_library(
  oscilloscopemultichannel
  "${CMAKE_CURRENT_SOURCE_DIR}/../oscilloscopeMultiChannel/oscilloscopeMultiChannel.cpp"
)
add_library(
  thermometer
  "${CMAKE_CURRENT_SOURCE_DIR}/../thermometer/thermometer.cpp"
)
add_library(
  rpcsquare
  "${CMAKE_CURRENT_SOURCE_DIR}/../rpcSquare/rpcSquare.cpp"
)

# Add dependencies to the drivers
#--------------------------------
find_package(Threads REQUIRED)
find_library(nds3_library NAMES nds3 PATHS ${LIBRARY_LOCATION})
mark_as_advanced(nds3_library)
target_link_libraries(oscilloscope ${nds3_library} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(oscilloscopemultichannel ${nds3_library} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thermometer ${nds3_library} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(rpcsquare ${nds3_library} ${CMAKE_THREAD_LIBS_INIT})

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
  TARGETS oscilloscope oscilloscopemultichannel thermometer rpcsquare
  PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    LIBRARY DESTINATION "${LIBDEST}/nds3"
    COMPONENT "Example shared drivers"
    ARCHIVE DESTINATION "${LIBDEST}/nds3"
    COMPONENT "Example static drivers"
)
