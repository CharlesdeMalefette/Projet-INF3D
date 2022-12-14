#include "mesh simple/God.hpp"
#include "scene/scene.hpp"

using namespace cgp;



void god_structure::bird_initialize()
{
// Create the hierarchy


    mesh_drawable corps;
    mesh_drawable tete;
    mesh_drawable yeux;
    mesh_drawable yeux1;
    mesh_drawable bec;
    mesh_drawable aile_droite_base;
    mesh_drawable aile_gauche_base;
    mesh_drawable aile_droite;
    mesh_drawable aile_gauche;



    corps.initialize(mesh_primitive_sphere(1.0f), "Corps"); corps.anisotropic_scale = vec3{ 1.0f,0.5f,0.4f };
    tete.initialize(mesh_primitive_sphere(0.25f), "Tete");
    yeux.initialize(mesh_primitive_sphere(0.05f), "Yeux");
    yeux1.initialize(mesh_primitive_sphere(0.05f), "Yeux1");
    bec.initialize(mesh_primitive_cone(0.1f, 0.2f, { 0,0,0 }, { pow(3,0.5f) / 2,0,-0.5f }));

    aile_gauche_base.initialize(mesh_primitive_quadrangle({ -0.4f,0,0 }, { -0.3f,-0.6f,0 }, { 0.15f,-0.6f,0 } ,{ 0.4f,0,0 }),
        "Aile gauche base");
    aile_gauche.initialize(mesh_primitive_triangle({ -0.3f,0,0 }, { -0.3f,-0.6f,0 }, { 0.15f,0,0 }), "Aile gauche");

    aile_droite_base.initialize(mesh_primitive_quadrangle({ -0.4f,0,0 }, { -0.3f,0.6f,0 }, { 0.15f,0.6f,0 }, { 0.4f,0,0 }),
        "Aile droite base");
    aile_droite.initialize(mesh_primitive_triangle({ -0.3f,0,0 }, { -0.3f,0.6f,0 }, { 0.15f,0,0 }), "Aile droite");

    yeux.shading.color = { 0,0,0 };
    yeux1.shading.color = { 0,0,0 };
    bec.shading.color = { 0.5f,0.3f,0.3f};
    hierarchy_birds.resize(N_birds);
    for(int i=0;i<N_birds;i++){
    hierarchy_birds[i].add(corps);
    hierarchy_birds[i].add(tete, "Corps", { 1.1f,0,0.2f });
    hierarchy_birds[i].add(yeux, "Tete",{ 0.18f, 0.07f, 0.08f });
    hierarchy_birds[i].add(yeux1, "Tete" ,{ 0.18f, -0.07f, 0.08f });
    hierarchy_birds[i].add(bec, "Tete", { 0.18f,0,-0.08f });
    hierarchy_birds[i].add(aile_gauche_base, "Corps", { 0,-0.3f,0 });
    hierarchy_birds[i].add(aile_gauche, "Aile gauche base",{0,-0.6f,0});
    hierarchy_birds[i].add(aile_droite_base, "Corps", { 0,0.3f,0 });
    hierarchy_birds[i].add(aile_droite, "Aile droite base", { 0,0.6f,0 });

}}

void god_structure::vautour_initialize()
{
// Create the hierarchy



    mesh_drawable corps;
    mesh_drawable tete;
    mesh_drawable cou;
    mesh_drawable echarpe;

    mesh_drawable yeux_globule_gauche;
    mesh_drawable yeux_globule_droite;
    mesh_drawable yeux_centre_gauche;
    mesh_drawable yeux_centre_droite;

    mesh_drawable bec;
    mesh_drawable aile_droite_base;
    mesh_drawable aile_gauche_base;
    mesh_drawable aile_droite;
    mesh_drawable aile_gauche;



    corps.initialize(mesh_primitive_sphere(1.0f), "Corps"); corps.anisotropic_scale = vec3{ 1.0f,0.5f,0.4f };
    cou.initialize(mesh_primitive_cylinder(0.05f,{0,0,0},{0.5f,0,0}),"Cou");
    tete.initialize(mesh_primitive_sphere(0.2f), "Tete");

    //echarpe.initialize(mesh_primitive_torus(0.1f,0.05f,{0,0,0},{1,0,0}));

    yeux_globule_droite.initialize(mesh_primitive_sphere(0.05f), "Yeux_gd");
    yeux_globule_gauche.initialize(mesh_primitive_sphere(0.05f), "Yeux_gg");
    yeux_centre_droite.initialize(mesh_primitive_sphere(0.03f), "Yeux_cd");
    yeux_centre_gauche.initialize(mesh_primitive_sphere(0.03f), "Yeux_cg");

    bec.initialize(mesh_primitive_cone(0.1f, 0.2f, { 0,0,0 }, { pow(3,0.5f) / 2,0,-0.5f }));

    aile_gauche_base.initialize(mesh_primitive_quadrangle({ -0.4f,0,0 }, { -0.3f,-0.6f,0 }, { 0.15f,-0.6f,0 } ,{ 0.4f,0,0 }),
        "Aile gauche base");
    aile_gauche.initialize(mesh_primitive_triangle({ -0.3f,0,0 }, { -0.3f,-0.6f,0 }, { 0.15f,0,0 }), "Aile gauche");

    aile_droite_base.initialize(mesh_primitive_quadrangle({ -0.4f,0,0 }, { -0.3f,0.6f,0 }, { 0.15f,0.6f,0 }, { 0.4f,0,0 }),
        "Aile droite base");
    aile_droite.initialize(mesh_primitive_triangle({ -0.3f,0,0 }, { -0.3f,0.6f,0 }, { 0.15f,0,0 }), "Aile droite");

    // Shading color //

    tete.shading.color = {1,0.4f,0.6f}; // Rose
    cou.shading.color = {1,0.4f,0.6f}; // Rose
    corps.shading.color = {0.2f,0.2f,0.2f}; // Gris foncé
    aile_gauche_base.shading.color = {0.1f,0.1f,0.1f}; // Gris foncé
    aile_droite_base.shading.color = {0.1f,0.1f,0.1f}; // Gris foncé
    aile_gauche.shading.color = {0.1f,0.1f,0.1f}; // Gris foncé
    aile_droite.shading.color = {0.1f,0.1f,0.1f}; // Gris foncé
    yeux_globule_droite.shading.color = { 1,1,1 }; // Blanc
    yeux_globule_gauche.shading.color = { 1,1,1 };
    yeux_centre_droite.shading.color = { 0,0,0 }; // Noir
    yeux_centre_gauche.shading.color = { 0,0,0 }; // Noir
    bec.shading.color = { 0.9f,0.6f,0.1f}; // Jaune bec
    //echarpe.shading.color = {0.8f,0.8f,0.8f};

    // Hierarchize //

    hierarchy_birds.resize(N_vautour);

    for(int i=0;i<N_vautour;i++){
    hierarchy_birds[i].add(corps);
    hierarchy_birds[i].add(cou, "Corps", { 1.1f,0,0.2f });
    //hierarchy_birds[i].add(echarpe, "Cou", { -0.9f,0,0});
    hierarchy_birds[i].add(tete, "Cou", { 1.0f,0,0});
    hierarchy_birds[i].add(yeux_globule_droite, "Tete",{ 0.18f, 0.07f, 0.08f });
    hierarchy_birds[i].add(yeux_globule_gauche, "Tete" ,{ 0.18f, -0.07f, 0.08f });
    hierarchy_birds[i].add(yeux_centre_droite, "Tete",{ 0.23f, 0.07f, 0.08f });
    hierarchy_birds[i].add(yeux_centre_gauche, "Tete" ,{ 0.23f, -0.07f, 0.08f });
    hierarchy_birds[i].add(bec, "Tete", { 0.18f,0,-0.08f });
    hierarchy_birds[i].add(aile_gauche_base, "Corps", { 0,-0.3f,0 });
    hierarchy_birds[i].add(aile_gauche, "Aile gauche base",{0,-0.6f,0});
    hierarchy_birds[i].add(aile_droite_base, "Corps", { 0,0.3f,0 });
    hierarchy_birds[i].add(aile_droite, "Aile droite base", { 0,0.6f,0 });

}}

void god_structure::corbeau_initialize()
{

// Create the hierarchy


    mesh_drawable corps;
    mesh_drawable tete;
    mesh_drawable yeux;
    mesh_drawable yeux1;
    mesh_drawable bec;
    mesh_drawable aile_droite_base;
    mesh_drawable aile_gauche_base;
    mesh_drawable aile_droite;
    mesh_drawable aile_gauche;



    corps.initialize(mesh_primitive_sphere(1.0f), "Corps"); corps.anisotropic_scale = vec3{ 1.0f,0.5f,0.4f };
    tete.initialize(mesh_primitive_sphere(0.25f), "Tete");
    yeux.initialize(mesh_primitive_sphere(0.05f), "Yeux");
    yeux1.initialize(mesh_primitive_sphere(0.05f), "Yeux1");
    bec.initialize(mesh_primitive_cone(0.1f, 0.2f, { 0,0,0 }, { pow(3,0.5f) / 2,0,-0.5f }));

    aile_gauche_base.initialize(mesh_primitive_quadrangle({ -0.4f,0,0 }, { -0.3f,-0.6f,0 }, { 0.15f,-0.6f,0 } ,{ 0.4f,0,0 }),
        "Aile gauche base");
    aile_gauche.initialize(mesh_primitive_triangle({ -0.3f,0,0 }, { -0.3f,-0.6f,0 }, { 0.15f,0,0 }), "Aile gauche");

    aile_droite_base.initialize(mesh_primitive_quadrangle({ -0.4f,0,0 }, { -0.3f,0.6f,0 }, { 0.15f,0.6f,0 }, { 0.4f,0,0 }),
        "Aile droite base");
    aile_droite.initialize(mesh_primitive_triangle({ -0.3f,0,0 }, { -0.3f,0.6f,0 }, { 0.15f,0,0 }), "Aile droite");

    yeux.shading.color = { 1,0,0 };
    yeux1.shading.color = { 1,0,0 };
    bec.shading.color = { 0.2f,0.2f,0.2f};
    corps.shading.color = {0,0,0};
    tete.shading.color = {0,0,0};
    aile_droite_base.shading.color = {0,0,0};
    aile_gauche_base.shading.color = {0,0,0};
    aile_droite.shading.color = {0,0,0};
    aile_gauche.shading.color = {0,0,0};



    hierarchy_birds.resize(N_birds);
    for(int i=0;i<N_birds;i++){
    hierarchy_birds[i].add(corps);
    hierarchy_birds[i].add(tete, "Corps", { 1.1f,0,0.2f });
    hierarchy_birds[i].add(yeux, "Tete",{ 0.18f, 0.07f, 0.08f });
    hierarchy_birds[i].add(yeux1, "Tete" ,{ 0.18f, -0.07f, 0.08f });
    hierarchy_birds[i].add(bec, "Tete", { 0.18f,0,-0.08f });
    hierarchy_birds[i].add(aile_gauche_base, "Corps", { 0,-0.3f,0 });
    hierarchy_birds[i].add(aile_gauche, "Aile gauche base",{0,-0.6f,0});
    hierarchy_birds[i].add(aile_droite_base, "Corps", { 0,0.3f,0 });
    hierarchy_birds[i].add(aile_droite, "Aile droite base", { 0,0.6f,0 });

}}
