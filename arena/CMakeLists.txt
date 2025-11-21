project(arena)

add_library(${PROJECT_NAME} 
  STATIC
  # === ARENA ===
  ${CMAKE_CURRENT_SOURCE_DIR}/arena.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena_string.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena_string.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
)

install(TARGETS ${PROJECT_NAME} DESTINATION arena)
install(
  FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/arena.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/arena_string.hpp

  DESTINATION include
)
