#include "pepite.hpp"

using namespace cgp;

mesh create_pepite()
{
    mesh pepite = mesh_primitive_tetrahedron({0,0,0},{0,0,0.2f},{0.1f,0,0.1f},{0.1f,0.2f,0.1f});
    pepite.push_back(mesh_primitive_tetrahedron({0,0.1f,-0.05f},{0.1f,0.05f,0.1f},{0.05f,0.1f,0.15f},{-0.05f,0.2f,0.2f}));
    pepite.push_back(mesh_primitive_tetrahedron({0,0.15f,0.05f},{0.05f,0.05f,0.05f},{0.05f,0.05f,0.2f},{-0.1f,0.1f,0.1f}));
    return pepite;
}
