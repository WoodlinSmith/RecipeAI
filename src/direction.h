/***************************************************************************//**
 * @file directions.h
 * This file contains an enum of possible move directions, to be used for the
 * move() and attack() functions of Actor derivatives.
 ******************************************************************************/
#ifndef __DIRECTION_H
#define __DIRECTION_H

#include<iostream>

enum direction {UP = 0, UPRIGHT = 1, RIGHT = 2, DOWNRIGHT = 3, DOWN = 4, DOWNLEFT = 5, LEFT = 6, UPLEFT = 7, STAY};

std::ostream &operator<< ( std::ostream &, direction const & );

#endif
