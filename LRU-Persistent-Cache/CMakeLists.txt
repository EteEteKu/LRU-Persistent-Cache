# CMakeList.txt: проект CMake для LRU-Persistent-Cache
add_executable (LRU-Persistent-Cache "src/main.cpp" "include/KVstore.h" "src/KVstore.cpp")

target_include_directories(LRU-Persistent-Cache PRIVATE include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LRU-Persistent-Cache PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
enable_testing()
add_subdirectory(tests)