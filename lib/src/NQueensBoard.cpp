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
 * Implements class NQueensBoard.
 */

#include "NQueensBoard.h"

using namespace std;
using namespace hdc::nqueens;

bool NQueensBoard::_solve(std::size_t r,
                          std::function<bool(NQueensBoard &)> fn) const {
    for (std::size_t c = 0; c < _n; ++c) {
        if (_canOccupySquare(r, c)) {
            NQueensBoard board(*this);
            board._occupySquare(r, c);
            if (r + 1 < _n) {
                if (board._solve(r + 1, fn)) {
                    return true;
                }
            } else {
                if (fn(board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void NQueensBoard::_occupySquare(std::size_t r, std::size_t c) {
    _setSquareOccupied(r, c);
    _setColumnThreatened(c);
    _setDiagonalThreatened(r, c, 0);
    _setDiagonalThreatened(r, c, 1);
}