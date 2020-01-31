### Configuration ###
cmake_minimum_required(VERSION 3.10.0)

project(OsuBot VERSION 0.1.0)

# C++ Compilation specs
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

### Main Executable ###
add_executable(${PROJECT_NAME})
set(SRC_DIR "source/")

# generate Config file
find_file(__CONFIG_FILE ${PROJECT_NAME}Config.h.in ${CMAKE_SOURCE_DIR}/${SRC_DIR})
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


### Tests ###
enable_testing()

#add_executable(ParserTest ParserTest.cpp Parser/*.cpp)
add_test(NAME Parse COMMAND ${PROJECT_NAME} TestFiles/DefaultTestFile)
set_tests_properties(Parse PROPERTIES
    REQUIRED_FILES ${CMAKE_SOURCE_DIR}/TestFiles/DefaultTestFile
)
#set_tests_properties(Parse
#    PROPERTIES __IS_SAME testFiles/DefaultTestFile# may need a program to compare the values with .osu file
#)

add_test(NAME Usage COMMAND ${PROJECT_NAME})
set_tests_properties(Usage PROPERTIES
    PASS_REGULAR_EXPRESSION "Version [0-9]+\\.[0-9]+"
)

### Installer ###
# Maybe one day ?