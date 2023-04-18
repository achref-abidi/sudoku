cmake_minimum_required(VERSION 3.16)

project(Sudoku)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

set(SUDOKU_SRC
        ./src/launcher.cpp
        ./src/cell.cpp
        ./src/main.cpp
        ./src/game.cpp
        )

set(SUDOKU_INC
        ./include/cell.h
        ./include/launcher.h
        ./include/game.h
        )

set(IMG_RESOURCES
        ./img/Button01.png
        ./img/Cell01.png
        ./img/Cell02.png
        ./img/Cell03.png
        ./img/Cell04.png
        ./img/panel.jpg
        )

find_package(Qt6 REQUIRED

        PATHS "/home/achrefabidi/opt/Qt/6.5.0/gcc_64/lib/cmake/Qt6/"

        COMPONENTS Core Gui Widgets
        NO_DEFAULT_PATH)


message(STATUS ${Qt6Widgets_DIR})

qt_standard_project_setup()

add_executable(${PROJECT_NAME} ${SUDOKU_SRC} ${SUDOKU_INC})
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

qt_add_resources(${PROJECT_NAME}
        imageresources
        PREFIX ""
        FILES ${IMG_RESOURCES}
        )
