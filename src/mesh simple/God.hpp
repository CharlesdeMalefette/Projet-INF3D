
#pragma once

#include "cgp/cgp.hpp"
// The structure of the custom scene


// God signifie tout objet vivant étant amené à se déplacer dans la scène, initialement, ca devait être des sortes de dieux d'où le nom god
// Finalement, il ne s'agira que d'oiseaux

struct god_structure{

    // The entire hierarchy
    cgp::hierarchy_mesh_drawable hierarchy;
    std::vector<cgp::hierarchy_mesh_drawable> hierarchy_birds;

    int N_birds=23; // Monde campagne
    int N_vautour = 23; // Monde roc
    int N_corbeau = 23; // Monde volcan

    // ****************************** //
    // Functions
    // ****************************** //

    void bird_initialize();
    void vautour_initialize();
    void corbeau_initialize();
};
