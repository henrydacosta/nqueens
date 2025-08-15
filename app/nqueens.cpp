/*
MIT License

Copyright (c) 2025 Henry da Costa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file
 * Implements the nqueens app.
 */

#include "NQueensBoard.h"

#include "cxxopts.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <string>

using namespace std;
using namespace hdc::nqueens;

/**
 * Prints an N-Queens board to a given output stream.
 *
 * @param[in] board
 * The N-Queens board.
 *
 * @param[in] occ
 * The string to output for occupied squares.
 *
 * @param[in] unocc
 * The string to output for unoccupied squares.
 *
 * @param[in] ostr
 * The output stream.
 */
void printBoard(const NQueensBoard &board, const string &occ,
                const string &unocc, ostream &ostr) {
    size_t n = board.getSize();
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            if (board.isSquareOccupied(r, c)) {
                ostr << occ;
            } else {
                ostr << unocc;
            }
        }
        ostr << endl;
    }
}

/**
 * Prints N-Queens solutions to a given output stream.
 *
 * @param[in] solns
 * The N-Queens solutions.
 *
 * @param[in] occ
 * The string to output for occupied squares.
 *
 * @param[in] unocc
 * The string to output for unoccupied squares.
 *
 * @param[in] ostr
 * The output stream.
 */
void printSolutions(const vector<NQueensBoard> &solns, const string &occ,
                    const string &unocc, ostream &ostr) {
    for (size_t i = 0; i < solns.size(); ++i) {
        cout << "Solution " << i + 1 << ':' << endl;
        printBoard(solns[i], occ, unocc, ostr);
    }
}

int main(int argc, char **argv) {
    size_t n;
    size_t solve = numeric_limits<size_t>::max();
    size_t print = numeric_limits<size_t>::max();
    bool live = false;
    bool random = false;
    string occ;
    string unocc;

    cxxopts::Options options("nqueens", "N-Queens solver");

    // clang-format off
    options.add_options()
        ("n,size",
         "The N in N-Queens",
         cxxopts::value<size_t>(n)->default_value("4"))
        ("s,solve",
         "Maximum number of solutions to get instead of all possible solutions",
         cxxopts::value<size_t>(solve))
        ("p,print",
         "Maximum number of solutions to print instead of all gotten solutions",
         cxxopts::value<size_t>(print))
        ("l,live",
         "Print solutions as they are found, without storing them",
         cxxopts::value<bool>(live))
        ("r,random",
         "Print solutions in random order, ignored if --live is present",
         cxxopts::value<bool>(random))
        ("o,occupied",
         "String for printing occupied squares",
         cxxopts::value<string>(occ)->default_value(" Q"))
        ("u,unoccupied",
         "String for printing unoccupied squares",
         cxxopts::value<string>(unocc)->default_value(" ."))
        ("h,help", "Print help and exit");
    // clang-format on

    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            cout << options.help() << endl;
            return EXIT_SUCCESS;
        }

        NQueensBoard board(n);
        size_t count = 0;
        std::chrono::time_point<std::chrono::high_resolution_clock> t1;
        std::chrono::time_point<std::chrono::high_resolution_clock> t2;
        if (live) {
            t1 = chrono::high_resolution_clock::now();
            board.solve(
                [&count, &solve, &print, &occ, &unocc](NQueensBoard &board) {
                    if (count < print) {
                        cout << "Solution " << count + 1 << ':' << endl;
                        printBoard(board, occ, unocc, cout);
                    }
                    return ++count >= solve;
                });
            t2 = chrono::high_resolution_clock::now();
        } else {
            vector<NQueensBoard> solns;
            t1 = chrono::high_resolution_clock::now();
            board.solve([&solns, &solve](NQueensBoard &board) {
                solns.emplace_back(board);
                return solns.size() >= solve;
            });
            t2 = chrono::high_resolution_clock::now();
            count = solns.size();

            print = min(print, solns.size());
            if (print > 0) {
                if (random) {
                    std::random_device rd;
                    std::mt19937 g(rd());
                    std::shuffle(begin(solns), end(solns), g);
                }
                solns.erase(begin(solns) + print, end(solns));
                printSolutions(solns, occ, unocc, cout);
            }
        }

        cout << count << " solutions" << endl;

        auto dursec = chrono::duration_cast<chrono::duration<float>>(t2 - t1);
        cout << dursec.count() << " seconds" << endl;

        return EXIT_SUCCESS;
    } catch (const cxxopts::exceptions::exception &e) {
        cout << "Error parsing options: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}