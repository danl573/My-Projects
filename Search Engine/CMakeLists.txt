cmake_minimum_required(VERSION 3.16)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 17)

add_executable(21f_final_proj_template main.cpp catch_setup.cpp DSAvlNode.h DSAvlTree.h Query.cpp wordInfo.h
        DSAvlTest.cpp DSHashTable.h DSHashTest.cpp DSAvl_Map.h Parser.cpp DSString.cpp Documento.cpp Morpheme.cpp)
