find_package(raylib 3.0 REQUIRED)

add_executable(pml_system
  main.c
  grid.c
  )

target_link_libraries(pml_system
  PRIVATE
  raylib
  tld-dev
  )

add_executable(test_grid
  test_grid.c
  grid.c
  )
target_link_libraries(test_grid
  PRIVATE
  raylib
  tld-dev
  )
