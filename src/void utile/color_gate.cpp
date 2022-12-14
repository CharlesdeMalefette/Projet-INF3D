
#include "scene/scene.hpp"
using namespace cgp;

// Fonction qui colorie les barrières pour le monde arc-en-ciel


void scene_structure::color_gate_light()
{
    for(int i=0;i<N_barreau;i++){
    if(i%7 == 0)
        gate_right[i].shading.color = {1,0,0};
    if(i%7 == 1)
        gate_right[i].shading.color = {1,0.5f,0};
    if(i%7 == 2)
        gate_right[i].shading.color = {1,1,0};
    if(i%7 == 3)
        gate_right[i].shading.color = {0,1,0};
    if(i%7 == 4)
        gate_right[i].shading.color = {0,0,1};
    if(i%7 == 5)
        gate_right[i].shading.color = {0.2f,0.2f,0.4f};
    if(i%7 == 6)
        gate_right[i].shading.color = {0.5f,0,1};

    if(i%7 == 0)
        gate_left[i].shading.color = {1,0,0};
    if(i%7 == 1)
        gate_left[i].shading.color = {1,0.5f,0};
    if(i%7 == 2)
        gate_left[i].shading.color = {1,1,0};
    if(i%7 == 3)
        gate_left[i].shading.color = {0,1,0};
    if(i%7 == 4)
        gate_left[i].shading.color = {0,0,1};
    if(i%7 == 5)
        gate_left[i].shading.color = {0.2f,0.2f,0.5f};
    if(i%7 == 6)
        gate_left[i].shading.color = {0.5f,0,1};
    }
}
