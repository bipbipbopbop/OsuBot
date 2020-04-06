### TestFinder ###
add_executable(TestFinder)

## add Logger Library
target_link_libraries(TestFinder Logger)
target_link_libraries(TestFinder jhack)

## construct source files list
set(TESTFINDER_SRC
    OsuFinder.cpp
    OsuFinder.hpp
)
list(TRANSFORM TESTFINDER_SRC PREPEND ${SRC_DIR}/Finder/)
list(APPEND TESTFINDER_SRC
     ${TESTS_SRC_DIR}/${TESTS_CONFIG_FILE}
     ${TESTS_SRC_DIR}/TestFinder/main.cpp
)

## add Source files
target_sources(TestFinder PRIVATE ${TESTFINDER_SRC})
target_include_directories(TestFinder PRIVATE
                           ${SRC_DIR}
                           ${TESTS_SRC_DIR}
)
unset(TESTFINDER_SRC)

add_test(NAME Finder COMMAND TestFinder)
set_tests_properties(Finder PROPERTIES
    WORKING_DIRECTORY ${OsuBot_BINARY_DIR}
    PASS_REGULAR_EXPRESSION "Success!"
)
