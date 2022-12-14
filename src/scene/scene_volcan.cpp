#include "scene/scene.hpp"

#include "mesh simple/terrain.hpp"
#include "mesh simple/tree.hpp"
#include "mesh simple/gate.hpp"
#include "mesh simple/God.hpp"
#include "mesh simple/pepite.hpp"

using namespace cgp;

// Monde 3, difficulté supplémentaire : des comètes qui balaient le terrain
// Environnement plus angoissant qui sonne une fin de jeu proche



god_structure god_volcan;



void scene_structure::initialize_volcan()
{

    // Basic set-up

        global_frame.initialize(mesh_primitive_frame(), "Frame");

        // Initial placement of the camera
        environment[2].camera.position_camera = { 2*terrain_length_x, 0.5f, -2.0f };
        environment[2].camera.manipulator_rotate_roll_pitch_yaw(0, 0, Pi / 2.0f);

        // Initialize the Skybox
        skybox.initialize("assets/skybox_volcan/","png");


     // Initialize the sphere fixe
         sphere.initialize(mesh_primitive_sphere(sphere_radius), "Sphere");
         sphere.transform.translation = { 1.9*terrain_length_x, 0.3f, -2.0f };
         sphere.texture = opengl_load_texture_image("assets/magma.jpg",GL_REPEAT,GL_REPEAT);


     // Initialize a planet, anneau, meteorite //

         planet.initialize(mesh_primitive_sphere(5.0f),"Planet");
         planet.texture = opengl_load_texture_image("assets/Venus.jpeg", GL_REPEAT, GL_REPEAT);

         anneau.initialize(mesh_primitive_torus(8.0f,0.5f,{0,0,0},{0,sqrt(0.91f),0.3f}));
         anneau.texture = opengl_load_texture_image("assets/anneau.jpeg", GL_REPEAT, GL_REPEAT);

         meteorite.initialize(mesh_primitive_sphere(1.0f),"Meteorite");
         meteorite.texture = opengl_load_texture_image("assets/meteorite.jpeg", GL_REPEAT, GL_REPEAT);


    // Initialize the terrain

        int N_terrain_samples = 300;
        mesh const terrain_mesh = create_terrain_mesh(N_terrain_samples, terrain_length_x,terrain_length_y);
        terrain.resize(N_terrain);
        for(int i=0;i<N_terrain;i++){
            terrain[i].initialize(terrain_mesh,"terrain_i");
            terrain[i].transform.translation = i*transl;
            terrain[i].shading.phong.specular = 0.5f;
            terrain[i].texture = opengl_load_texture_image("assets/magma.jpg", GL_REPEAT, GL_REPEAT);
        }
        terrain_vert.initialize(create_terrain_mesh(N_terrain_samples,terrain_length_x/7,terrain_length_y));
        terrain_vert.texture = opengl_load_texture_image("assets/magma.jpg", GL_REPEAT, GL_REPEAT);
        terrain_vert.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi/2);
        terrain_vert.shading.phong.ambient = 0;
        terrain_vert.shading.phong.specular = 0;


    // Initialize the rocher

        mesh rocher_mesh = mesh_load_file_obj("assets/Rock.obj");
        rocher_tombant.initialize(rocher_mesh,"rocher");
        rocher_tombant.texture = opengl_load_texture_image("assets/lave.jpeg",GL_REPEAT,GL_REPEAT);

        rocher.initialize(rocher_mesh,"rocher");
        rocher.texture = opengl_load_texture_image("assets/lave.jpeg",GL_REPEAT,GL_REPEAT);
        rocher.transform.scaling = 0.4f;
        rocher_position = generate_positions_on_terrain(10,terrain_length_x,terrain_length_y);

        z_rocher.resize(N_terrain);
        for(int i=0;i<N_terrain;i++)
            z_rocher[i] =rand_interval(-terrain_length_y / 2, terrain_length_y / 2);


    // Initialize the trees, pepite //
        tree.initialize(create_tree_volcan(), "Tree");
        tree_position = generate_positions_on_terrain(20, terrain_length_x,terrain_length_y);

        pepite.initialize(create_pepite());
        pepite.transform.scaling = 2;
        pepite.texture = opengl_load_texture_image("assets/pepite.png", GL_REPEAT, GL_REPEAT);




    // Initialize the gate //

        int N_barreau = 40;
        gate_right.resize(N_barreau);
        gate_left.resize(N_barreau);
        for(int i=0;i<N_barreau;i++){
            gate_right[i].initialize(create_gate(N_barreau,i),"Gate_ir");
            gate_left[i].initialize(create_gate(N_barreau,i),"Gate_il");}

        gate_position_right = position_gate_right(N_barreau,terrain_length_x,terrain_length_y);
        gate_position_left = position_gate_left(N_barreau,terrain_length_x,terrain_length_y);


    // Personnage final : Ace //

        billboard_rengoku.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
        billboard_rengoku.texture = opengl_load_texture_image("assets/perso_trophes/Ace.png");
        billboard_rengoku.shading.phong.diffuse =0.5f;

    // Initialisation des corbeaux

        god_volcan.corbeau_initialize();
        z_oiseaux.resize(god_volcan.N_corbeau);
        for(int i=0;i<god_volcan.N_corbeau;i++)
            z_oiseaux[i] =rand_interval(-terrain_length_y / 2, terrain_length_y / 2);

    // Initialisation du dragon
        mesh dragon_mesh = mesh_load_file_obj("assets/Dragon.obj");
        dragon.initialize(dragon_mesh,"dragon");

        dragon.transform.scaling = 0.03f;
        dragon.texture = opengl_load_texture_image("assets/dragon.jpeg");
        dragon.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, Pi/2);



    // Initialisation des obstacles
        obstacle_cylindre.resize(N_obstacle_cylindre_volcan);
        obstacle_tore.resize(N_obstacle_tore);
        check_pepite.resize(N_obstacle_tore);
        position_tore.resize(N_obstacle_tore);
        mesh_score.resize(N_obstacle_tore+1);

        for(int i=0;i<N_obstacle_cylindre_volcan;i++){
            obstacle_cylindre[i].initialize(mesh_primitive_cylinder(0.2f,{0,0,0},{0,18,0}));
            obstacle_cylindre[i].texture = opengl_load_texture_image("assets/lave.jpeg");}

        for(int i=0;i<N_obstacle_tore;i++){
            obstacle_tore[i].initialize(mesh_primitive_torus(1,0.1f,{0,0,0},{1,0,0}));
            position_tore[i] = rand_interval(-terrain_length_y/2+1,terrain_length_y/2-1);
            obstacle_tore[i].texture = opengl_load_texture_image("assets/magma.jpg");
            check_pepite[i]= false;} //Aucune pépite ramassée
    // Initialisation du score

        for(int i=0;i<N_obstacle_tore+1;i++){
            mesh_score[i].initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }));}
        load_score_volcan();

}





void scene_structure::display_volcan()
{

     // Basic elements of the scene
     environment[2].light = environment[2].camera.position();

    // Display the skybox as the first shape
     draw(skybox, environment[2]);

     // Launch display functions //

     display_gate_left_volcan();
     display_gate_right_volcan();
     display_obstacle_volcan();
     display_astres_volcan();
     display_sphere_volcan();
     display_dragon_volcan();
     display_resultat_volcan();
     display_terrain_volcan();
     display_trees_volcan();
     display_corbeau_volcan();
     display_rocher_volcan();
     display_rocher_tombant_volcan();


     // Si fin de niveau, on passe au suivant
     if (sphere.transform.translation[0]<-16*terrain_length_x) {
         initialize_light();
         Numero_monde = 0;
     }

    // Si contact avec obstacles, on va directement à la fin du jeu
    if(contact_obstacle == true){
        initialize_dark();
        Numero_monde = 4;}

}

void scene_structure::display_terrain_volcan()
{
    for(int i=0;i<N_terrain;i++){
       draw(terrain[i],environment[2]);
        if((sphere.transform.translation[1]<terrain[i].transform.translation[1]+1)&&(sphere.transform.translation[0]<-i*terrain_length_x)) contact_obstacle = true;} // Contact avec le sol}
    for(int i=0;i<N_terrain-1;i++){
       terrain_vert.transform.translation = {-(i+0.495f)*terrain_length_x,i*5+2.5f,0};
       draw(terrain_vert,environment[2]);}
}

void scene_structure::display_corbeau_volcan()
{
    for(int i=0;i<god_volcan.N_corbeau;i++){

    god_volcan.hierarchy_birds[i]["Tete"].transform.rotation = rotation_transform::from_axis_angle({ 0, 1, 0 }, -0.2f + 0.3f*cos(2*timer.t));
    god_volcan.hierarchy_birds[i]["Aile gauche base"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.5f * cos(8 * timer.t));
    god_volcan.hierarchy_birds[i]["Aile gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.8f * cos(8 * timer.t));
    god_volcan.hierarchy_birds[i]["Aile droite base"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.5f * -cos(8 * timer.t));
    god_volcan.hierarchy_birds[i]["Aile droite"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 0.8f * -cos(8 * timer.t));


        // This function must be called before the drawing in order to propagate the deformations through the hierarchy
    god_volcan.hierarchy_birds[i].update_local_to_global_coordinates();

    god_volcan.hierarchy_birds[i]["Corps"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },(-Pi/2));

    for(int i=0;i<god_volcan.N_corbeau;i++){
        cgp::vec3 offset_birds = {terrain_length_x*timer.t/10,15.0f-0.15f*timer.t,z_oiseaux[i]};
        god_volcan.hierarchy_birds[i]["Corps"].transform.translation = i*transl_birds+offset_birds;
        draw(god_volcan.hierarchy_birds[i],environment[2]);}}

}

void scene_structure::display_obstacle_volcan()
{
    float x_s = sphere.transform.translation[0];
    float y_s = sphere.transform.translation[1];
    float z_s = sphere.transform.translation[2];
    // Display obstacle //

    for(int i=0;i<N_obstacle_cylindre_volcan;i++){
        obstacle_cylindre[i].transform.translation = {(-0.5f-float(i/4))*terrain_length_x,(5.0f*float(i/4)),14*cos((i+1)*timer.t/30)};
        draw(obstacle_cylindre[i],environment[2]);
        if((std::abs(x_s-obstacle_cylindre[i].transform.translation[0])<2*sphere_radius)&&(std::abs(z_s-obstacle_cylindre[i].transform.translation[2])<2*sphere_radius))
            contact_obstacle=true;}


    for(int i=0;i<N_obstacle_tore;i++){

        obstacle_tore[i].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 2*timer.t);
        obstacle_tore[i].transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        pepite.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 2*timer.t);
        pepite.transform.translation = {-i*terrain_length_x,i*5+4,position_tore[i]};

        draw(obstacle_tore[i],environment[2]);

        // Ramassage de la pépite
        if((std::abs(pepite.transform.translation[0]-sphere.transform.translation[0])<4*sphere_radius)&&(std::abs(pepite.transform.translation[1]-sphere.transform.translation[1])<4*sphere_radius)&&(std::abs(pepite.transform.translation[2]-sphere.transform.translation[2])<4*sphere_radius))
            check_pepite[i] = true; // La pépite est ramassée
        if(check_pepite[i]==false)//Si la pépite est déja ramassée on ne la dessine plus
            draw(pepite,environment[2]);

        if((std::abs(obstacle_tore[i].transform.translation[0]-x_s)<0.3f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-sphere.transform.translation[2],2),0.5f)<1.26f)&&(pow(pow(obstacle_tore[i].transform.translation[1]-y_s,2)+pow(obstacle_tore[i].transform.translation[2]-z_s,2),0.5f)>0.74f)){
            contact_obstacle = true;}}


}

void scene_structure::display_astres_volcan()
{
    // Display planet, anneau, meteorite
    planet.transform.rotation = rotation_transform::from_axis_angle({ 0,sqrt(0.91f),0.3f }, 2*timer.t);
    planet.transform.translation = {-3*terrain_length_x,25.0f,-2*terrain_length_y};

    anneau.transform.rotation = rotation_transform::from_axis_angle({ 0,sqrt(0.91f),0.3f }, 2*timer.t);
    anneau.transform.translation = {-3*terrain_length_x,25.0f,-2*terrain_length_y};

    draw(anneau,environment[2]);
    draw(planet,environment[2]);

    planet.transform.rotation = rotation_transform::from_axis_angle({ 0,sqrt(0.91f),-0.3f }, 2*timer.t);
    planet.transform.translation = {-2*terrain_length_x,25.0f,2*terrain_length_y};

    anneau.transform.rotation = rotation_transform::from_axis_angle({ 0,sqrt(0.91f),-0.3f }, 2*timer.t);
    anneau.transform.translation = {-2*terrain_length_x,25.0f,2*terrain_length_y};

    draw(anneau,environment[2]);
    draw(planet,environment[2]);

    planet.transform.rotation = rotation_transform::from_axis_angle({ 0,-sqrt(0.91f),0.3f }, 2*timer.t);
    planet.transform.translation = {-6*terrain_length_x,25.0f,2.5f*terrain_length_y};

    anneau.transform.rotation = rotation_transform::from_axis_angle({ 0,-sqrt(0.91f),0.3f }, 2*timer.t);
    anneau.transform.translation = {-6*terrain_length_x,25.0f,2.5f*terrain_length_y};

    draw(anneau,environment[2]);
    draw(planet,environment[2]);


   for(int i=0;i <N_meteorite;i++){
       meteorite.transform.rotation = rotation_transform::from_axis_angle({ 0,sqrt(0.91f),-0.3f }, 2*timer.t);
       meteorite.transform.translation = {-i*terrain_length_x+2*timer.t,10.0f+5*i-timer.t,2*terrain_length_y*cos(i*timer.t/5)};
       draw(meteorite,environment[2]);}
}

void scene_structure::display_trees_volcan()
{
        for (vec3 position: tree_position) {
            for(int i=0;i<N_terrain;i++){
                tree.transform.translation = i*transl + position;
                draw(tree, environment[2]);}}
}

void scene_structure::display_dragon_volcan()
{
    for(int i=0;i<N_terrain/2;i++){
        dragon.transform.translation = {-2*i*terrain_length_x,2.5f+10*i,i%2*10-i};
        draw(dragon,environment[2]);}
}

void scene_structure::display_sphere_volcan()
{
    // Draw the principal sphere
    draw(sphere,environment[2]);

}

void scene_structure::display_rocher_volcan()
{
    vec3 const offset = { 0,1,0 };
    for (vec3 position: rocher_position) {
            for(int i=0;i<N_terrain;i++){
                rocher.transform.translation = i*transl + position+offset;
                draw(rocher, environment[2]);}}


}

void scene_structure::display_rocher_tombant_volcan()
{
            for(int i=0;i<N_terrain;i++){



                if(rocher_tombant.transform.translation[1] > terrain[i].transform.translation[1]-12.0f){
                    vec3 move_rocher = {0,50+10*i-0.5f*9.81f*timer.t,z_rocher[i]};
                    rocher_tombant.transform.rotation = rotation_transform::from_axis_angle({0,0,1 }, timer.t);
                    rocher_tombant.transform.translation = i*transl + move_rocher;
                    // Contact avec les rochers tombant
                    draw(rocher_tombant,environment[2]);
                    if((std::abs(rocher_tombant.transform.translation[0]-sphere.transform.translation[0])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[1]-sphere.transform.translation[1])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[2]-sphere.transform.translation[2])<2*sphere_radius)) contact_obstacle = true;

                    vec3 move_rocher_2 = {0,50+10*i-0.5f*9.81f*timer.t,-z_rocher[i]};
                    rocher_tombant.transform.rotation = rotation_transform::from_axis_angle({0,0,-1 }, timer.t);
                    rocher_tombant.transform.translation = i*transl + move_rocher_2;
                    draw(rocher_tombant,environment[2]);
                    if((std::abs(rocher_tombant.transform.translation[0]-sphere.transform.translation[0])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[1]-sphere.transform.translation[1])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[2]-sphere.transform.translation[2])<2*sphere_radius)) contact_obstacle = true;}

                else {
                    vec3 move_rocher = {0,2.7f,z_rocher[i]};
                    rocher_tombant.transform.rotation = rotation_transform::from_axis_angle({0,0,1 }, 0);
                    rocher_tombant.transform.translation = i*transl + move_rocher;
                    draw(rocher_tombant,environment[2]);
                    if((std::abs(rocher_tombant.transform.translation[0]-sphere.transform.translation[0])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[1]-sphere.transform.translation[1])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[2]-sphere.transform.translation[2])<2*sphere_radius)) contact_obstacle = true;

                    vec3 move_rocher_2 = {0,2.7f,-z_rocher[i]};
                    rocher_tombant.transform.rotation = rotation_transform::from_axis_angle({0,0,-1 }, 0);
                    rocher_tombant.transform.translation = i*transl + move_rocher_2;
                    draw(rocher_tombant,environment[2]);
                    if((std::abs(rocher_tombant.transform.translation[0]-sphere.transform.translation[0])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[1]-sphere.transform.translation[1])<2*sphere_radius)&&(std::abs(rocher_tombant.transform.translation[2]-sphere.transform.translation[2])<2*sphere_radius)) contact_obstacle = true;}

              }
}

void scene_structure::display_gate_right_volcan()
{
    for(int i=0;i<terrain_length_x;i++){
        gate_right[i].transform.translation = gate_position_right[i];
        for(int j=0;j<N_terrain;j++){
            gate_right[i].shading.color = {1,0.6f*std::abs(cos(3*timer.t)),0};
            draw(gate_right[i],environment[2]);
            gate_right[i].transform.translation += transl;}

}

}

void scene_structure::display_gate_left_volcan()
{
        for(int i=0;i<terrain_length_x;i++){
            gate_left[i].transform.translation = gate_position_left[i];
            for(int j=0;j<N_terrain;j++){
                gate_left[i].shading.color = {1,0.6f*std::abs(cos(3*timer.t)),0};
                draw(gate_left[i],environment[2]);
                gate_left[i].transform.translation += transl;}
}

}


void scene_structure::display_resultat_volcan()
{
    int pepite_ramassées=0;
    for(int i=0;i<N_obstacle_tore;i++){
        if (check_pepite[i]==true) pepite_ramassées+=1;
    }
    if(pepite_ramassées<15){
    mesh_score[pepite_ramassées].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    mesh_score[pepite_ramassées].transform.translation = {-16*terrain_length_x,24*5,terrain_length_y/2};
    draw(mesh_score[pepite_ramassées],environment[2]);}

    if(pepite_ramassées==15){
        perfect_volcan = true;
        display_billboard_ace_volcan();}




}

void scene_structure::display_billboard_ace_volcan()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);


    billboard_rengoku.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi/2);
    billboard_rengoku.transform.translation = {-16*terrain_length_x,18*5,terrain_length_y/2};
    draw(billboard_rengoku,environment[2]);

    glDepthMask(true);
    glDisable(GL_BLEND);

}


