find_package(Git)

if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        OUTPUT_VARIABLE NDS_REVISION_HASH
        ERROR_QUIET
        )
    if(NOT ${NDS_REVISION_HASH} STREQUAL "")
        string(STRIP ${NDS_REVISION_HASH} NDS_REVISION_HASH)
    endif()
    message(STATUS "Current git revision is ${NDS_REVISION_HASH}")
else()
    set(NDS_REVISION_HASH "unknown")
endif()
