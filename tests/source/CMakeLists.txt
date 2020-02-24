### Program behavior ###

# Usage
add_test(NAME Usage COMMAND ${CMAKE_PROJECT_NAME})
set_tests_properties(Usage PROPERTIES
    PASS_REGULAR_EXPRESSION "Version [0-9]+\\.[0-9]+"
)