add_executable(NQueensApp
    nqueens.cpp)

set_target_properties(NQueensApp PROPERTIES OUTPUT_NAME "nqueens")

target_compile_features(NQueensApp PRIVATE cxx_std_17)

target_link_libraries(NQueensApp NQueensLib cxxopts)
