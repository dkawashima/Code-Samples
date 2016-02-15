/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "DepthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver. All coordinate pairs are unvisited.
 */
void DepthFirstSolver::init()
{
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            visited[i][j] = false;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
	delete stack;
    deinit();
}


/**
 * @brief Deinitializes the solver. Does not need any additional deletes.
 */
void DepthFirstSolver::deinit()
{

}

/**
 * @brief Solves the maze given by `maze` using DFS.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    Coordinate curPos = Coordinate(MAZE_START_X, MAZE_START_Y);
    bool movesMade;
    stack->push(curPos);
    while (stack->is_empty() != 1){
        visited[curPos.x][curPos.y] = true;
        if (curPos.x == MAZE_END_X && curPos.y == MAZE_END_Y){
            break;
        } else {
            movesMade = add_possible_moves(curPos, maze);
            if (movesMade == false){
                stack->pop();
            }
        }
        curPos = stack->peek();

    }

}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
std::vector<Coordinate> DepthFirstSolver::get_path()
{
    std::vector<Coordinate> list = stack->get_path();

    return list;
}

/**
 * @brief Checks if new moves are possible from a coordinate 
 * and adds them to the stack
 *
 * @return true if moves are possible, false if not.
 */
bool DepthFirstSolver::add_possible_moves(Coordinate c, MazeGrid* maze)
{
    int res = maze->get_possible_moves(c.x, c.y);
    bool movesMade = false;
    if (res & E){
        if (visited[c.x + 1][c.y] == false){
            stack->push(Coordinate(c.x + 1, c.y));
            movesMade = true;
        }
    }
    if (res & W && movesMade == false){
        if (visited[c.x - 1][c.y] == false){
            stack->push(Coordinate(c.x - 1, c.y));
            movesMade = true;
        }
    }
    if (res & N && movesMade == false){
        if (visited[c.x][c.y - 1] == false){
            stack->push(Coordinate(c.x, c.y - 1));
            movesMade = true;
        }
    }
    if (res & S && movesMade == false){
        if (visited[c.x][c.y + 1] == false){
            stack->push(Coordinate(c.x, c.y + 1));
            movesMade = true;
        }
    }
    return movesMade;
}

