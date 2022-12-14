#include "telegraphe.hpp"

using namespace cgp;

mesh create_telegraphe()
{
    mesh telegraphe = mesh_primitive_cylinder(0.1f,{-1,0,-2},{-1,6.0f,-2});
    telegraphe.push_back(mesh_primitive_cylinder(0.2f,{6,0,5},{6,6.0f,5}));
    telegraphe.push_back(mesh_primitive_arrow({-1,6.0f,-2},{6,6.0f,5}));

    return telegraphe;
}
