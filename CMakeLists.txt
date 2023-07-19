cmake_minimum_required(VERSION 3.12)
project(cli_snake4c
    VERSION 0.0.1
    DESCRIPTION "snake_game"
    LANGUAGES C)

add_library(core_lib STATIC src/core/snake_game_core.c src/core/snake_game_core_sycle.c)
target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(core_lib PROPERTIES VERSION ${PROJECT_VERSION})


add_library(view_lib STATIC src/view/snake_view.c src/view/snake_controle.c)
target_include_directories(view_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(view_lib PROPERTIES VERSION ${PROJECT_VERSION})

add_library(utils_lib STATIC src/utils/argparser.c)
target_include_directories(utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(utils_lib PROPERTIES VERSION ${PROJECT_VERSION})


add_executable(snake_game src/main.c)
target_link_libraries(snake_game core_lib view_lib utils_lib)


# add_executable(snake_game src/main.c  src/view/snake_view.c src/view/snake_controle.c src/core/snake_game_core.c src/core/snake_game_core_sycle.c)
# target_include_directories(snake_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
