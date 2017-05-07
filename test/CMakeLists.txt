set(TEST_NAME Test)

add_executable(${TEST_NAME} test.cpp)

include_directories(${FOLDER_LIB_INCLUDE})
target_link_libraries(${TEST_NAME} ${PROJECT_NAME})

