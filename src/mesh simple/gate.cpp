#include "mesh simple/gate.hpp"
#include "mesh simple/tree.hpp"
#include "mesh simple/terrain.hpp"

using namespace cgp;

mesh create_gate(int N,int i)
{
    mesh gate = create_cylinder_mesh(0.05f,10*sin(Pi*i/N));

    return gate;
}

std::vector<vec3> position_gate_right(int N,float terrain_length_x, float terrain_length_y)
{
    std::vector<cgp::vec3> position;
    for(int i=0;i<N;i++){
        //position.push_back({i-terrain_length_x/2,terrain_length_y/2,evaluate_terrain_height(i-terrain_length_x/2,terrain_length_y/2)});
        position.push_back({i-terrain_length_x/2,evaluate_terrain_height(i-terrain_length_x/2,terrain_length_y/2),terrain_length_y/2,});
    }
    return position;
}
std::vector<vec3> position_gate_left(int N,float terrain_length_x, float terrain_length_y)
{
    std::vector<cgp::vec3> position;
    for(int i=0;i<N;i++){
        //position.push_back({i-terrain_length_x/2,-terrain_length_y/2,evaluate_terrain_height(i-terrain_length_x/2,-terrain_length_y/2)});
        position.push_back({i-terrain_length_x/2,evaluate_terrain_height(i-terrain_length_x/2,-terrain_length_y/2),-terrain_length_y/2,});
    }
    return position;
}

std::vector<vec3> position_gate_right_light(int N,float terrain_length_x, float terrain_length_y)
{
    std::vector<cgp::vec3> position;
    for(int i=0;i<N;i++){
        //position.push_back({i-terrain_length_x/2,terrain_length_y/2,evaluate_terrain_height(i-terrain_length_x/2,terrain_length_y/2)});
        position.push_back({i-terrain_length_x/2,evaluate_terrain_height_light(i-terrain_length_x/2,terrain_length_y/2),terrain_length_y/2,});
    }
    return position;
}
std::vector<vec3> position_gate_left_light(int N,float terrain_length_x, float terrain_length_y)
{
    std::vector<cgp::vec3> position;
    for(int i=0;i<N;i++){
        //position.push_back({i-terrain_length_x/2,-terrain_length_y/2,evaluate_terrain_height(i-terrain_length_x/2,-terrain_length_y/2)});
        position.push_back({i-terrain_length_x/2,evaluate_terrain_height_light(i-terrain_length_x/2,-terrain_length_y/2),-terrain_length_y/2,});
    }
    return position;
}
