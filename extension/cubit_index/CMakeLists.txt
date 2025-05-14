cmake_minimum_required(VERSION 3.5...3.29)

project(CubitIndexExtension)

# Set compiler flags similar to original
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -fPIC")

# Linux-specific configuration
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories("/usr/include/x86_64-linux-gnu")
    include_directories("/usr/local/include")
    set(BOOST_LIBRARYDIR /usr/lib/x86_64-linux-gnu)
    set(BOOST_INCLUDEDIR /usr/include)
    set(Boost_NO_SYSTEM_PATHS on)
    find_package(Boost COMPONENTS filesystem program_options system REQUIRED)
    ADD_DEFINITIONS("-DLINUX")
ENDIF()

# Find URCU library
find_library(URCU_LIBRARIES 
    NAMES urcu
    HINTS "/usr/lib/x86_64-linux-gnu;/usr/local/lib")

# Add include paths
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

# Gather source files (keep your current list)
set(CUBIT_EXTENSION_FILES
    src/cubit/table.cpp
    src/cubit/table_lf.cpp
    src/cubit/table_lk.cpp

    src/nicolas/base_table.cpp
    src/nicolas/tablex.cpp
    src/nicolas/util.cpp
    src/nicolas/segBtv.cpp
    src/nicolas/perf.cpp

    src/fastbit/bitvector.cpp
    src/fastbit/fileManager.cpp
    src/fastbit/resource.cpp
    src/fastbit/util.cpp
    src/fastbit/array_t.cpp

    cubit_index_extension.cpp
)

# Remove test files (keep your current removals)
list(REMOVE_ITEM CUBIT_EXTENSION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/nicolas/nicolas.cpp")
list(REMOVE_ITEM CUBIT_EXTENSION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/disk/disk.cpp")
list(REMOVE_ITEM CUBIT_EXTENSION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/bench/bench.cpp")

# Build extensions
build_static_extension(cubit_index ${CUBIT_EXTENSION_FILES})
build_loadable_extension(cubit_index ${CUBIT_EXTENSION_FILES})

# Link to dependencies - add Boost libraries from original
target_link_libraries(cubit_index_loadable_extension 
    pthread 
    atomic 
    ${URCU_LIBRARIES} 
    ${Boost_LIBRARIES}
)

# Installation (keep your current)
install(
    TARGETS cubit_index_extension
    EXPORT "${DUCKDB_EXPORT_SET}"
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
)