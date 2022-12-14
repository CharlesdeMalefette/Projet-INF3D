#include "haie.hpp"

using namespace cgp;

mesh create_haie()
{
    mesh haie = mesh_primitive_parallepipède({0,0,0},2.0f,2.0f,0.7f);
    return haie;

}
