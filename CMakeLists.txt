cmake_minimum_required(VERSION 3.0)
project(pong)

set(CMAKE_CXX_STANDARD 11)


set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
add_executable(pong main.cpp menu.cpp sterowanie.cpp gracz.cpp rakieta.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS REQUIRED graphics window audio system network)
target_link_libraries(pong sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
        sfml-network
        )

