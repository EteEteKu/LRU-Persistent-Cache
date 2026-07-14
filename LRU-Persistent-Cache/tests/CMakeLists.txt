

include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(Catch2)
add_executable(unit_tests "test_kvstore.cpp" "../src/KVstore.cpp" "test_lrucache.cpp" "../src/LRUcache.cpp" "test_snapshot.cpp")
target_include_directories(unit_tests PRIVATE ../include)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
set_property(TARGET unit_tests PROPERTY CXX_STANDARD 20)