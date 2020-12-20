# cmake_minimum_required(VERSION <specify CMake version here>)
project(Ivanin-metaprog-3)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Ivanin-metaprog-3
        main.cpp
        lib/EmptyEdge.h
        lib/graphBymatrix/MatrixGraph.h
        lib/TypeList.h
        lib/graphBymatrix/MatrixGraphComponents.h)
