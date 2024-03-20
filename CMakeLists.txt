cmake_minimum_required(VERSION 3.28)
project(Discrete_HW2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Discrete_HW2 main.cpp)


include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
