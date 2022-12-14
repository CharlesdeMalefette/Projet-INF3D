#pragma once

#include "cgp/cgp.hpp"


float evaluate_terrain_height(float x, float y);
float evaluate_terrain_height_light(float x,float terrain_length_x);

/** Compute a terrain mesh
    The (x,y) coordinates of the terrain are set in [-length/2, length/2].
    The z coordinates of the vertices are computed using evaluate_terrain_height(x,y).
    The vertices are sampled along a regular grid structure in (x,y) directions.
    The total number of vertices is N*N (N along each direction x/y)     */
cgp::mesh create_terrain_mesh(int N, float length_x, float length_y);
cgp::mesh create_terrain_mesh_light(int N, float length_x, float length_y);


std::vector<cgp::vec3> generate_positions_on_terrain(int N, float terrain_length_x, float terrain_length_y);
std::vector<cgp::vec3> position_gate_right(int N,float terrain_length_x, float terrain_length_y);
std::vector<cgp::vec3> position_gate_left(int N,float terrain_length_x, float terrain_length_y);
std::vector<cgp::vec3> position_gate_right_light(int N,float terrain_length_x, float terrain_length_y);
std::vector<cgp::vec3> position_gate_left_light(int N,float terrain_length_x, float terrain_length_y);

cgp::mesh create_gate(int N, int i);
