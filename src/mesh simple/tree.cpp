#include "tree.hpp"

using namespace cgp;




mesh create_cylinder_mesh(float radius, float height)
{

    mesh m;

    // Number of samples
    int N = 20;

    // Geometry
    for(int k=0; k<N; ++k)
    {
        float u = k/float(N);
        //vec3 p = {radius*std::cos(2*3.14f*u), radius*std::sin(2*3.14f*u), 0.0f};
        vec3 p = {radius*std::cos(2*3.14f*u), 0.0f, radius*std::sin(2*3.14f*u)};
        m.position.push_back( p );
        //m.position.push_back( p+vec3(0,0,height) );
        m.position.push_back( p+vec3(0,height,0) );
    }

    // Connectivity
    for(int k=0; k<N; ++k)
    {
        int u00 = 2*k;
        int u01 = (2*k+1)%(2*N);
        int u10 = (2*(k+1))%(2*N);
        int u11 = (2*(k+1)+1) % (2*N);

        uint3 t1 = {u00, u10, u11};
        uint3 t2 = {u00, u11, u01};
        m.connectivity.push_back(t1);
        m.connectivity.push_back(t2);
    }

    m.fill_empty_field();
    return m;
}

mesh create_cone_mesh(float radius, float height, float z_offset)
{

    mesh m;

    // conical structure
    // *************************** //

    int N = 20;

    // geometry
    for(int k=0; k<N; ++k)
    {
        float u = k/float(N);
        //vec3 p = {radius*std::cos(2*3.14f*u), radius*std::sin(2*3.14f*u), 0.0f};
        vec3 p = {radius*std::cos(2*3.14f*u), 0.0f, radius*std::sin(2*3.14f*u)};
        //m.position.push_back( p+vec3{0,0,z_offset} );
        m.position.push_back( p+vec3{0,z_offset,0} );
    }
    // apex
    //m.position.push_back({0,0,height+z_offset});
    m.position.push_back({0,height+z_offset,0});

    // connectivity
    int Ns = N;
    for(int k=0; k<Ns; ++k) {
        //m.connectivity.push_back( {k , (k+1)%Ns, Ns} );
        m.connectivity.push_back( {k , Ns,(k+1)%Ns} );
    }

    // close the bottom of the cone
    // *************************** //

    // Geometry
    for(int k=0; k<N; ++k)
    {
        float u = k/float(N);
        //vec3 p = {radius*std::cos(2*3.14f*u), radius*std::sin(2*3.14f*u), 0.0f};
        vec3 p = {radius*std::cos(2*3.14f*u), 0.0f,radius*std::sin(2*3.14f*u)};
        //m.position.push_back( p+vec3{0,0,z_offset} );
        m.position.push_back( p+vec3{0,z_offset,0} );
    }
    // central position
    //m.position.push_back( {0,0,z_offset} );
    m.position.push_back( {0,z_offset,0} );

    // connectivity
    for(int k=0; k<Ns; ++k)
        //m.connectivity.push_back( {k+Ns+1, (k+1)%Ns+Ns+1, 2*Ns+1} );
        m.connectivity.push_back( {k+Ns+1, 2*Ns+1,(k+1)%Ns+Ns+1, } );

    m.fill_empty_field();
    return m;
}


mesh create_tree()
{
    float h = 0.7f; // trunk height
    float r = 0.1f; // trunk radius

    // Create a brown trunk
    mesh trunk = create_cylinder_mesh(r, h);
    trunk.color.fill({0.6f, 0.3f, 0.1f});


    // Create a green foliage from 3 cones
    mesh foliage = create_cone_mesh(4*r, 6*r, 0.0f);      // base-cone
    foliage.push_back(create_cone_mesh(4*r, 6*r, 2*r));   // middle-cone
    foliage.push_back(create_cone_mesh(4*r, 6*r, 4*r));   // top-cone
    //foliage.position += vec3(0,0,h);                 // place foliage at the top of the trunk
    foliage.position += vec3(0,h,0);
    foliage.color.fill({0, 0.7f, 0});
       
    // The tree is composed of the trunk and the foliage
    mesh tree = trunk;
    tree.push_back(foliage);

    return tree;
}

mesh create_mushroom()
{
    float h = 0.2f; // trunk height
    float r = 0.05f; // trunk radius

    // Create a brown trunk
    mesh trunk = create_cylinder_mesh(r, h);
    trunk.color.fill({ 0.8f, 0.7f, 0.4f });

    // Create a green foliage from 3 cones
    //mesh hat = create_cone_mesh(2.5f * r, 2 * r, 0.0f);      // base-cone
    mesh hat = create_cone_mesh(2.5f * r, 0.8f*h,2 * r);      // base-cone
    //hat.position += vec3(0, 0, h);                        // place foliage at the top of the trunk
    hat.position += vec3(0, 0.5f*h, 0);                        // place foliage at the top of the trunk
    hat.color.fill({ 1, 0, 0 });

    // The tree is composted of the trunk and the hat
    mesh mushroom = trunk;
    mushroom.push_back(hat);

    return mushroom;
}

mesh create_tree_volcan() // Arbre mort
{
    float h = 1.8f; // trunk height
    float r = 0.1f; // trunk radius

    // Create a brown trunk
    mesh trunk = create_cylinder_mesh(r, h);
    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,1.7f,0},{0,2.2f,0.6f}));
    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,1.7f,0},{0,2.2f,-0.6f}));
    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,1.7f,0},{0.6f,2.2f,0}));
    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,1.7f,0},{-0.6f,2.2f,0}));

    trunk.push_back(mesh_primitive_cylinder(0.03f,{-0.6f,2.2f,0},{-0.9f,2.4f,-0.2f}));
    trunk.push_back(mesh_primitive_cylinder(0.03f,{-0.6f,2.2f,0},{-0.9f,2.4f,0.2f}));

    trunk.push_back(mesh_primitive_cylinder(0.03f,{0.6f,2.2f,0},{0.9f,2.4f,-0.2f}));
    trunk.push_back(mesh_primitive_cylinder(0.03f,{0.6f,2.2f,0},{0.9f,2.4f,0.2f}));

    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,2.2f,-0.6f},{-0.2f,2.4f,-0.8f}));
    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,2.2f,-0.6f},{0.2f,2.4f,-0.8f}));

    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,2.2f,0.6f},{-0.2f,2.4f,0.8f}));
    trunk.push_back(mesh_primitive_cylinder(0.05f,{0,2.2f,0.6f},{0.2f,2.4f, 0.8f}));


    trunk.color.fill({0.3f, 0.15f, 0.05f});



    return trunk;
}


