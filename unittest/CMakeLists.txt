set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(SOURCES main.cpp
    formats/hex_data_test.cpp
    formats/intel_hex_test.cpp
    )

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC  gtest)
