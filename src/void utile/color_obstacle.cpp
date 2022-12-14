#include "scene/scene.hpp"
using namespace cgp;

// Fonctions qui colorient les obstacles pour le monde arc-en-ciel

// Obstacles cylindriques horizontaux
void scene_structure::color_obstacle_horiz_light()
{
    for(int i=0;i<N_obstacle_cylindre_horiz_light;i++){
    if(i%7 == 0)
        obstacle_cylindre_horiz[i].shading.color = {1,0,0};
    if(i%7 == 1)
        obstacle_cylindre_horiz[i].shading.color = {1,0.5f,0};
    if(i%7 == 2)
        obstacle_cylindre_horiz[i].shading.color = {1,1,0};
    if(i%7 == 3)
        obstacle_cylindre_horiz[i].shading.color = {0,1,0};
    if(i%7 == 4)
        obstacle_cylindre_horiz[i].shading.color = {0,0,1};
    if(i%7 == 5)
        obstacle_cylindre_horiz[i].shading.color = {0.2f,0.2f,0.4f};
    if(i%7 == 6)
        obstacle_cylindre_horiz[i].shading.color = {0.5f,0,1};
}
}


// Obstacles cylindriques verticaux
void scene_structure::color_obstacle_vert_light()
{
    for(int i=0;i<N_obstacle_cylindre_light;i++){
    if(i%7 == 0)
        obstacle_cylindre[i].shading.color = {1,0,0};
    if(i%7 == 1)
        obstacle_cylindre[i].shading.color = {1,0.5f,0};
    if(i%7 == 2)
        obstacle_cylindre[i].shading.color = {1,1,0};
    if(i%7 == 3)
        obstacle_cylindre[i].shading.color = {0,1,0};
    if(i%7 == 4)
        obstacle_cylindre[i].shading.color = {0,0,1};
    if(i%7 == 5)
        obstacle_cylindre[i].shading.color = {0.2f,0.2f,0.4f};
    if(i%7 == 6)
        obstacle_cylindre[i].shading.color = {0.5f,0,1};
}
}

// Obstacles toriques
void scene_structure::color_obstacle_tore_light()
{
    for(int i=0;i<N_obstacle_tore;i++){
    if(i%7 == 0)
        obstacle_tore[i].shading.color = {1,0,0};
    if(i%7 == 1)
        obstacle_tore[i].shading.color = {1,0.5f,0};
    if(i%7 == 2)
        obstacle_tore[i].shading.color = {1,1,0};
    if(i%7 == 3)
        obstacle_tore[i].shading.color = {0,1,0};
    if(i%7 == 4)
        obstacle_tore[i].shading.color = {0,0,1};
    if(i%7 == 5)
        obstacle_tore[i].shading.color = {0.2f,0.2f,0.4f};
    if(i%7 == 6)
        obstacle_tore[i].shading.color = {0.5f,0,1};
}
}
