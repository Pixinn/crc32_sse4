CMAKE_MINIMUM_REQUIRED( VERSION 2.8.3 )
set(PROJECT_NAME “CRC32C_SSE4”)
PROJECT("Crc32c")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# COMPILER SETTINGS
if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -pthread -march=native")
    if( APPLE )
  	  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
    	SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++" )
    	SET( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++" )
    	SET( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -stdlib=libc++" )
  endif( APPLE )
endif()
# -----------------


set(FOLDER_LIB_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(FOLDER_LIB_SRC "src")
set(FOLDER_TESTS_SRC "test")



set(PUBLIC  ${FOLDER_LIB_INCLUDE}/Crc.hpp)
set(PRIVATE ${FOLDER_LIB_SRC}/Crc.cpp
            ${FOLDER_LIB_SRC}/crc32c_sse42.cpp
            ${FOLDER_LIB_SRC}/crc32c.h ${FOLDER_LIB_SRC}/crc32c.cpp)
set(SOURCES ${PUBLIC} ${PRIVATE})

include_directories(${FOLDER_LIB_INCLUDE})
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

source_group("Public" FILES ${PUBLIC})
source_group("Private" FILES ${PRIVATE})

add_subdirectory(${FOLDER_TESTS_SRC})
