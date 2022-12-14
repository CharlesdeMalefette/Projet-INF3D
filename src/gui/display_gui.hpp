#pragma once

#include "cgp/cgp.hpp"



// The element of the GUI that are not already stored in other structures
struct gui_parameters {
public:
    bool display_frame      = true;
    bool display_wireframe  = false;
    bool display_terrain   = true;
    bool display_tree      = true;
    bool display_mushroom  = true;
    bool display_billboard = true;
    bool display_gate_right = true;
    bool display_gate_left = true;
    bool display_god = true;




                      // Standard GUI element storage
void display_gui(); // The display of the GUI, also called within the animation loop

};


