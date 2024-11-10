
set(TARGET_NAME decoder-fuzzing)

set(Sources
  "src/decoder_fuzzing.cpp"
)

add_executable(${TARGET_NAME} ${Sources})

target_compile_options(${TARGET_NAME} PRIVATE -g -O0 -fsanitize=fuzzer,address)
target_link_options(${TARGET_NAME} PRIVATE -fsanitize=fuzzer,address)

target_link_libraries(
  ${TARGET_NAME} 
    PRIVATE
      ${PROJECT_NAME}
)