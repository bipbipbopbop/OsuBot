### TestParser ###

## construct source files list
set(TESTPARSER_SRC
    OsuParser.cpp
    OsuParser.hpp
    OsuKey.cpp
    OsuKey.hpp
)
list(TRANSFORM TESTPARSER_SRC PREPEND ${CMAKE_SOURCE_DIR}/${SRC_DIR}Parser/)

add_executable(TestParser
    ${TEST_SRC_DIR}/TestParser/main.cpp
    ${TESTPARSER_SRC}
)
target_include_directories(TestParser PRIVATE
                           ${CMAKE_SOURCE_DIR}/${SRC_DIR}
)
unset(TESTPARSER_SRC)

add_test(NAME Parser COMMAND TestParser)
set_tests_properties(Parser PROPERTIES
#    REQUIRED_FILES ${CMAKE_SOURCE_DIR}/tests/data/Default
#    REQUIRED_FILES "${CMAKE_SOURCE_DIR}/tests/data/Team Nekokan - Can't Defeat Airman (Blue Dragon) [Holy Shit! It's Airman!!].osu"
    PASS_REGULAR_EXPRESSION "Success!"
)
