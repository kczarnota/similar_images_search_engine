cmake_minimum_required(VERSION 3.5)
project(BagOfWords CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


file(GLOB SRC_LIST
        "src/*.hpp"
        "src/*.cpp"
        "src/*/*.hpp"
        "src/*/*.cpp"
        )

find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS system filesystem serialization )
find_package( Qt5Widgets REQUIRED )

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} )
