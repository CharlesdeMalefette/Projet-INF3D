#pragma once

#include "cgp/cgp.hpp"

std::vector<cgp::vec3> position_gate_right(int N,float terrain_length_x,float terrain_length_y);
std::vector<cgp::vec3> position_gate_left(int N,float terrain_length_x,float terrain_length_y);
cgp::mesh create_gate(int N, int i);
