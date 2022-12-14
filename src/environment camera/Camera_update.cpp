
#include "environment camera/Camera_update.hpp"
#include "scene/scene.hpp"
#include "gui/display_gui.hpp"

using namespace cgp;

gui_parameters gui_cam;



// The main function implementing the Moving Mode

void scene_structure::update_camera()
{

    // Constantes de mouvement

    float const pitch = 1.0f; // speed of the pitch
    float const roll  = 1.0f; // speed of the roll
    float const yaw = 1.0f; // speed of the yaw
    float const translate = 5.0f; // speed of the translation

    // Touche du clavier

    inputs_keyboard_parameters const& keyboard = inputs.keyboard;

    // Pas de temps

    float const dt = timer.update();

    // Poistion de la sphère par rapport à la caméra

    vec3 offset_sphere = {-0.1*terrain_length_x,-0.2f,0};


    // Créer la caméra du monde courant
        camera_head& camera = environment[Numero_monde].camera;
        vec3 const forward_displacement = (2*bijection()+speed) * 0.3f * dt * camera.front(); //   We consider in this example a constant velocity, so the displacement is: velocity * dt * front-camera-vector
        // 2*bijection indique qu'on accélère le rythme à chaque monde

        //if((mode_jeu == true)&&(Numero_monde!=4)){ // Dans le monde dark on ne bouge pas
            camera.position_camera += forward_displacement; // The camera moves forward all the time in player mode only
            sphere.transform.translation = camera.position_camera+offset_sphere;//}



        /*// Wind, du vent déplace en permanence la sphère, projet abandonné car trop le jeu devenait trop compliqué avec les collisions
        if(sphere.transform.translation[0]<-2*terrain_length_x){
            timer.update();
            camera.position_camera += {0,0,0.04f};
            sphere.transform.translation += {0,0,0.04f};}*/





    // **************************//
    // Touches du clavier engendrant un déplacement de la caméra et de la sphère qui suit, utilisateur en mode admin seulement pour le mouv arrière//

    if(keyboard.tab){ // Mouvement vers l'avant
        camera.position_camera += 2*forward_displacement;
        sphere.transform.translation = camera.position_camera+offset_sphere;}

    if(mode_jeu == false){ // Mode admin
    if(keyboard.backspace){ // Mouvement vers l'arrière
        camera.position_camera -= forward_displacement;
        sphere.transform.translation = camera.position_camera+offset_sphere;}}




    // Movement of rotation, utilisable seulement en mode administrateur //
    if(mode_jeu == false){ // Mode admin
    if (keyboard.a)
        camera.manipulator_rotate_roll_pitch_yaw(roll*dt, 0, 0);

    if (keyboard.z)
        camera.manipulator_rotate_roll_pitch_yaw(-roll*dt, 0, 0);

    if (keyboard.w)
        camera.manipulator_rotate_roll_pitch_yaw(0, pitch*dt, 0);

    if (keyboard.q)
        camera.manipulator_rotate_roll_pitch_yaw(0, -pitch*dt, 0);

    if (keyboard.s)
        camera.manipulator_rotate_roll_pitch_yaw(0, 0, yaw*dt);

    if (keyboard.x)
        camera.manipulator_rotate_roll_pitch_yaw(0, 0, -yaw*dt);}


    // Movement of translation, utilisable tout le temps

    if (keyboard.up){
        camera.manipulator_translate_in_plane({0,-1.5f*translate*dt});
        sphere.transform.translation = camera.position_camera+offset_sphere;}

    if (keyboard.down){
        camera.manipulator_translate_in_plane({0,1.5f*translate*dt});
        sphere.transform.translation = camera.position_camera+offset_sphere;}

    if (keyboard.right){
        camera.manipulator_translate_in_plane({-2*translate*dt,0});
        sphere.transform.translation = camera.position_camera+offset_sphere;}

    if (keyboard.left){
        camera.manipulator_translate_in_plane({2*translate*dt,0});
        sphere.transform.translation = camera.position_camera+offset_sphere;}


}

int scene_structure::bijection() // associe les numero_monde à leur vrai ordre dans le jeu, corrige notre erreur initiale
{
    if(Numero_monde == 0) return 4; //Monde 4:light
    if(Numero_monde == 1) return 1; //Monde 1:campagne
    if(Numero_monde == 2) return 3; //Monde 4:volcan
    if(Numero_monde == 3) return 2; //Monde 2: roc
}
