add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp MinMaxAlgo.cpp)

include(FetchContent)

  FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG        "preview-3.1.6"
  )
FetchContent_MakeAvailable(SDL)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.87.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Boost)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 Boost::filesystem Boost::system Boost::thread Boost::asio)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/SDL-main/SDL/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../tests)