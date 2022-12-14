#include "gui/display_gui.hpp"
#include "scene/scene.hpp"



void gui_parameters::display_gui()
{
    ImGui::Checkbox("Frame", &display_frame);
    ImGui::Checkbox("Wireframe", &display_wireframe);

    ImGui::Checkbox("terrain", &display_terrain);
    ImGui::Checkbox("tree", &display_tree);
    ImGui::Checkbox("mushroom", &display_mushroom);
    ImGui::Checkbox("billboard", &display_billboard);
    ImGui::Checkbox("gate_right", &display_gate_right);
    ImGui::Checkbox("gate_left", &display_gate_left);
    ImGui::Checkbox("god", &display_god);
    //ImGui::SliderFloat("Speed", &speed, 0.2f, 60.0f); // Set the camera velocity


}

