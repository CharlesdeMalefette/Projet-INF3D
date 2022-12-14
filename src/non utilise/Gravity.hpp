

#include "cgp/cgp.hpp"


struct particle_element
{
    cgp::vec3 p; // Position
    cgp::vec3 v; // Speed
};

struct scene_gravity
{
public :
    void setup_data();
    void frame_draw();


    particle_element pA;
    particle_element pB;
    particle_element pC;
    float L0;


    cgp::mesh_drawable sphere;      // Visual display of particles
    cgp::segments_drawable borders; // Visual display of borders
    cgp::segments_drawable segment_drawer;

    cgp::timer_basic timer;
};






