#include "interface.hpp"
#include <experimental/coroutine>

GameManager Game;

//std::vector<std::map<const char*, Object*>> objects;
std::map<const char*, Image*> images;
//std::map<const char*, Audio*> sounds;
KeyState KeyStates[256];
//Level level;

#define DEBUG 1
#define VERSION 1
#define NAME "The Phoenix of Ise"
using std::make_pair;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void callback_resize(
    [[maybe_unused]] GLFWwindow* window,
    int width, int height)
{
  glViewport(0, 0, width, height);
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

GLFWwindow* GameManager::SetupWindow()
{
    if (!glfwInit())
        return NULL;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Without these two hints, nothing above OpenGL version 2.1 is supported
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    printf("Creating window ...\n");
    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window!\n");
//      std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return window;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, callback_resize);
    glfwMakeContextCurrent(window);
//    glfwSetKeyCallback(window, callback_key);
    
    //printf("Setting draw methods...\n");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    //printf("Resizing display...\n");
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    images.emplace("player", new Image("Resources/Images/Player.png"));
//    images.emplace("textwindow", new Image("Resources\\Images\\Window.png"));
//    images.emplace("background1", new Image("Resources\\Images\\TitleBG.png"));
//    images.emplace("tileset", new Image("Resources\\Images\\Tileset.png"));

//    alutInit(0, NULL);
//    sounds.emplace("sample", new Audio("Resources\\walk.wav"));
    
    printf("Loading GameObject functions...\n");
//    glutIdleFunc(Game.Main);
//    glutDisplayFunc(Game.Redraw);
//    glutTimerFunc(1, Game.Update, 0);
//
//    glutKeyboardFunc(Game.CharacterPress);
//    glutKeyboardUpFunc(Game.CharacterRelease);
//    glutSpecialFunc(Game.SymbolPress);
//    glutSpecialUpFunc(Game.SymbolRelease);
//
//    glutMouseFunc(Game.MouseCall);
//    glutMotionFunc(Game.UpdateMousePos);
//    glutPassiveMotionFunc(Game.UpdateMousePos);
    newFrame = true;

//    objects.resize(MAX_LAYERS);
//    AddObject(2, "player", new Player(416, 320, 0, -32,
//        make_pair("face_down", new Sprite(32, 64, 0, 0, 1, 0, images.at("player"))),
//        make_pair("face_left", new Sprite(32, 64, 64, 0, 1, 0, images.at("player"))),
//        make_pair("face_up", new Sprite(32, 64, 128, 0, 1, 0, images.at("player"))),
//        make_pair("face_right", new Sprite(32, 64, 192, 0, 1, 0, images.at("player"))),
//        make_pair("move_down", new Sprite(32, 64, 0, 64, 4, 100, images.at("player"))),
//        make_pair("move_left", new Sprite(32, 64, 64, 64, 4, 100, images.at("player"))),
//        make_pair("move_up", new Sprite(32, 64, 128, 64, 4, 100, images.at("player"))),
//        make_pair("move_right", new Sprite(32, 64, 192, 64, 4, 100, images.at("player"))),
//        make_pair("", nullptr)
//        ));
//
//    AddObject(BG_LAYER, "background", new Object(480, 260, make_pair("background1", new Sprite(960, 512, 0, 0, 1, 0, images.at("background1"))),
//        make_pair("", nullptr)));
//
//    AddObject(UI_LAYER, "startmenu", new Menu(30, 30, 200, 200, 5, 16, "Resources\\Fonts\\Test2.ttf", make_pair("window", new Sprite(763, 146, 0, 0, 1, 0, images.at("textwindow"))), "New Game", "Load", "Delete", "Options", "Exit"));
    
//    auto ngame = []() {
//        Game.state.Change("map", NULL);
//        printf("New game\n");
//    };
//
//    auto lgame = []() {
//        Game.state.Change("dialogue", NULL);
//        printf("Showing a thing\n");
//
//        AddObject(UI_LAYER, "dialogue", new Dialogue(30, 300, 700, 200, 3, 24, "Resources\\Fonts\\Test2.ttf", make_pair("window", new Sprite(763, 146, 0, 0, 1, 0, images.at("textwindow"))),
//            "You have clicked LOAD", "This is currently unavailable.\nSorry!!", "Now back to Menu"));
//
//        auto menu = []() {
//            Game.state.Change("menu", NULL);
//            printf("Back to Menu\n");
//        };
//
//        objects[UI_LAYER].at("dialogue")->AddActions({ menu });
//    };
//    printf("point value: %p\n", lgame);
//    objects[UI_LAYER].at("startmenu")->AddActions({ ngame, lgame });
//    printf("SIZE: %d\n", objects[UI_LAYER].at("startmenu")->actions.size());

//    init_resources();
//    level.LoadLevel("Resources\\Maps\\map1-0.txt", images.at("tileset"), 0);
//    level.LoadLevel("Resources\\Maps\\map1-1.txt", images.at("tileset"), 1);
//    level.LoadLevel("Resources\\Maps\\map1-2.txt", images.at("tileset"), 2);
//    level.LoadCollision("Resources\\Maps\\map1-c.txt");
    printf("Setup complete, proceeding to main loop\n\n");

//    state.Add("menu", new EmptyState());
//    state.Add("map", new EmptyState());
//    state.Add("dialogue", new EmptyState());
//    state.Change("menu", NULL);

//    glutMainLoop();
    
    return window;
}

void key_callback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
    switch(action) {
        case GLFW_PRESS:
            break;
    }
}


//void AddObject(int Layer, const char* name, Object* Thing)
//{
//    if (Layer > UI_LAYER) Layer = UI_LAYER;
//    if (Layer < BG_LAYER) Layer = BG_LAYER;
//    objects[Layer][name] = Thing;
//}
