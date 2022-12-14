
#include "scene/scene.hpp"
using namespace cgp;

// Fonctions qui pour chaque monde initialisent tous les scores possibles à afficher

void scene_structure::load_score_roc()
{

    mesh_score[0].texture = opengl_load_texture_image("assets/score_roc/zero.png");
    mesh_score[1].texture = opengl_load_texture_image("assets/score_roc/un.png");
    mesh_score[2].texture = opengl_load_texture_image("assets/score_roc/deux.png");
    mesh_score[3].texture = opengl_load_texture_image("assets/score_roc/trois.png");
    mesh_score[4].texture = opengl_load_texture_image("assets/score_roc/quatre.png");
    mesh_score[5].texture = opengl_load_texture_image("assets/score_roc/cinq.png");
    mesh_score[6].texture = opengl_load_texture_image("assets/score_roc/six.png");
    mesh_score[7].texture = opengl_load_texture_image("assets/score_roc/sept.png");
    mesh_score[8].texture = opengl_load_texture_image("assets/score_roc/huit.png");
    mesh_score[9].texture = opengl_load_texture_image("assets/score_roc/neuf.png");
    mesh_score[10].texture = opengl_load_texture_image("assets/score_roc/dix.png");
    mesh_score[11].texture = opengl_load_texture_image("assets/score_roc/onze.png");
    mesh_score[12].texture = opengl_load_texture_image("assets/score_roc/douze.png");
    mesh_score[13].texture = opengl_load_texture_image("assets/score_roc/treize.png");
    mesh_score[14].texture = opengl_load_texture_image("assets/score_roc/quatorze.png");
    mesh_score[15].texture = opengl_load_texture_image("assets/score_roc/quinze.png");

}

void scene_structure::load_score_campagne()
{

    mesh_score[0].texture = opengl_load_texture_image("assets/score_campagne/zero.png");
    mesh_score[1].texture = opengl_load_texture_image("assets/score_campagne/un.png");
    mesh_score[2].texture = opengl_load_texture_image("assets/score_campagne/deux.png");
    mesh_score[3].texture = opengl_load_texture_image("assets/score_campagne/trois.png");
    mesh_score[4].texture = opengl_load_texture_image("assets/score_campagne/quatre.png");
    mesh_score[5].texture = opengl_load_texture_image("assets/score_campagne/cinq.png");
    mesh_score[6].texture = opengl_load_texture_image("assets/score_campagne/six.png");
    mesh_score[7].texture = opengl_load_texture_image("assets/score_campagne/sept.png");
    mesh_score[8].texture = opengl_load_texture_image("assets/score_campagne/huit.png");
    mesh_score[9].texture = opengl_load_texture_image("assets/score_campagne/neuf.png");
    mesh_score[10].texture = opengl_load_texture_image("assets/score_campagne/dix.png");
    mesh_score[11].texture = opengl_load_texture_image("assets/score_campagne/onze.png");
    mesh_score[12].texture = opengl_load_texture_image("assets/score_campagne/douze.png");
    mesh_score[13].texture = opengl_load_texture_image("assets/score_campagne/treize.png");
    mesh_score[14].texture = opengl_load_texture_image("assets/score_campagne/quatorze.png");
    mesh_score[15].texture = opengl_load_texture_image("assets/score_campagne/quinze.png");

}

void scene_structure::load_score_volcan()
{
    mesh_score[0].texture = opengl_load_texture_image("assets/score_volcan/zero.png");
    mesh_score[1].texture = opengl_load_texture_image("assets/score_volcan/un.png");
    mesh_score[2].texture = opengl_load_texture_image("assets/score_volcan/deux.png");
    mesh_score[3].texture = opengl_load_texture_image("assets/score_volcan/trois.png");
    mesh_score[4].texture = opengl_load_texture_image("assets/score_volcan/quatre.png");
    mesh_score[5].texture = opengl_load_texture_image("assets/score_volcan/cinq.png");
    mesh_score[6].texture = opengl_load_texture_image("assets/score_volcan/six.png");
    mesh_score[7].texture = opengl_load_texture_image("assets/score_volcan/sept.png");
    mesh_score[8].texture = opengl_load_texture_image("assets/score_volcan/huit.png");
    mesh_score[9].texture = opengl_load_texture_image("assets/score_volcan/neuf.png");
    mesh_score[10].texture = opengl_load_texture_image("assets/score_volcan/dix.png");
    mesh_score[11].texture = opengl_load_texture_image("assets/score_volcan/onze.png");
    mesh_score[12].texture = opengl_load_texture_image("assets/score_volcan/douze.png");
    mesh_score[13].texture = opengl_load_texture_image("assets/score_volcan/treize.png");
    mesh_score[14].texture = opengl_load_texture_image("assets/score_volcan/quatorze.png");
    mesh_score[15].texture = opengl_load_texture_image("assets/score_volcan/quinze.png");

}

void scene_structure::load_score_light()
{
    mesh_score[0].texture = opengl_load_texture_image("assets/score_light/zero.png");
    mesh_score[1].texture = opengl_load_texture_image("assets/score_light/un.png");
    mesh_score[2].texture = opengl_load_texture_image("assets/score_light/deux.png");
    mesh_score[3].texture = opengl_load_texture_image("assets/score_light/trois.png");
    mesh_score[4].texture = opengl_load_texture_image("assets/score_light/quatre.png");
    mesh_score[5].texture = opengl_load_texture_image("assets/score_light/cinq.png");
    mesh_score[6].texture = opengl_load_texture_image("assets/score_light/six.png");
    mesh_score[7].texture = opengl_load_texture_image("assets/score_light/sept.png");
    mesh_score[8].texture = opengl_load_texture_image("assets/score_light/huit.png");
    mesh_score[9].texture = opengl_load_texture_image("assets/score_light/neuf.png");
    mesh_score[10].texture = opengl_load_texture_image("assets/score_light/dix.png");
    mesh_score[11].texture = opengl_load_texture_image("assets/score_light/onze.png");
    mesh_score[12].texture = opengl_load_texture_image("assets/score_light/douze.png");
    mesh_score[13].texture = opengl_load_texture_image("assets/score_light/treize.png");
    mesh_score[14].texture = opengl_load_texture_image("assets/score_light/quatorze.png");
    mesh_score[15].texture = opengl_load_texture_image("assets/score_light/quinze.png");

}

