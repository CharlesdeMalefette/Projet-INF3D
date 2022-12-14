#include "cactus.hpp"

using namespace cgp;


mesh create_cactus()
{
    mesh base = mesh_primitive_cylinder(0.1f,{0,0,0},{0,1.5f,0});
    base.push_back(mesh_primitive_cylinder(0.08f,{0,0.5f,-0.3f},{0,1,-0.3f,}));
    base.push_back(mesh_primitive_cylinder(0.08f,{0,0.5f,0.3f},{0,1.1f,0.3f}));
    base.push_back(mesh_primitive_cylinder(0.08f,{0,0.5f,0},{0,0.5f,0.34f}));
    base.push_back(mesh_primitive_cylinder(0.08f,{0,0.5f,0},{0,0.5f,-0.34f}));
    base.push_back(mesh_primitive_sphere(0.1f,{0,1.5f,0}));
    base.push_back(mesh_primitive_sphere(0.08f,{0,1,-0.3f}));
    base.push_back(mesh_primitive_sphere(0.08f,{0,1.1f,0.3f}));

    return base;
}


