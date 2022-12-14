#include "scene/scene.hpp"

#include "mesh simple/terrain.hpp"
#include "non utilise/interpolation.hpp"
#include "mesh simple/barriere.hpp"
#include "mesh simple/pepite.hpp"


using namespace cgp;

// Monde 4, dernier monde, le plus difficile avec des obstacles trés nombreux et un environnement psychedelique
// Comparable à la route arc-en-ciel de mario kart


void scene_structure::initialize_light()
{

    // Basic set-up

        global_frame.initialize(mesh_primitive_frame(), "Frame");

        // Initial placement of the camera
        environment[0].camera.position_camera = { 3*terrain_length_x, 0.5f, -2.0f };
        environment[0].camera.manipulator_rotate_roll_pitch_yaw(0, 0, Pi / 2.0f);

        // Initialize the Skybox
        skybox.initialize("assets/skybox_light/","png");         // indicate a path where to load the 6 texture images


    // Initialize the sphere

         sphere.initialize(mesh_primitive_sphere(sphere_radius), "Sphere");
         sphere.transform.translation = { 2.9*terrain_length_x, 0.3f, -2.0f };
         sphere.texture = opengl_load_texture_image("assets/arc_en_ciel.jpeg",GL_REPEAT,GL_REPEAT);


     // Initialize the terrain

        int N_terrain_samples = 300;
        mesh const terrain_mesh = create_terrain_mesh_light(N_terrain_samples, terrain_length_x,terrain_length_y);
        terrain.resize(N_terrain);
        for(int i=0;i<N_terrain;i++){
            terrain[i].initialize(terrain_mesh,"terrain_i");
            terrain[i].transform.translation = i*transl;
            terrain[i].shading.phong.specular = 0.5f;
            terrain[i].texture = opengl_load_texture_image("assets/arc_en_ciel.jpeg", GL_REPEAT, GL_REPEAT);}
        terrain_vert.initialize(create_terrain_mesh_light(N_terrain_samples,terrain_length_x/7,terrain_length_y));
        terrain_vert.texture = opengl_load_texture_image("assets/arc_en_ciel.jpeg", GL_REPEAT, GL_REPEAT);
        terrain_vert.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi/2);
        terrain_vert.shading.phong.ambient = 0;
        terrain_vert.shading.phong.specular = 0;


     // Initialisation des barrières //

            int N_barreau = 40;
            gate_right.resize(N_barreau);
            gate_left.resize(N_barreau);
            for(int i=0;i<N_barreau;i++){
                gate_right[i].initialize(create_gate(N_barreau,i),"Gate_ir");
                gate_left[i].initialize(create_gate(N_barreau,i),"Gate_il");}
            color_gate_light();
            gate_position_right = position_gate_right_light(N_barreau,terrain_length_x,terrain_length_y);
            gate_position_left = position_gate_left_light(N_barreau,terrain_length_x,terrain_length_y);


      // Initialisation du score et du résultat final //

            billboard_rengoku.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
            billboard_rengoku.texture = opengl_load_texture_image("assets/perso_trophes/kizaru.png");

            check_pepite.resize(N_obstacle_tore);
            mesh_score.resize(N_obstacle_tore);

            for(int i=0;i<N_obstacle_tore;i++)
                mesh_score[i].initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }));
            load_score_light();

     // Initialisation des obstacles //

        initialize_obstacle_light();
        color_obstacle_horiz_light();
        color_obstacle_vert_light();
        color_obstacle_tore_light();

     // Initialisation des pépites //

        pepite.initialize(create_pepite());
        pepite.transform.scaling = 2;
        pepite.texture = opengl_load_texture_image("assets/pepite.png", GL_REPEAT, GL_REPEAT);}


void scene_structure::display_light()
{
     // Basic elements of the scene
     environment[0].light = environment[0].camera.position();

    // Display the skybox as the first shape
     draw(skybox, environment[0]);

     // Launch display functions //
     display_obstacle_light();
     display_sphere_light();
     display_resultat_light();
     display_terrain_light();
     display_gate_right_light();
     display_gate_left_light();

     // Si fin de niveau, on passe au suivant
     if (sphere.transform.translation[0]<-16*terrain_length_x) {
         initialize_dark();
         Numero_monde = 4;
     }

    // Si contact avec obstacles, on va directement à la fin du jeu
    if(contact_obstacle == true){
        initialize_dark();
        Numero_monde = 4;}

}

void scene_structure::display_terrain_light()
{
    for(int i=0;i<N_terrain;i++){
        draw(terrain[i],environment[0]);
        if((sphere.transform.translation[1]<terrain[i].transform.translation[1])&&(sphere.transform.translation[0]<-i*terrain_length_x)) contact_obstacle = true;} // Contact avec le sol
    for(int i=0;i<N_terrain-1;i++){
        terrain_vert.transform.translation = {-(i+0.495f)*terrain_length_x,i*5+2.5f,0};
        draw(terrain_vert,environment[0]);}
}

void scene_structure::display_obstacle_light()
{
    float x_s = sphere.transform.translation[0];
    float y_s = sphere.transform.translation[1];
    float z_s = sphere.transform.translation[2];

    // Display obstacle //

    for(int i=0;i<N_obstacle_cylindre_light;i++){
        obstacle_cylindre[i].transform.translation = {(0.5-float(i/2))*terrain_length_x,1+2.1f*i,14*cos((i+1)*timer.t/14)};
        draw(obstacle_cylindre[i],environment[0]);
        if((std::abs(x_s-obstacle_cylindre[i].transform.translation[0])<2*sphere_radius)&&(std::abs(z_s-obstacle_cylindre[i].transform.translation[2])<2*sphere_radius))
            contact_obstacle=true;}

    for(int i=0;i<N_obstacle_cylindre_horiz_light;i++){
        obstacle_cylindre_horiz[i].transform.translation = {(0.5f-float(i/2))*terrain_length_x,6+2.5f*i-3+10*cos((i+1)*timer.t/15),0};
        draw(obstacle_cylindre_horiz[i],environment[0]);
        if((std::abs(x_s-obstacle_cylindre_horiz[i].transform.translation[0])<2.0f*sphere_radius)&&(std::abs(y_s-obstacle_cylindre_horiz[i].transform.translation[1])<2.0f*sphere_radius))
          contact_obstacle=true;}


    for(int i=0;i<N_obstacle_tore;i++){

        obstacle_tore[i].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 2*timer.t);
        obstacle_tore[i].transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        pepite.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 2*timer.t);
        pepite.transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        draw(obstacle_tore[i],environment[0]);

        // Ramassage de la pépite
        if((std::abs(pepite.transform.translation[0]-sphere.transform.translation[0])<4*sphere_radius)&&(std::abs(pepite.transform.translation[1]-sphere.transform.translation[1])<4*sphere_radius)&&(std::abs(pepite.transform.translation[2]-sphere.transform.translation[2])<4*sphere_radius))
            check_pepite[i] = true; // La pépite est ramassée
        if(check_pepite[i]==false)//Si la pépite est déja ramassée on ne la dessine plus
            draw(pepite,environment[0]);

        if((std::abs(obstacle_tore[i].transform.translation[0]-x_s)<0.3f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-sphere.transform.translation[2],2),0.5f)<1.28f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-z_s,2),0.5f)>0.72f)){
            contact_obstacle = true;}}


}


void scene_structure::display_sphere_light()
{
    // Draw the principal sphere
    draw(sphere,environment[0]);

}


void scene_structure::display_gate_right_light()
{
    for(int i=0;i<terrain_length_x;i++){
        gate_right[i].transform.translation = gate_position_right[i];
        for(int j=0;j<N_terrain;j++){
            draw(gate_right[i],environment[0]);
            gate_right[i].transform.translation += transl;}

}

}

void scene_structure::display_gate_left_light()
{
        for(int i=0;i<terrain_length_x;i++){
            gate_left[i].transform.translation = gate_position_left[i];
            for(int j=0;j<N_terrain;j++){
                draw(gate_left[i],environment[0]);
                gate_left[i].transform.translation += transl;}
}

}

void scene_structure::display_resultat_light() // Affichage du score courant
{
    int pepite_ramassées=0;
    for(int i=0;i<N_obstacle_tore;i++){
        if (check_pepite[i]==true) pepite_ramassées+=1;
    }
    if(pepite_ramassées<15){
    mesh_score[pepite_ramassées].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    mesh_score[pepite_ramassées].transform.translation = {-16*terrain_length_x,24*5,terrain_length_y/2};
    draw(mesh_score[pepite_ramassées],environment[0]);}

    if(pepite_ramassées==15){ // Affichage du personnage final si toutes les pépites sont ramassées
        perfect_light = true;
        display_billboard_kizaru_light();}
}





void scene_structure::display_billboard_kizaru_light()
{


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);


    billboard_rengoku.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    billboard_rengoku.transform.translation = {-16*terrain_length_x,18*5,terrain_length_y/2};
    draw(billboard_rengoku,environment[0]);

    glDepthMask(true);
    glDisable(GL_BLEND);


}



