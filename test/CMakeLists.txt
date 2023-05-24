include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  arx_ut
  arx_ut.cpp
  ../src/ARX.cpp
  ../src/SISO.cpp
  ../src/struktury.cpp
)
target_link_libraries(
    arx_ut
    GTest::gtest_main
)
target_include_directories(arx_ut PRIVATE ../include)

# Set the output name for the executable
set_target_properties(arx_ut PROPERTIES OUTPUT_NAME "arx_ut")

include(GoogleTest)
gtest_discover_tests(arx_ut)