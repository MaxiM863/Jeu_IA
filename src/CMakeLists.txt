add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

#add_test(NAME Utility COMMAND ${PROJECT_NAME} tests)

include(FetchContent)

  FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG        "preview-3.1.6"
  )
FetchContent_MakeAvailable(SDL)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/SDL-main/SDL/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../tests)