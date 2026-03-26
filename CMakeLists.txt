cmake_minimum_required(VERSION 3.16)
project(StudentuProgramaV1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(studentu_programa
    main.cpp
    Studentas.cpp
    Failai.cpp
    Rikiavimas.cpp
    Ivedimas.cpp
    Tyrimai.cpp
)