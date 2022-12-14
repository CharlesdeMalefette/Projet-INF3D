
#include "cgp/cgp.hpp" // Give access to the complete CGP library
#include <iostream>  
#include <vector>

// Custom scene of this code
#include "scene/scene.hpp"

#include "mesh simple/God.hpp"
#include "environment camera/Camera_update.hpp"
#include "gui/display_gui.hpp"



// *************************** //
// Global Variables
// *************************** //

// A helper tool to factorize common default functions (Window initialization, code that starts frame, etc)
cgp::helper_common_scene helper_common;








// The custom structure of the current scene defined in "scene.hpp"
scene_structure scene;

//camera_structure camera;

gui_parameters dis;



// *************************** //
// Start of the program
// *************************** //

GLFWwindow* standard_window_initialization(int width=0, int height=0);

int main(int, char* argv[])
{
	std::cout << "Run " << argv[0] << std::endl;


	// ************************ //
	//     INITIALISATION
	// ************************ //
	
	// Standard Initialization with dimension in pixels
    GLFWwindow* window = standard_window_initialization(640,480);

    scene.environment.resize(scene.N_nombre_monde);


	
	// Custom scene initialization
	std::cout << "Initialize data of the scene ..." << std::endl;

    if(scene.mode_jeu == true) scene.initialize_campagne(); // On commence par la campgane en mode player

    if(scene.mode_jeu == false){ // Mode administrateur
        if(scene.Numero_monde == 1) scene.initialize_campagne();
        if(scene.Numero_monde == 3) scene.initialize_roc();
        if(scene.Numero_monde == 2) scene.initialize_volcan();
        if(scene.Numero_monde == 0) scene.initialize_light();
        if(scene.Numero_monde == 4) scene.initialize_dark();}

    scene.environment[scene.Numero_monde].projection.update_aspect_ratio(float(640)/float(480));

	std::cout << "Initialization success" << std::endl;




	// ************************ //
	//     Animation Loop
	// ************************ //
	std::cout<<"Start animation loop ..."<<std::endl;
	while (!glfwWindowShouldClose(window))
	{
		// Reset the screen for a new frame
        helper_common.frame_begin(scene.environment[0].background_color, window, scene.inputs.window, scene.inputs.mouse.on_gui);
        scene.environment[0].projection.update_aspect_ratio(scene.inputs.window.aspect_ratio());
		


        // Update the camera position at every frame for a fly-mode
        scene.update_camera();


		// Call the display of the scene


        if(scene.Numero_monde == 1) scene.display_campagne();
        if(scene.Numero_monde == 3) scene.display_roc();
        if(scene.Numero_monde == 0) scene.display_light();
        if(scene.Numero_monde == 2) scene.display_volcan();
        if(scene.Numero_monde == 4) scene.display_dark();




		// End of ImGui display and handle GLFW events
		helper_common.frame_end(window);
	}
	
	// Cleanup
	cgp::imgui_cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}



// This function is called everytime the window is resized
void window_size_callback(GLFWwindow* , int width, int height)
{
    scene.inputs.window = { width, height };
    std::cout << width << " " << height << std::endl;
    std::cout << scene.environment[scene.Numero_monde].camera.matrix_frame() << std::endl;
    std::cout << scene.environment[1].camera.matrix_view() << std::endl;
    for(int i=0; i<4;i++)
        scene.environment[i].projection.update_aspect_ratio(float(width)/float(height));
}

// This function is called everytime the mouse is moved

void mouse_move_callback(GLFWwindow*, double xpos, double ypos)
{
	scene.inputs.mouse_position_update( { xpos, ypos } );


    // Apply camera rotation only if shift is not pressed
    //if (!scene.inputs.keyboard.shift)
      //  camera_standard_behavior_rotation(scene.environment.camera, scene.inputs);*/
}

// This function is called everytime a mouse button is clicked/released
void mouse_click_callback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
{
	scene.inputs.mouse.click.update_from_glfw_click(button, action);
}

// This function is called everytime a keyboard touch is pressed/released
void keyboard_callback(GLFWwindow* /*window*/, int key, int , int action, int /*mods*/)
{
	scene.inputs.keyboard.update_from_glfw_key(key, action);
}

// Standard initialization procedure
GLFWwindow* standard_window_initialization(int width_target, int height_target)
{
	// Create the window using GLFW
	GLFWwindow* window = cgp::create_window(width_target, height_target);

	// Update storage for window size for the scene
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);
	scene.inputs.window = { width, height };

	// Display debug information on command line
	std::cout << cgp::opengl_info_display() << std::endl;

	// Initialize ImGUI
	cgp::imgui_init(window);

	// Set the callback functions for the inputs
	glfwSetKeyCallback(window, keyboard_callback);            // Event called when a keyboard touch is pressed/released
	glfwSetMouseButtonCallback(window, mouse_click_callback); // Event called when a button of the mouse is clicked/released
	glfwSetCursorPosCallback(window, mouse_move_callback);    // Event called when the mouse is moved
	glfwSetWindowSizeCallback(window, window_size_callback);  // Event called when the window is rescaled        

	// Load default shader and initialize default frame
	helper_common.initialize();

	return window;
}


