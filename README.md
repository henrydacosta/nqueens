# N-Queens Solver

## What is This?

This project contains a command line (console) application that solves the N-Queens problem.

## How to Build It

To build this project, you will need:

- [CMake](https://cmake.org/), version 3.11 or higher.

- A C++17 or higher compiler that CMake can use.

- Optionally, [Doxygen](https://www.doxygen.nl/index.html), if you want to build
the docs. The CMake configuration files automatically build the docs if you have Doxygen installed.

- An internet connection.

This project uses the cxxopts library. The CMake configuration files automatically get cxxopts from GitHub.

If you have all the prerequisites and want to build this project, you can issue the following shell commands from the directory
where you cloned this project:

```shell
cmake -B build .
cmake --build build
```

The default configuration on Windows is Debug. To build the Release version, replace the `cmake --build build` line with `cmake --build build --config Release`.

If you want to generate the internal version of the docs, with implementation
details, replace the `cmake -B build .` line with `cmake -DDOXYGEN_INTERNAL_DOCS=YES -B build .`.

The notable outputs from the build are:

| Platform    | File                                   | Description                                                                         |
| ----------- | -------------------------------------- | ----------------------------------------------------------------------------------- |
| Non-Windows | build/app/nqueens                      | The N-Queens solver application.                                                    |
| Windows     | build/app/<i>Configutation</i>/nqueens | The N-Queens solver application, where *Configuration* is **Debug** or **Release**. |
| All         | build/docs/html/index.html             | The Doxygen-generated help page.                                                    |

The author has successfully built this project in the following environments:

| Compiler     | CMake  | OS              |
| ------------ | ------ | --------------- |
| MSVC 19.44   | 4.1.0  | Windows 11      |
| Clang 19.1.5 | 4.1.0  | Windows 11      |
| Clang 10.0.0 | 4.0.3  | Ubuntu 20.04    |
| GNU 13.3.0   | 3.28.3 | Linux Mint 22.1 |

## How It Works

This project uses recursive backtracking, which is excellently described on [this page](https://www.geeksforgeeks.org/dsa/n-queen-problem-backtracking-3/).

## Results

The N-Queens solver application was benchmarked on the following platforms:

| Platform | CPU                                                                 | OS         |
| -------: | ------------------------------------------------------------------- | ---------- |
|        1 | Intel(R) Core(TM) i7-8700 @ 3.20GHz, 6 Cores, 12 Logical Processors | Windows 11 |
|        2 | TBD | TBD |
|        3 | TBD | TBD |

The following table shows the number of seconds that it took to find all the solutions for each value of *N* from 1 through 15 on each platform. The command used was `nqueens -l -p 0 -n <N>` to avoid storing or printing the solutions. The results were averaged over three runs.

|   N | Solutions | Platform 1 |
| --: | --------: | ---------: |
|   1 |         1 |   6.33E-07 |
|   2 |         0 |   9.33E-07 |
|   3 |         0 |   1.77E-06 |
|   4 |         2 |   4.50E-06 |
|   5 |        10 |   1.65E-05 |
|   6 |         4 |   3.81E-05 |
|   7 |        40 |   1,39E-04 |
|   8 |        92 |   5.50E-04 |
|   9 |       352 |   2.45E-03 |
|  10 |       724 |   1.20E-02 |
|  11 |      2680 |   5.84E-02 |
|  12 |     14200 |   2.88E-01 |
|  13 |     73712 |   1.49E+00 |
|  14 |    365596 |   8.09E+00 |
|  15 |   2279184 |   4.81E+01 |
