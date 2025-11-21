project(test)

add_executable(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/arena_test.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena_string_test.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena_string_test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE arena)
