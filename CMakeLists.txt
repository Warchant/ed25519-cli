cmake_minimum_required(VERSION 3.0)
project(ed25519-cli C CXX)

find_package(ed25519 REQUIRED)

add_executable(ed25519-cli
  main.cpp
  )
target_link_libraries(ed25519-cli
  ed25519
  )
target_include_directories(ed25519-cli PRIVATE
  ./clipp/include
  )