
#include "cgp/cgp.hpp"
#include "gui/display_gui.hpp"
#include "environment camera/environment_camera_head.hpp"


// Structure de notre scène principale qui servira pour les cinq mondes

struct scene_structure {


    // ****************************** //
    // Elements de la scène
    // ****************************** //

    // Réglage des paramètres à faire varier pour passer du mode admin au mode player //

    bool mode_jeu = false; // True si mode joueur, false si mode administrateur

    int Numero_monde = 0; // Dans la version joueur, vaut 1 pour débuter de la campagne
                          // Dans la version administrateur, à faire varier pour régler le monde désiré

    float speed = 35 ;   // The velocity of the camera displacement


    // Constante //

        int N_nombre_monde = 5;

        float terrain_length_x = 40;
        float terrain_length_y = 30;
        int N_terrain=15;

        int N_obstacle_cylindre=15;
        int N_obstacle_cylindre_light=35;
        int N_obstacle_cylindre_horiz_light = 35;
        int N_obstacle_tore = 15;
        int N_obstacle_cylindre_volcan = 60;

        int N_barreau = int(terrain_length_x);
        int N_barriere = int(terrain_length_x/2);
        int N_haie = int(terrain_length_x/2);

        float sphere_radius = 0.2f; // Rayon de la sphère qui se déplace

        int N_meteorite = 40;



        // Vecteur //

        cgp::vec3 transl = {-terrain_length_x,5.0f,0}; // Vecteur permettant de passer d'un terrain au suivant, utile pour placer les mesh sur chaque terrain
        cgp::vec3 transl_birds = {-terrain_length_x,3.0f,0}; // Pour positionner les oiseaux
        cgp::vec3 offset_y = {0,2.0f,0};
        cgp::vec3 g   = {0,-9.81f,0}; // Gravity




    // Global setting //

        std::vector<scene_environment_camera_head> environment; // Un environnement par monde
        cgp::skybox_drawable skybox; // Une skybox par monde, on utilisera cependant le même objet
        cgp::mesh_drawable global_frame;          // The standard global frame
        cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
        cgp::timer_basic timer; // Timer used for the animation



    // Mesh //


    std::vector<cgp::mesh_drawable> terrain;
    cgp::mesh_drawable terrain_vert;

    // Mesh (et autres) qui interagissent avec la sphere

    cgp::mesh_drawable sphere;

    cgp::mesh_drawable pepite; // Objet à récolter
    std::vector<bool> check_pepite; //Booléen qui check si la sphère a déja ramassé une pépite
    std::vector<cgp::mesh_drawable> mesh_score; // Score qui s'incrémente

    std::vector<cgp::mesh_drawable> obstacle_cylindre; // A éviter
    std::vector<cgp::mesh_drawable> obstacle_cylindre_horiz; // A éviter
    std::vector<cgp::mesh_drawable> obstacle_tore; // A éviter
    cgp::mesh_drawable rocher_tombant; // A éviter
    cgp::mesh_drawable meteorite;  // A éviter

    bool contact_obstacle = false; // Booléen qui devient true si la sphère heurte un objet et donc arrête le jeu


    // Mesh qui décorent

    cgp::mesh_drawable tree;
    cgp::mesh_drawable cactus;
    cgp::mesh_drawable mushroom;
    cgp::mesh_drawable rocher;
    cgp::mesh_drawable telegraphe;
    cgp::mesh_drawable dragon;

    cgp::mesh_drawable billboard;
    cgp::mesh_drawable billboard_rengoku;


    cgp::mesh_drawable planet;
    cgp::mesh_drawable anneau;


    std::vector<cgp::mesh_drawable> gate_right;
    std::vector<cgp::mesh_drawable> gate_left;

    // Vecteur de position des mesh //

    std::vector<cgp::vec3> gate_position_right;
    std::vector<cgp::vec3> gate_position_left;
    std::vector<cgp::vec3> tree_position;
    std::vector<cgp::vec3> cactus_position;
    std::vector<cgp::vec3> rocher_position;
    std::vector<cgp::vec3> mushroom_position;
    std::vector<cgp::vec3> billboard_position;
    std::vector<float> position_tore;
    std::vector<float> z_oiseaux; // Décalage sur z de oiseaux
    std::vector<float> z_rocher; // Décalage sur z des rochers



    // Affichage des résultats finaux //

    bool perfect_campagne = false; // Variable qui vaut true si campagne est finit à 100%
    bool perfect_roc = false;
    bool perfect_light = false;
    bool perfect_volcan = false;

    cgp::mesh_drawable parfait; // image à afficher si victoire 100%
    cgp::mesh_drawable crl; // image si victoire partielle (campagne,roc,light)
    cgp::mesh_drawable crv;
    cgp::mesh_drawable clv;
    cgp::mesh_drawable rlv;
    cgp::mesh_drawable cr;  // etc..
    cgp::mesh_drawable cl;
    cgp::mesh_drawable cv;
    cgp::mesh_drawable rl;
    cgp::mesh_drawable rv; // image si victoire partielle (roc,volcan)
    cgp::mesh_drawable lv;
    cgp::mesh_drawable c;
    cgp::mesh_drawable r;
    cgp::mesh_drawable l;   // etc..
    cgp::mesh_drawable v;
    cgp::mesh_drawable neant;   // image si défaite totale




    // ****************************** //
    // Functions
    // ****************************** //


    void update_camera(); // Fait bouger la caméra quand une touche du clavier est activée

    // Fonction d'affichage //


    void load_preparation_finale();

    int bijection();




    // Fonction du monde 1 : Campagne //
    void initialize_campagne();
    void display_campagne();
    void display_trees_campagne();
    void display_billboard_campagne();
    void display_mushroom_campagne();
    void display_gate_left_campagne();
    void display_gate_right_campagne();
    void display_sphere_campagne();
    void display_obstacle_campagne();
    void display_resultat_campagne();
    void display_billboard_rengoku_campagne();
    void load_score_campagne();
    void display_terrain_campagne();
    void display_bird_campagne();


    // Fonction du monde 2 : Roc //
    void initialize_roc();
    void display_roc();
    void display_billboard_rengoku_roc();
    void display_obstacle_roc();
    void display_gate_left_roc();
    void display_gate_right_roc();
    void display_cactus_roc();
    void display_rocher_roc();
    void display_barriere_left_roc();
    void display_barriere_right_roc();
    void display_sphere_roc();
    void display_resultat_roc();
    void load_score_roc();
    void display_vautour_roc();
    void display_terrain_roc();
    void display_telegraphe_roc();

    // Fonctions du monde 3 : Volcan //
    void initialize_volcan();
    void display_volcan();
    void display_billboard_volcan();
    void display_gate_left_volcan();
    void display_gate_right_volcan();
    void display_trees_volcan();
    void display_astres_volcan();
    void display_obstacle_volcan();
    void display_sphere_volcan();
    void display_dragon_volcan();
    void display_resultat_volcan();
    void display_terrain_volcan();
    void load_score_volcan();
    void display_billboard_ace_volcan();
    void display_corbeau_volcan();
    void display_rocher_volcan();
    void display_rocher_tombant_volcan();

    // Fonctions du monde 4 : Light //
    void initialize_light();
    void display_light();
    void display_billboard_kizaru_light();
    void display_obstacle_light();
    void display_sphere_light();
    void display_resultat_light();
    void load_score_light();
    void display_terrain_light();
    void display_gate_right_light();
    void display_gate_left_light();
    void color_gate_light();
    void color_obstacle_horiz_light();
    void color_obstacle_vert_light();
    void color_obstacle_tore_light();
    void initialize_obstacle_light();


    // Fonctions du monde 5 : Dark //
    void initialize_dark();
    void display_dark();



};

