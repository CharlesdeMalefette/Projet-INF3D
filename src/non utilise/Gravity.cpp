#include "Gravity.hpp"
#include "scene/scene.hpp"





using namespace cgp;

scene_structure scene_gravit;


//static void set_gui(timer_basic& timer);


/** Compute spring force applied on particle pi from particle pj */
vec3 spring_force(const vec3& pi, const vec3& pj, float L0, float K)
{
    vec3 const pji = pj - pi;
    float const L = norm(pji);
    return K * (L - L0) * pji / L;
}


void scene_gravity::setup_data()
{
    // Initial position and speed of particles
    // ******************************************* //
    pA.p = {0,0,0};     // Initial position of particle A
    pA.v = {0,0,0};     // Initial speed of particle A

    pB.p = {0.5f,0,0};  // Initial position of particle B
    pB.v = {0,0,0};     // Initial speed of particle B

    pC.p = {1.0f, 0, 0};
    pC.v = {0,0,0};

    L0 = 0.4f; // Rest length between A and B


    // Display elements
    // ******************************************* //
    /*segment_drawer.initialize()
    segment_drawer.uniform_parameter.color = {0,0,1};*/

    sphere.initialize(mesh_primitive_sphere(),"Sphere");
    sphere.transform.scaling = 0.05f;


    std::vector<vec3> borders_segments = {{-1,-1,-1},{1,-1,-1}, {1,-1,-1},{1,1,-1}, {1,1,-1},{-1,1,-1}, {-1,1,-1},{-1,-1,-1},
                                          {-1,-1,1} ,{1,-1,1},  {1,-1,1}, {1,1,1},  {1,1,1}, {-1,1,1},  {-1,1,1}, {-1,-1,1},
                                          {-1,-1,-1},{-1,-1,1}, {1,-1,-1},{1,-1,1}, {1,1,-1},{1,1,1},   {-1,1,-1},{-1,1,1}};
    borders.initialize(borders_segments);
    borders.color = {0,0,0};

}





void scene_gravity::frame_draw()
{
    timer.update();



    // Simulation time step (dt)
    float dt = timer.scale*0.01f;

    // Simulation parameters
    const float m  = 0.01f;        // particle mass
    const float K  = 5.0f;         // spring stiffness
    const float mu = 0.005f;       // damping coefficient

    //float dt = 2.0f / sqrt(K/m);

    const vec3 g   = {0,-9.81f,0}; // gravity

    // Forces
    const vec3 f_spring  = spring_force(pB.p, pA.p, L0, K);
    const vec3 f_weight =  m * g;
    const vec3 f_damping = pB.v * mu; // TO DO: correct this force value
    const vec3 F = f_spring+f_weight - f_damping;

    // Numerical Integration (Verlet)
    {
        // Only particle B should be updated
        vec3& p = pB.p; // position of particle
        vec3& v = pB.v; // speed of particle

        p = p + dt * v;
        v = v + dt * F / m;

        //const vec3 f2_spring  = spring_force(pC.p, pB.p, L0, K);
        //const vec3 f2_damping = pC.v * mu;
        //const vec3 F2 = f2_spring+f_weight - f2_damping;

        //pC.v = pC.v + dt * F2 / m;
        //pC.p = pC.p + dt * pC.v;
    }




    // Display of the result

    // particle pa
    sphere.transform.translation = pA.p;
    sphere.shading.color = {0,0,0};
    draw(sphere, scene_gravit.environment[0]);

    // particle pb
    sphere.transform.translation = pB.p;
    sphere.shading.color = {1,0,0};
    //draw(sphere, scene_gravit.environment[0]);

    // Spring pa-pb
    segment_drawer.uniform_parameter.p1 = pA.p;
    segment_drawer.uniform_parameter.p2 = pB.p;
    //draw(segment_drawer,scene_gravit.environment[0]);


    /*sphere.uniform.transform.translation = pC.p;
    sphere.uniform.color = {1,1,0};
    draw(sphere, scene.camera, shaders["mesh"]);
    segment_drawer.uniform_parameter.p1 = pB.p;
    segment_drawer.uniform_parameter.p2 = pC.p;
    segment_drawer.draw(shaders["segment_im"],scene.camera); */


    //draw(borders, scene.camera);
}

/*
// Part specific GUI drawing
static void set_gui(timer_basic& timer)
{
    // Can set the speed of the animation
    float scale_min = 0.05f;
    float scale_max = 2.0f;
    ImGui::SliderScalar("Time scale", ImGuiDataType_Float, &timer.scale, &scale_min, &scale_max, "%.2f s");

    // Start and stop animation
    if (ImGui::Button("Stop"))
        timer.stop();
    if (ImGui::Button("Start"))
        timer.start();

}*/
