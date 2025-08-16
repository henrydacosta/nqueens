add_library(NQueensLib
    include/NQueensBoard.h
    src/NQueensBoard.cpp)

set_target_properties(NQueensLib PROPERTIES OUTPUT_NAME "nqueens")

target_include_directories(NQueensLib PUBLIC include)
