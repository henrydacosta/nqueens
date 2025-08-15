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
 * Declares class NQueensBoard.
 */

#ifndef _NQUEENSBOARD_H
#define _NQUEENSBOARD_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

namespace hdc {
namespace nqueens {

/**
 * An N-Queens board.
 */
class NQueensBoard {
public:
    /**
     * N-Queens board constructor.
     *
     * @param[in] n
     * Board size (the N in N-Queens).
     */
    NQueensBoard(std::size_t n)
        : _oc(n), _tc(n),
          _td{std::vector<bool>(n * 2 - 1), std::vector<bool>(n * 2 - 1)},
          _n(n) {}

    /**
     * Returns the board size (the N in N-Queens).
     */
    std::size_t getSize() const { return _n; }

    /**
     * Returns whether a given square is occupied.
     *
     * @param[in] r
     * The row index of the square.
     *
     * @param[in] c
     * The column index of the square.
     */
    bool isSquareOccupied(std::size_t r, std::size_t c) const {
        return _oc[r] == c;
    }

    /**
     * Solves the N-Queens board and calls a function for each solution found.
     *
     * Stops solving when the called function returns true;
     *
     * @param[in] fn
     * The function to call for each solution found.
     */
    void solve(std::function<bool(NQueensBoard &)> fn) const { _solve(0, fn); }

private:
    std::vector<std::size_t> _oc; //!< Each row's occupied column.
    std::vector<bool> _tc;        //!< Whether a given column has a queen.
    std::vector<bool> _td[2];     //!< Whether a given diagonal has a queen.
    std::size_t _n;               //!< The board size (the N in N-Queens).

    /**
     * Returns the index into <tt>_td[type]</tt> for a given square.
     *
     * @param[in] r
     * The row index of the square that the diagonal includes.
     *
     * @param[in] c
     * The column index of the square that the diagonal includes.
     *
     * @param[in] type
     * The diagonal type, 0 or 1.
     */
    std::size_t _getDiagonalIndex(std::size_t r, std::size_t c,
                                  std::size_t type) const {
        assert(type < 2);
        switch (type) {
            case 0:
                return r + c;
            case 1:
                return _n - 1 + r - c;
            default:
                // Should never happen.
                return 0;
        }
    }

    /**
     * Returns whether a given column contains a queen.
     *
     * @param[in] c
     * The column index.
     */
    bool _isColumnThreatened(std::size_t c) const { return _tc[c]; }

    /**
     * Returns whether a diagonal through a given square contains a queen.
     *
     * @param[in] r
     * The row index of the square that the diagonal includes.
     *
     * @param[in] c
     * The column index of the square that the diagonal includes.
     *
     * @param[in] type
     * The diagonal type, 0 or 1.
     */
    bool _isDiagonalThreatened(std::size_t r, std::size_t c,
                               std::size_t type) const {
        assert(type < 2);
        if (type < 2) {
            return _td[type][_getDiagonalIndex(r, c, type)];
        }
        // Should never happen.
        return false;
    }

    /**
     * Returns whether a given square can be occupied.
     *
     * @param[in] r
     * The row index of the square.
     *
     * @param[in] c
     * The column index of the square.
     */
    bool _canOccupySquare(std::size_t r, std::size_t c) const {
        return !_isColumnThreatened(c) && !_isDiagonalThreatened(r, c, 0) &&
               !_isDiagonalThreatened(r, c, 1);
    }

    /**
     * Sets that a given square is occupied.
     *
     * @param[in] r
     * The row index of the square.
     *
     * @param[in] c
     * The column index of the square.
     */
    void _setSquareOccupied(std::size_t r, std::size_t c) { _oc[r] = c; }

    /**
     * Sets that a given column is occupied.
     *
     * @param[in] c
     * The column index.
     */
    void _setColumnThreatened(std::size_t c) { _tc[c] = true; }

    /**
     * Sets that a diagonal through a given square is occupied.
     *
     * @param[in] r
     * The row index of the square that the diagonal includes.
     *
     * @param[in] c
     * The column index of the square that the diagonal includes.
     *
     * @param[in] type
     * The diagonal type, 0 or 1.
     */
    void _setDiagonalThreatened(std::size_t r, std::size_t c,
                                std::size_t type) {
        assert(type < 2);
        if (type < 2) {
            _td[type][_getDiagonalIndex(r, c, type)] = true;
        }
    }

    /**
     * Occupies a square and sets all the necessary flags.
     *
     * @param[in] r
     * The row index of the square.
     *
     * @param[in] c
     * The column index of the square.
     */
    void _occupySquare(std::size_t r, std::size_t c);

    /**
     * Solves an N-Queens board starting at a given row.
     *
     * Stops solving when the called function returns true.
     *
     * @param[in] r
     * The starting row to solve.
     *
     * @param[in] fn
     * The function to call when a solution is found.
     */
    bool _solve(std::size_t r, std::function<bool(NQueensBoard &)> fn) const;
}; // class NQueensBoard

} // namespace nqueens
} // namespace hdc

#endif // _NQUEENSBOARD_H