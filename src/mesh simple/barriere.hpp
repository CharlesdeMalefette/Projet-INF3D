#pragma once

#include "cgp/cgp.hpp"

cgp::mesh create_barriere();
std::vector<cgp::vec3> position_barriere_right(int N,float terrain_length_x,float terrain_length_y);
std::vector<cgp::vec3> position_barriere_left(int N,float terrain_length_x,float terrain_length_y);

