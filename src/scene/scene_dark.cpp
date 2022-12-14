#include "scene/scene.hpp"

using namespace cgp;

void scene_structure::initialize_dark()
{
    global_frame.initialize(mesh_primitive_frame(), "Frame");


    // Initial placement of the camera
        environment[4].camera.position_camera = { 1.8f*terrain_length_x, 15.0f, 0 };
        environment[4].camera.manipulator_rotate_roll_pitch_yaw(-Pi/2, 0, Pi / 2.0f);
    // Initialize the Skybox
    skybox.initialize("assets/skybox_dark/","png");

// Préparer les félicitations finales
    load_preparation_finale();

}

void scene_structure::display_dark()
{
    // Basic elements of the scene
    environment[4].light = environment[4].camera.position();
    environment[4].camera.manipulator_rotate_roll_pitch_yaw(0.001f*cos(timer.t),0,0);
    draw(skybox,environment[4]);

            if((perfect_campagne==true)&(perfect_roc==true)&(perfect_light==true)&(perfect_volcan==true)) draw(parfait,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==true)&(perfect_light==true)&(perfect_volcan==false)) draw(crl,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==true)&(perfect_light==false)&(perfect_volcan==true)) draw(crv,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==false)&(perfect_light==true)&(perfect_volcan==true)) draw(clv,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==true)&(perfect_light==true)&(perfect_volcan==true)) draw(rlv,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==true)&(perfect_light==false)&(perfect_volcan==false)) draw(cr,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==false)&(perfect_light==true)&(perfect_volcan==false)) draw(cl,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==false)&(perfect_light==false)&(perfect_volcan==true)) draw(cv,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==true)&(perfect_light==true)&(perfect_volcan==false)) draw(rl,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==true)&(perfect_light==false)&(perfect_volcan==true)) draw(rv,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==false)&(perfect_light==true)&(perfect_volcan==true)) draw(lv,environment[4]);
            if((perfect_campagne==true)&(perfect_roc==false)&(perfect_light==false)&(perfect_volcan==false)) draw(c,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==true)&(perfect_light==false)&(perfect_volcan==false)) draw(r,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==false)&(perfect_light==true)&(perfect_volcan==false)) draw(l,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==false)&(perfect_light==false)&(perfect_volcan==true)) draw(v,environment[4]);
            if((perfect_campagne==false)&(perfect_roc==false)&(perfect_light==false)&(perfect_volcan==false)) draw(neant,environment[4]);

}
