/* 
 * File:   Globals.hpp
 * Author: Rajesh
 *
 * Created on March 9, 2016, 11:39 PM
 */

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 800
#define GRIDSIZE 10

#define TIMESTEP 10
#define DRAW_ITER 1

#define N 1000
#define RADIUS 5
#define VELOCITY 10

#define DEBUG true

const int nrows = ((int) ((float) IMAGE_WIDTH / GRIDSIZE));
const int ncols = ((int) ((float) IMAGE_HEIGHT / GRIDSIZE));

#endif /* GLOBALS_HPP */

