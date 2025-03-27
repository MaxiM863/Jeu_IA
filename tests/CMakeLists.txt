target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

enable_testing()

add_test(NAME Utility COMMAND ${PROJECT_NAME} tests)