cmake_minimum_required(VERSION 3.5)
project(BagOfWords CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SRC_LIST
        "src/*.hpp"
        "src/*.cpp"
        )

file(GLOB SRC_LIST_TEST
        "test/*.hpp"
        "test/*.cpp"
        )
find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS system filesystem serialization )

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )

set(TEST_SOURCE_FILES ${SRC_LIST}) #kopiuje pliki do testow

list(REMOVE_ITEM TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp) #usuwa niepotrzebnego maina
add_executable(Test ${SRC_LIST_TEST} ${TEST_SOURCE_FILES})
target_link_libraries( Test ${OpenCV_LIBS} )
target_link_libraries( Test ${Boost_LIBRARIES} )

enable_testing()
add_test(TestProject Test)