set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(SOURCES main.cpp)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC  gtest)
