### Tests ###

# Variables Definition
set(TESTS_SRC_DIR ${TESTS_DIR}/source)
set(TESTS_DATA_DIR ${TESTS_DIR}/data)

# Config file
find_file(__CONFIG_FILE
    ${CMAKE_PROJECT_NAME}TestsConfig.h.in
    ${CMAKE_SOURCE_DIR}/cmake
)
if(EXISTS ${__CONFIG_FILE})
    string(REGEX REPLACE ".*/([^/]*)\\.in" "\\1" TESTS_CONFIG_FILE ${__CONFIG_FILE})
    configure_file(${__CONFIG_FILE} ${TESTS_SRC_DIR}/${TESTS_CONFIG_FILE})
else()
    set(TESTS_CONFIG_FILE "")
endif()
unset(__CONFIG_FILE CACHE)


# Unit Tests #
# Program behavior
add_subdirectory(${TESTS_SRC_DIR})

# TestParser
add_subdirectory(${TESTS_SRC_DIR}/TestParser)