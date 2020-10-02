### Configuration ###
cmake_minimum_required(VERSION 3.0.0)

project(OsuBot VERSION 0.1.0)

# C++ Compilation specs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


### Main Executable ###
add_executable(${CMAKE_PROJECT_NAME})
set(REL_SRC_DIR "source")
set(SRC_DIR ${PROJECT_SOURCE_DIR}/${REL_SRC_DIR})

# generate Config file (CONFIG_FILE var)
find_file(__CONFIG_FILE
    ${CMAKE_PROJECT_NAME}Config.h.in
    ${PROJECT_SOURCE_DIR}/cmake
)
if(EXISTS ${__CONFIG_FILE})
    string(REGEX REPLACE ".*/([^/]*)\\.in" "\\1" CONFIG_FILE ${__CONFIG_FILE})
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE HAS_CONFIG_FILE)
    configure_file(${__CONFIG_FILE} ${SRC_DIR}/${CONFIG_FILE})
else()
    set(CONFIG_FILE "")
endif()
unset(__CONFIG_FILE CACHE)


# add Logger Library
add_subdirectory(${SRC_DIR}/Logger)
target_link_libraries(${CMAKE_PROJECT_NAME} Logger)
file(MAKE_DIRECTORY ${OsuBot_BINARY_DIR}/logs)#keep the build folder clean

# add jhack Library
add_subdirectory(${PROJECT_SOURCE_DIR}/externals/jhack)
target_link_libraries(${CMAKE_PROJECT_NAME} jhack)

# source files
set(SRC
    main.cpp
    OsuBot.cpp
    Parser/OsuKey.cpp
    Parser/OsuParser.cpp
    Finder/OsuFinder.cpp
)
set(INC
    ${CONFIG_FILE}
    OsuBot.hpp
    Parser/OsuKey.hpp
    Parser/OsuParser.hpp
    Finder/OsuFinder.hpp
)

list(TRANSFORM SRC PREPEND ${REL_SRC_DIR}/)
list(TRANSFORM INC PREPEND ${REL_SRC_DIR}/)

# build target
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SRC} ${INC})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
                           ${REL_SRC_DIR}
)
if(CMAKE_CXX_COMPILER_ID EQUAL "MSVC")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -g)
endif()

### Tests ###
option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()
    set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)
    add_subdirectory(${TESTS_DIR})
endif()


### Installer ###
# Maybe one day ?