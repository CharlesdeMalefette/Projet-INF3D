#include "barriere.hpp"
#include "mesh simple/terrain.hpp"

using namespace cgp;

mesh create_barriere()
{
    mesh barriere = mesh_primitive_parallepipède({0,0,0},2.0f,0.3f,0.2f);
    barriere.push_back(mesh_primitive_parallepipède({0,2.0f,0},2.0f,0.3f,0.2f));
    barriere.push_back(mesh_primitive_parallepipède({0.9f,1.0f,0},0.2f,2.0f,0.2f));
    barriere.push_back(mesh_primitive_parallepipède({-0.9f,1.0f,0},0.2f,2.0f,0.2f));
    barriere.push_back(mesh_primitive_cylinder(0.1f,{-1,0.1f,0},{1,1.9f,0}));


    return barriere;
}

std::vector<vec3> position_barriere_right(int N, float terrain_length_x,float terrain_length_y)
{
    std::vector<cgp::vec3> position;
    for(int i=0;i<N;i++){

        position.push_back({-terrain_length_x/2+2*i,0.5f+evaluate_terrain_height(-terrain_length_x/2+2*i,terrain_length_y/2),terrain_length_y/2,});
    }
    return position;
}
std::vector<vec3> position_barriere_left(int N, float terrain_length_x, float terrain_length_y)
{
    std::vector<cgp::vec3> position;
    for(int i=0;i<N;i++){
        position.push_back({-terrain_length_x/2+2*i,0.5f+evaluate_terrain_height(-terrain_length_x/2+2*i,-terrain_length_y/2),-terrain_length_y/2,});
    }
    return position;
}
