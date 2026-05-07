cmake_minimum_required(VERSION 3.16)
project(StudentuProgramaV2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(studentu_programa
    main.cpp
    Zmogus.cpp
    Studentas.cpp
    Failai.cpp
    Rikiavimas.cpp
    Ivedimas.cpp
    Tyrimai.cpp
    Testai.cpp
)

# Unit testai su doctest
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(studentu_testai
    tests/StudentasTestai.cpp
    Zmogus.cpp
    Studentas.cpp
)
target_include_directories(studentu_testai PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(studentu_testai PRIVATE doctest::doctest)

enable_testing()
add_test(NAME StudentasTestai COMMAND studentu_testai)

# Doxygen dokumentacija
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    add_custom_target(dokumentacija
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generuojama Doxygen dokumentacija..."
        VERBATIM
    )
endif()