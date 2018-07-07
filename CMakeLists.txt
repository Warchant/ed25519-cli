cmake_minimum_required(VERSION 3.0)
project(ed25519-cli LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

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


include(GNUInstallDirs)
install(TARGETS ed25519-cli EXPORT ed25519Config
  RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
  )
export(
  TARGETS ed25519-cli
  FILE ed25519Config.cmake
)