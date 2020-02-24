### TestParser ###
add_executable(TestParser)

## add Logger Library
target_link_libraries(TestParser Logger)

## construct source files list
set(TESTPARSER_SRC
    OsuParser.cpp
    OsuParser.hpp
    OsuKey.cpp
    OsuKey.hpp
)
list(TRANSFORM TESTPARSER_SRC PREPEND ${SRC_DIR}/Parser/)
list(APPEND TESTPARSER_SRC
     ${TESTS_SRC_DIR}/${TESTS_CONFIG_FILE}
     ${TESTS_SRC_DIR}/TestParser/main.cpp
)

## add Source files
target_sources(TestParser PRIVATE ${TESTPARSER_SRC})
target_include_directories(TestParser PRIVATE
                           ${SRC_DIR}
                           ${TESTS_SRC_DIR}
)
unset(TESTPARSER_SRC)

add_test(NAME Parser COMMAND TestParser)
set_tests_properties(Parser PROPERTIES
    REQUIRED_FILES ${TESTS_DATA_DIR}/Default
    PASS_REGULAR_EXPRESSION "Success!"
)
