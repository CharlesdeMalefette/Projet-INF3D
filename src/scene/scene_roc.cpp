#include "scene/scene.hpp"

#include "mesh simple/terrain.hpp"
#include "mesh simple/tree.hpp"
#include "mesh simple/cactus.hpp"
#include "mesh simple/gate.hpp"
#include "mesh simple/God.hpp"
#include "mesh simple/barriere.hpp"
#include "mesh simple/telegraphe.hpp"
#include "mesh simple/pepite.hpp"

using namespace cgp;

// Monde 2, obstacle plus rapide et nouvel obstacle à éviter : les télégraphes
// Le joueur s'étant habitué au jeu pourra alors découvrir un nouvel environnement moins familier et plus original

god_structure god_roc;



void scene_structure::initialize_roc()
{


    // Global settings

        global_frame.initialize(mesh_primitive_frame(), "Frame");

        // Initial placement of the camera
        environment[3].camera.position_camera = { 3.5f*terrain_length_x, 0.5f, -2.0f };
        environment[3].camera.manipulator_rotate_roll_pitch_yaw(0, 0, Pi / 2.0f);

        // Initialize the Skybox
        skybox.initialize("assets/skybox_roc/","png");         // indicate a path where to load the 6 texture images


    // Initialize the sphere fixe
         sphere.initialize(mesh_primitive_sphere(sphere_radius), "Sphere");
         sphere.transform.translation = { 3.4f*terrain_length_x, 0.3f, -2.0f };
         sphere.texture = opengl_load_texture_image("assets/sable.jpeg",GL_REPEAT,GL_REPEAT);

    // Rocher
         mesh rocher_mesh = mesh_load_file_obj("assets/Rock.obj");
         rocher.initialize(rocher_mesh,"rocher");
         rocher.texture = opengl_load_texture_image("assets/roc.jpeg",GL_REPEAT,GL_REPEAT);
         rocher.transform.scaling = 0.5f;
         rocher_position = generate_positions_on_terrain(20,terrain_length_x,terrain_length_y);
         z_rocher.resize(N_terrain);
         for(int i=0;i<N_terrain;i++)
             z_rocher[i] =rand_interval(-terrain_length_y / 2, terrain_length_y / 2);


    // Initialize the terrain

        int N_terrain_samples = 300;

        mesh const terrain_mesh = create_terrain_mesh(N_terrain_samples, terrain_length_x,terrain_length_y);
        terrain.resize(N_terrain);
        for(int i=0;i<N_terrain;i++){
            terrain[i].initialize(terrain_mesh,"terrain_i");
            terrain[i].transform.translation = i*transl;
            terrain[i].shading.phong.specular = 0.5f;
            terrain[i].texture = opengl_load_texture_image("assets/sable.jpeg", GL_REPEAT, GL_REPEAT);}

        terrain_vert.initialize(create_terrain_mesh(N_terrain_samples,terrain_length_x/7,terrain_length_y));
        terrain_vert.texture = opengl_load_texture_image("assets/sable.jpeg", GL_REPEAT, GL_REPEAT);
        terrain_vert.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi/2);
        terrain_vert.shading.phong.ambient = 0;
        terrain_vert.shading.phong.specular = 0;


    // Initialize les vautours //

        god_roc.vautour_initialize();
        z_oiseaux.resize(god_roc.N_vautour);
        for(int i=0;i<god_roc.N_vautour;i++)
            z_oiseaux[i] =rand_interval(-terrain_length_y / 2, terrain_length_y / 2);

    // Initialize the cactus, telegraphe //

        cactus.initialize(create_cactus(),"Cactus");
        cactus_position = generate_positions_on_terrain(20,terrain_length_x,terrain_length_y);
        cactus.texture = opengl_load_texture_image("assets/cactus.jpeg", GL_REPEAT, GL_REPEAT);

        telegraphe.initialize(create_telegraphe(),"Telegraphe");
        telegraphe.texture=opengl_load_texture_image("assets/barriere.jpeg");


    // Initialisation des barrières //

        gate_right.resize(N_barriere);
        gate_left.resize(N_barriere);
        for(int i=0;i<N_barriere;i++){
            gate_right[i].initialize(create_barriere(),"Gate_ir");
            gate_left[i].initialize(create_barriere(),"Gate_il");
            gate_left[i].texture = opengl_load_texture_image("assets/barriere.jpeg");
            gate_right[i].texture = opengl_load_texture_image("assets/barriere.jpeg");}
        gate_position_right = position_barriere_right(N_barriere,terrain_length_x,terrain_length_y);
        gate_position_left = position_barriere_left(N_barriere,terrain_length_x,terrain_length_y);


    // Initialize billboards //


        billboard_rengoku.initialize(mesh_primitive_quadrangle({ 0,0,-1.5f*terrain_length_y }, { 0,30,-1.5f*terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
        billboard_rengoku.texture = opengl_load_texture_image("assets/perso_trophes/crocodile.png");



        // Initialisation des obstacles

            obstacle_cylindre.resize(N_obstacle_cylindre);
            obstacle_tore.resize(N_obstacle_tore);
            check_pepite.resize(N_obstacle_tore);
            position_tore.resize(N_obstacle_tore);
            mesh_score.resize(N_obstacle_tore+1);

            for(int i=0;i<N_obstacle_cylindre;i++){
                obstacle_cylindre[i].initialize(mesh_primitive_cylinder(0.3f,{0,2,0},{0,15,0}));
                obstacle_cylindre[i].texture = opengl_load_texture_image("assets/barriere.jpeg");
                obstacle_cylindre[i].shading.phong.specular = 0.5f;}

            for(int i=0;i<N_obstacle_tore;i++){
                obstacle_tore[i].initialize(mesh_primitive_torus(1,0.1f,{0,0,0},{1,0,0}));
                position_tore[i] = rand_interval(-terrain_length_y/2+1,terrain_length_y/2-1);
                obstacle_tore[i].texture = opengl_load_texture_image("assets/sable.jpeg");
                check_pepite[i]= false;} //Aucune pépite ramassée


      // Initialisation du score
            for(int i=0;i<N_obstacle_tore+1;i++){
                mesh_score[i].initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }));}
            load_score_roc();


        pepite.initialize(create_pepite());
        pepite.transform.scaling = 2;
        pepite.texture = opengl_load_texture_image("assets/pepite.png", GL_REPEAT, GL_REPEAT);}


void scene_structure::display_roc()
{

     // Basic elements of the scene
     environment[3].light = environment[3].camera.position();

    // Display the skybox as the first shape
     draw(skybox, environment[3]);

     // Launch display functions //


     display_obstacle_roc();
     display_cactus_roc();
     display_rocher_roc();
     display_barriere_left_roc();
     display_barriere_right_roc();
     display_sphere_roc();
     display_resultat_roc();
     display_vautour_roc();
     display_terrain_roc();
     display_telegraphe_roc();

     // Si fin de niveau, on passe au suivant
     if (sphere.transform.translation[0]<-16*terrain_length_x) {
         initialize_volcan();
         Numero_monde = 2;
     }

    // Si contact avec obstacles, on va directement à la fin du jeu
    if(contact_obstacle == true){
        initialize_dark();
        Numero_monde = 4;}

}


void scene_structure::display_terrain_roc()
{
    for(int i=0;i<N_terrain;i++){
        draw(terrain[i],environment[3]);
        if((sphere.transform.translation[1]<terrain[i].transform.translation[1])&&(sphere.transform.translation[0]<-i*terrain_length_x)) contact_obstacle = true;} // Contact avec le sol}
    for(int i=0;i<N_terrain-1;i++){
        terrain_vert.transform.translation = {-(i+0.495f)*terrain_length_x,i*5+2.5f,0};
        draw(terrain_vert,environment[3]);}
}

void scene_structure::display_telegraphe_roc()
{
    for(int i=0;i<N_terrain;i++){
        vec3 position_telegraphe = {2.0f,0,3-i%2*4+0.5*i};
        telegraphe.transform.translation = i*transl+position_telegraphe;
        draw(telegraphe,environment[3]);
        //if(((sphere.transform.translation[0]-telegraphe.transform.translation[0])<0.5f*sphere_radius)&&(sphere.transform.translation[2]-telegraphe.transform.translation[2]<0.5f*sphere_radius))
          //     contact_obstacle = true;

    }
}

void scene_structure::display_obstacle_roc()
{
    float x_s = sphere.transform.translation[0];
    float y_s = sphere.transform.translation[1];
    float z_s = sphere.transform.translation[2];

    // Display obstacle //

    for(int i=0;i<N_obstacle_cylindre;i++){
        obstacle_cylindre[i].transform.translation = {(-0.5f-float(i))*terrain_length_x,(5.0f*float(i)),14*cos((i+1)*timer.t/4)};
        draw(obstacle_cylindre[i],environment[3]);

        // Contact avec le cylindre

        //if((std::abs(x_s-obstacle_cylindre[i].transform.translation[0])<2*sphere_radius)&&(z_s >13*cos((i+1)*timer.t/4))&&(z_s <15*cos((i+1)*timer.t/4)))
        if((std::abs(x_s-obstacle_cylindre[i].transform.translation[0])<2*sphere_radius)&&(std::abs(z_s-obstacle_cylindre[i].transform.translation[2])<2*sphere_radius))
            contact_obstacle=true;}


    for(int i=0;i<N_obstacle_tore;i++){

        obstacle_tore[i].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 2*timer.t);
        obstacle_tore[i].transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        pepite.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 2*timer.t);
        pepite.transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        draw(obstacle_tore[i],environment[3]);

        // Ramassage de la pépite
        if((std::abs(pepite.transform.translation[0]-sphere.transform.translation[0])<4*sphere_radius)&&(std::abs(pepite.transform.translation[1]-sphere.transform.translation[1])<4*sphere_radius)&&(std::abs(pepite.transform.translation[2]-sphere.transform.translation[2])<4*sphere_radius))
            check_pepite[i] = true; // La pépite est ramassée
        if(check_pepite[i]==false)//Si la pépite est déja ramassée on ne la dessine plus
            draw(pepite,environment[3]);


        // Contact avec le tore

        if((std::abs(obstacle_tore[i].transform.translation[0]-x_s)<0.2f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-sphere.transform.translation[2],2),0.5f)<1.24f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-z_s,2),0.5f)>0.76f)){
            contact_obstacle = true;}}

}

void scene_structure::display_vautour_roc()
{
    for(int i=0;i<god_roc.N_vautour;i++){

        god_roc.hierarchy_birds[i]["Cou"].transform.rotation = rotation_transform::from_axis_angle({ 0, 1, 0 }, -0.2f + 0.3f*cos(2*timer.t));
        god_roc.hierarchy_birds[i]["Aile gauche base"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.5f * cos(8 * timer.t));
        god_roc.hierarchy_birds[i]["Aile gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.8f * cos(8 * timer.t));
        god_roc.hierarchy_birds[i]["Aile droite base"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.5f * -cos(8 * timer.t));
        god_roc.hierarchy_birds[i]["Aile droite"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.8f * -cos(8 * timer.t));


            // This function must be called before the drawing in order to propagate the deformations through the hierarchy
        god_roc.hierarchy_birds[i].update_local_to_global_coordinates();

        god_roc.hierarchy_birds[i]["Corps"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },(-Pi/2));

        for(int i=0;i<god_roc.N_vautour;i++){
            cgp::vec3 offset_birds = {terrain_length_x*timer.t/10,15.0f-0.15f*timer.t,z_oiseaux[i]};
            god_roc.hierarchy_birds[i]["Corps"].transform.translation = i*transl_birds+offset_birds;
            draw(god_roc.hierarchy_birds[i],environment[3]);}}


            }


void scene_structure::display_sphere_roc()
{
    // Draw the principal sphere
    draw(sphere,environment[3]);

}



void scene_structure::display_barriere_right_roc()
{
    for(int i=0;i<N_barriere;i++){
        gate_right[i].transform.translation = gate_position_right[i];
        for(int j=0;j<N_terrain;j++){
            draw(gate_right[i],environment[3]);
            gate_right[i].transform.translation += transl;}

}

}
void scene_structure::display_barriere_left_roc()
{
        for(int i=0;i<N_barriere;i++){
            gate_left[i].transform.translation = gate_position_left[i];
            for(int j=0;j<N_terrain;j++){
                draw(gate_left[i],environment[3]);
                gate_left[i].transform.translation += transl;}


}

}

void scene_structure::display_cactus_roc()
{
    vec3 const offset = { 0,0,0.05f };
        for (vec3 position: cactus_position) {
            for(int i=0;i<N_terrain;i++){
                cactus.transform.translation = i*transl + position - offset;    
                draw(cactus, environment[3]);}}
}

void scene_structure::display_rocher_roc()
{
    vec3 const offset = { 0,1,0 };
    for (vec3 position: rocher_position) {
            for(int i=0;i<N_terrain;i++){
                rocher.transform.translation = i*transl + position+offset;
                draw(rocher, environment[3]);}}


}



void scene_structure::display_resultat_roc()
{
    int pepite_ramassées=0;
    for(int i=0;i<N_obstacle_tore;i++){
        if (check_pepite[i]==true) pepite_ramassées+=1;
    }
    if(pepite_ramassées<15){
    mesh_score[pepite_ramassées].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    mesh_score[pepite_ramassées].transform.translation = {-16*terrain_length_x,24*5,terrain_length_y/2};
    draw(mesh_score[pepite_ramassées],environment[3]);}

    if(pepite_ramassées==15){
        perfect_roc = true;
        display_billboard_rengoku_roc();}


}


void scene_structure::display_billboard_rengoku_roc() // Affichage du personnage final si réussite du niveau
{


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);


    billboard_rengoku.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    billboard_rengoku.transform.translation = {-16*terrain_length_x,18*5,terrain_length_y/2};
    draw(billboard_rengoku,environment[3]);

    glDepthMask(true);
    glDisable(GL_BLEND);

}



