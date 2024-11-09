include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(TARGET_NAME cpp-bencode-tests)

set(Sources
  "src/object_tests.cpp")

add_executable(${TARGET_NAME} ${Sources})

target_link_libraries(
  ${TARGET_NAME} 
    PRIVATE
      ${PROJECT_NAME}
      gtest_main)

enable_testing()
gtest_discover_tests(${TARGET_NAME})