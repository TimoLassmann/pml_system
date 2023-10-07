find_library(raylib NAMES raylib)

if(NOT raylib)
  message(FATAL_ERROR "library.a not found!")
endif()




include_directories("${CMAKE_SOURCE_DIR}/raylib-4.5.0_macos/include")
add_executable(alife
  main.c
  grid.c
  )

target_link_libraries(alife 
  PRIVATE
  ${raylib}
  tld-dev
  )
