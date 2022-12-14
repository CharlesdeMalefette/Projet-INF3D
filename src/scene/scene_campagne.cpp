#include "scene/scene.hpp"
#include "mesh simple/terrain.hpp"
#include "mesh simple/tree.hpp"
#include "mesh simple/God.hpp"
#include "mesh simple/haie.hpp"
#include "mesh simple/pepite.hpp"
#include "mesh simple/barriere.hpp"


using namespace cgp;



god_structure god_campagne;

// Monde 1, cadre rassurant et peu de contrainte pour laisser au joueur le temps de s'accoutumer au jeu et à ses fonctionalités

void scene_structure::initialize_campagne()
{
    // Global settings //

        global_frame.initialize(mesh_primitive_frame(), "Frame");

        // Initial placement of the camera
        environment[1].camera.position_camera = { 3.5f*terrain_length_x, 0.5f, -2.0f };
        environment[1].camera.manipulator_rotate_roll_pitch_yaw(0, 0, Pi / 2.0f);

        // Initialize the Skybox

        skybox.initialize("assets/skybox_campagne/","png");         // indicate a path where to load the 6 texture images

    // Initialisation de la sphere joueuse

       sphere.initialize(mesh_primitive_sphere(sphere_radius), "Sphere");
       sphere.transform.translation = { 3.4f*terrain_length_x, 0.3f, -2.0f };
       sphere.texture = opengl_load_texture_image("assets/haie.jpeg",GL_REPEAT,GL_REPEAT);

    // Initialize the terrain

        //Terrains horizontaux
        int N_terrain_samples = 300;
        mesh const terrain_mesh = create_terrain_mesh(N_terrain_samples, terrain_length_x,terrain_length_y);
        terrain.resize(N_terrain);
        for(int i=0;i<N_terrain;i++){
            terrain[i].initialize(terrain_mesh,"terrain_i");
            terrain[i].transform.translation = i*transl;
            terrain[i].texture = opengl_load_texture_image("assets/grass.jpeg", GL_REPEAT, GL_REPEAT);
            terrain[i].shading.phong.ambient = 0.5f;
            terrain[i].shading.phong.specular = 0;

        } // Terrains verticaux
        terrain_vert.initialize(create_terrain_mesh(N_terrain_samples,terrain_length_x/7,terrain_length_y));
        terrain_vert.texture = opengl_load_texture_image("assets/grass.jpeg", GL_REPEAT, GL_REPEAT);
        terrain_vert.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi/2);
        terrain_vert.shading.phong.ambient = 0;
        terrain_vert.shading.phong.specular = 0;

    // Initialize the trees

        tree.initialize(create_tree(), "Tree");
        tree_position = generate_positions_on_terrain(20, terrain_length_x,terrain_length_y);

    // Initialisation des haies

        gate_right.resize(N_haie);
        gate_left.resize(N_haie);
        for(int i=0;i<N_haie;i++){
            gate_right[i].initialize(create_haie(),"Gate_ir");
            gate_left[i].initialize(create_haie(),"Gate_il");
            gate_left[i].texture = opengl_load_texture_image("assets/haie.jpeg");
            gate_right[i].texture = opengl_load_texture_image("assets/haie.jpeg");}
        gate_position_right = position_barriere_right(N_barreau,terrain_length_x,terrain_length_y);
        gate_position_left = position_barriere_left(N_barreau,terrain_length_x,terrain_length_y);



    // Initialize the mushrooms

        mushroom.initialize(create_mushroom(), "Mushroom");
        mushroom_position = generate_positions_on_terrain(100, terrain_length_x,terrain_length_y);


    // Initialize the grass of billboards

        billboard.initialize(mesh_primitive_quadrangle({ -0.5f,0,0 }, { 0.5f,0,0 }, { 0.5f,0.5f,0 }, { -0.5f,0.5f,0 }), "Quad");
        billboard.texture = opengl_load_texture_image("assets/grass.png");
        billboard.shading.phong = { 0.4f, 0.6f,0,1 };
        billboard.transform.scaling = 1.8f;
        billboard_position = generate_positions_on_terrain(150, terrain_length_x,terrain_length_y-2);

    // Initialisation du personnage de fin

        billboard_rengoku.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
        billboard_rengoku.texture = opengl_load_texture_image("assets/perso_trophes/zoro.png");
        billboard_rengoku.shading.phong.diffuse =0.5f;

    // Initialisation des oiseaux

        god_campagne.bird_initialize();
        z_oiseaux.resize(god_campagne.N_birds);
        for(int i=0;i<god_campagne.N_birds;i++){
            z_oiseaux[i] =rand_interval(-terrain_length_y / 2, terrain_length_y / 2);
}


    // Initialisation des obstacles

        obstacle_cylindre.resize(N_obstacle_cylindre);
        obstacle_tore.resize(N_obstacle_tore);
        check_pepite.resize(N_obstacle_tore);
        position_tore.resize(N_obstacle_tore);
        mesh_score.resize(N_obstacle_tore+1);

        for(int i=0;i<N_obstacle_cylindre;i++){
            obstacle_cylindre[i].initialize(mesh_primitive_cylinder(0.3f,{0,2,0},{0,15,0}));
            obstacle_cylindre[i].texture = opengl_load_texture_image("assets/haie.jpeg");
            obstacle_cylindre[i].shading.phong.specular = 0.5f;}

        for(int i=0;i<N_obstacle_tore;i++){
            obstacle_tore[i].initialize(mesh_primitive_torus(1,0.1f,{0,0,0},{1,0,0}));
            position_tore[i] = rand_interval(-terrain_length_y/2+1,terrain_length_y/2-1);
            //obstacle_tore[i].shading.color = {0.34f,0.16f,0};
            obstacle_tore[i].texture = opengl_load_texture_image("assets/haie.jpeg");
            check_pepite[i]= false;} //Aucune pépite ramassée

    // Initialisation du score

        for(int i=0;i<N_obstacle_tore+1;i++){
            mesh_score[i].initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }));}
        load_score_campagne();

    // Initialisation des pépites

        pepite.initialize(create_pepite());
        pepite.transform.scaling = 2;
        pepite.texture = opengl_load_texture_image("assets/pepite.png", GL_REPEAT, GL_REPEAT);

}





void scene_structure::display_campagne()
{
    // Display the skybox as the first shape
     draw(skybox, environment[1]);

    // Display all the elements of the scene
     display_trees_campagne();
     display_mushroom_campagne();
     display_gate_right_campagne();
     display_gate_left_campagne();
     display_sphere_campagne();
     display_obstacle_campagne();
     display_resultat_campagne();
     display_billboard_campagne();
     display_terrain_campagne();
     display_bird_campagne();

     // Si fin de niveau, on passe au suivant
     if (sphere.transform.translation[0]<-16*terrain_length_x) {
         initialize_roc();
         Numero_monde = 3;
     }

    // Si contact avec obstacles, on va directement à la fin du jeu
    if(contact_obstacle == true){
        initialize_dark();
        Numero_monde = 4;}


         }

void scene_structure::display_bird_campagne() // Affichage des oiseaux
{
    for(int i=0;i<god_campagne.N_birds;i++){

    god_campagne.hierarchy_birds[i]["Tete"].transform.rotation = rotation_transform::from_axis_angle({ 0, 1, 0 }, -0.2f + 0.3f*cos(2*timer.t));
    god_campagne.hierarchy_birds[i]["Aile gauche base"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.5f * cos(8 * timer.t));
    god_campagne.hierarchy_birds[i]["Aile gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.8f * cos(8 * timer.t));
    god_campagne.hierarchy_birds[i]["Aile droite base"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.5f * -cos(8 * timer.t));
    god_campagne.hierarchy_birds[i]["Aile droite"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.8f * -cos(8 * timer.t));


        // This function must be called before the drawing in order to propagate the deformations through the hierarchy
    god_campagne.hierarchy_birds[i].update_local_to_global_coordinates();

    god_campagne.hierarchy_birds[i]["Corps"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },(-Pi/2));

    for(int i=0;i<god_campagne.N_birds;i++){
        cgp::vec3 offset_birds = {terrain_length_x*timer.t/10,10.0f+2*i-0.2f*timer.t,z_oiseaux[i]};
        god_campagne.hierarchy_birds[i]["Corps"].transform.translation = i*transl_birds+offset_birds;
        draw(god_campagne.hierarchy_birds[i],environment[1]);}}

}

void scene_structure::display_terrain_campagne() // Affichage des terrains
{
    for(int i=0;i<N_terrain;i++){
        draw(terrain[i],environment[1]);
        if((sphere.transform.translation[1]<terrain[i].transform.translation[1])&&(sphere.transform.translation[0]<-i*terrain_length_x)) contact_obstacle = true;} // Contact avec le sol
    for(int i=0;i<N_terrain-1;i++){
        terrain_vert.transform.translation = {-(i+0.495f)*terrain_length_x,i*5+2.5f,0};
        draw(terrain_vert,environment[1]);}
}

void scene_structure::display_gate_right_campagne() // Rangée de haie à droite
{
    for(int i=0;i<N_haie;i++){
        gate_right[i].transform.translation = gate_position_right[i];
        for(int j=0;j<N_terrain;j++){
            draw(gate_right[i],environment[1]);
            gate_right[i].transform.translation += transl;}

}}
void scene_structure::display_gate_left_campagne() // A gauche
{
        for(int i=0;i<N_haie;i++){
            gate_left[i].transform.translation = gate_position_left[i];
            for(int j=0;j<N_terrain;j++){
                draw(gate_left[i],environment[1]);
                gate_left[i].transform.translation += transl;}
}

}

void scene_structure::display_obstacle_campagne() // Affichage des obstacles et des pépites
{
    float x_s = sphere.transform.translation[0];
    float y_s = sphere.transform.translation[1];
    float z_s = sphere.transform.translation[2];

    // Display obstacle //

    for(int i=0;i<N_obstacle_cylindre;i++){
        obstacle_cylindre[i].transform.translation = {(-0.5f-float(i))*terrain_length_x,(5.0f*float(i)),14*cos((i+1)*timer.t/4)};
        draw(obstacle_cylindre[i],environment[1]);

        // Contact avec le cylindre

        if((std::abs(x_s-obstacle_cylindre[i].transform.translation[0])<2*sphere_radius)&&(std::abs(z_s-obstacle_cylindre[i].transform.translation[2])<2*sphere_radius))
            contact_obstacle=true;}


    for(int i=0;i<N_obstacle_tore;i++){

        obstacle_tore[i].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 2*timer.t);
        obstacle_tore[i].transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        pepite.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 2*timer.t);
        pepite.transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        draw(obstacle_tore[i],environment[1]);

        // Ramassage de la pépite
        if((std::abs(pepite.transform.translation[0]-sphere.transform.translation[0])<4*sphere_radius)&&(std::abs(pepite.transform.translation[1]-sphere.transform.translation[1])<4*sphere_radius)&&(std::abs(pepite.transform.translation[2]-sphere.transform.translation[2])<4*sphere_radius))
            check_pepite[i] = true; // La pépite est ramassée
        if(check_pepite[i]==false)//Si la pépite est déja ramassée on ne la dessine plus
            draw(pepite,environment[1]);


        // Contact avec le tore

        if((std::abs(obstacle_tore[i].transform.translation[0]-x_s)<0.2f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-sphere.transform.translation[2],2),0.5f)<1.2f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-z_s,2),0.5f)>0.8f)){
            contact_obstacle = true;}}

}

void scene_structure::display_sphere_campagne() // Affichage de la sphère joueuse
{
    // Draw the principal sphere
    draw(sphere,environment[1]);

}
void scene_structure::display_trees_campagne() // Arbres
{
        for (vec3 position: tree_position) {
            for(int i=0;i<N_terrain;i++){
                tree.transform.translation = i*transl + position;
                draw(tree, environment[1]);}}
}

void scene_structure::display_mushroom_campagne() // Champignons
{
    vec3 offset_y = {0,0.05f,0};
    for (vec3 position : mushroom_position) {
        for(int i=0;i<N_terrain;i++){
            mushroom.transform.translation = i*transl + position+offset_y;
            draw(mushroom, environment[1]);
    }
}}


void scene_structure::display_billboard_campagne() // Herbe
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);

    vec3 const offset = { 0,0,0.02f };
    for (vec3 position : billboard_position) {
        for(int i=0;i<N_terrain;i++){
            billboard.transform.translation = i*transl + position - offset;
            draw(billboard, environment[1]);
    }}

    glDepthMask(true);
    glDisable(GL_BLEND);

}

void scene_structure::display_resultat_campagne() // Affichage du score actuel
{
    int pepite_ramassées=0;
    for(int i=0;i<N_obstacle_tore;i++){
        if (check_pepite[i]==true) pepite_ramassées+=1;
    }
    if(pepite_ramassées<15){
    mesh_score[pepite_ramassées].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    mesh_score[pepite_ramassées].transform.translation = {-16*terrain_length_x,24*5,terrain_length_y/2};
    draw(mesh_score[pepite_ramassées],environment[1]);}

    if(pepite_ramassées==15){
        perfect_campagne = true;
        display_billboard_rengoku_campagne();}



}

void scene_structure::display_billboard_rengoku_campagne() // Affichage du personnage final si réussite du niveau
{


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);


    billboard_rengoku.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    billboard_rengoku.transform.translation = {-16*terrain_length_x,18*5,terrain_length_y/2};
    draw(billboard_rengoku,environment[1]);

    glDepthMask(true);
    glDisable(GL_BLEND);

}



