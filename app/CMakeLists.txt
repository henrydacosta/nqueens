add_executable(nqueensapp
    nqueens.cpp)

set_target_properties(nqueensapp PROPERTIES OUTPUT_NAME "nqueens")

target_compile_features(nqueensapp PRIVATE cxx_std_17)

target_link_libraries(nqueensapp nqueenslib cxxopts)
