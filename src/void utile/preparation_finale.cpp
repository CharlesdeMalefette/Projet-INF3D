
#include "scene/scene.hpp"
using namespace cgp;

// Fonction qui prépare tous les cas de figure de réussite, 1 seul sera affiché en fin de partie en fonction de la réussite de la partie
// crl signifie que le monde Campagne, Roc, Light a été réussi parfaitement mais pas Volcan
// lv  signifie que le monde Light, Volcan a été réussi parfaitement mais pas Campagne et Roc
// etc..

void scene_structure::load_preparation_finale()
{
    parfait.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    parfait.texture = opengl_load_texture_image("assets/parfait.png");


    crl.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    crl.texture = opengl_load_texture_image("assets/ending/crl.png");

    crv.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    crv.texture = opengl_load_texture_image("assets/ending/crv.png");

    clv.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    clv.texture = opengl_load_texture_image("assets/ending/clv.png");

    rlv.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    rlv.texture = opengl_load_texture_image("assets/ending/rlv.png");

    cr.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    cr.texture = opengl_load_texture_image("assets/ending/cr.png");

    cl.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    cl.texture = opengl_load_texture_image("assets/ending/cl.png");

    cv.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    cv.texture = opengl_load_texture_image("assets/ending/cv.png");

    rl.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    rl.texture = opengl_load_texture_image("assets/ending/rl.png");

    rv.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    rv.texture = opengl_load_texture_image("assets/ending/rv.png");

    lv.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    lv.texture = opengl_load_texture_image("assets/ending/lv.png");

    c.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    c.texture = opengl_load_texture_image("assets/ending/c.png");

    r.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    r.texture = opengl_load_texture_image("assets/ending/r.png");

    l.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    l.texture = opengl_load_texture_image("assets/ending/l.png");

    v.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    v.texture = opengl_load_texture_image("assets/ending/v.png");

    neant.initialize(mesh_primitive_quadrangle({ 0,0,-terrain_length_y }, { 0,30,-terrain_length_y }, { 0,30,terrain_length_y }, { 0,0,terrain_length_y }), "Rengoku");
    neant.texture = opengl_load_texture_image("assets/ending/neant.png");



}
