#include "scene/scene.hpp"
using namespace cgp;


// Fonction qui initialise les obstacles pour le monde de la lumière (mise dans un autre fichier car volumineux)

void scene_structure::initialize_obstacle_light()
{
    // Initialisation des obstacles
        obstacle_cylindre.resize(N_obstacle_cylindre_light);
        obstacle_cylindre_horiz.resize(N_obstacle_cylindre_horiz_light);
        obstacle_tore.resize(N_obstacle_tore);
        position_tore.resize(N_obstacle_tore);



        for(int i=0;i<N_obstacle_cylindre_light;i++){
            obstacle_cylindre[i].initialize(mesh_primitive_cylinder(0.3f,{0,0,0},{0,15,0}));
            obstacle_cylindre[i].shading.color = {1,1,0};
            obstacle_cylindre[i].shading.phong.specular = 1;}

        for(int i=0;i<N_obstacle_cylindre_horiz_light;i++){
            obstacle_cylindre_horiz[i].initialize(mesh_primitive_cylinder(0.3f,{0,0,-terrain_length_y/2},{0,0,terrain_length_y/2}));
            obstacle_cylindre_horiz[i].shading.color = {1,1,0};
            obstacle_cylindre_horiz[i].shading.phong.specular = 1;}

        for(int i=0;i<N_obstacle_tore;i++){
            obstacle_tore[i].initialize(mesh_primitive_torus(1,0.1f,{0,0,0},{1,0,0}));
            position_tore[i] = rand_interval(-terrain_length_y/2+1,terrain_length_y/2-1);
            obstacle_tore[i].shading.color = {float(i)/N_obstacle_tore,float((1-i))/N_obstacle_tore,0};
            //obstacle_tore[i].texture = opengl_load_texture_image("assets/sable.jpeg");
            check_pepite[i]= false; //Aucune pépite ramassée

    }
}
