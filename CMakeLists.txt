### Configuration ###
cmake_minimum_required(VERSION 3.0.0)

project(OsuBot VERSION 0.1.0)

# C++ Compilation specs
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Main Executable ###
add_executable(${PROJECT_NAME})
set(SRC_DIR "source/")

# generate Config file (CONFIG_FILE var)
find_file(__CONFIG_FILE
    ${PROJECT_NAME}Config.h.in
    ${CMAKE_SOURCE_DIR}/cmake
)
if(EXISTS ${__CONFIG_FILE})
    string(REGEX REPLACE ".*/([^/]*)\\.in" "\\1" CONFIG_FILE ${__CONFIG_FILE})
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_CONFIG_FILE)
    configure_file(${__CONFIG_FILE} ${CMAKE_SOURCE_DIR}/${SRC_DIR}${CONFIG_FILE})
else()
    set(CONFIG_FILE "")
endif()
unset(__CONFIG_FILE CACHE)

# source files
set(SRC
    main.cpp
    Parser/OsuKey.cpp
    Parser/OsuParser.cpp
)
set(INC
    ${CONFIG_FILE}
    Parser/OsuKey.hpp
    Parser/OsuParser.hpp
)

list(TRANSFORM SRC PREPEND ${SRC_DIR})
list(TRANSFORM INC PREPEND ${SRC_DIR})

# build target
target_sources(${PROJECT_NAME} PRIVATE ${SRC} ${INC})
target_include_directories(${PROJECT_NAME} PRIVATE
                           ${SRC_DIR}
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -g)


### Tests ###
option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()
    set(TEST_SRC_DIR ${CMAKE_SOURCE_DIR}/tests/source)
    add_subdirectory(${TEST_SRC_DIR})
endif()


### Installer ###
# Maybe one day ?