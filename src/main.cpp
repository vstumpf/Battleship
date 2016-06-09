#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>

#include "Camera.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"
#include "Light.h"
#include "Material.h"
#include "Battleship.h"
#include "Object.h"


using namespace std;
using namespace Eigen;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from
string OBJFILE = "";
shared_ptr<Camera> camera;
Program * prog;

vector<Program *> progs;
vector<Material *> mats;
vector<Light *> lights;
vector<Shape *> shapes;
vector<Object *> objs;

Battleship * game;
Square select_sq = { 0, 0 };
Object * select_obj;
int progIndex = 0;
int matIndex = 0;
int lightIndex = 0;


bool keyToggles[256] = {false}; // only for English keyboards!

// This function is called when a GLFW error occurs
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		if (select_sq.y() < 9)
			select_sq.y()++;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if (select_sq.y() > 0)
			select_sq.y()--;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		if (select_sq.x() < 9)
			select_sq.x()++;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		if (select_sq.x() > 0)
			select_sq.x()--;
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		int ret = game->playerGuess(select_sq.x(), select_sq.y());
		if (ret == 2) {
			cout << "ALREADY GUESSED" << endl;
		} else {
			int winner = game->checkWinner();
			if (winner == 0) {
				game->computerGuess();
				if (game->checkWinner() != 0)
					cout << "Computer won!" << endl;
			}
			else if (winner == 1) {
				cout << "Player won!" << endl;
			}
			else if (winner == 2) {
				cout << "Computer won!" << endl;
			}
		}
	}



	/* No materials needed, will be handled in shader
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		if (mods & GLFW_MOD_SHIFT) {
			matIndex--;
			if (matIndex < 0)
				matIndex = MAXMATS - 1;
		}
		else {
			matIndex++;
			if (matIndex >= MAXMATS)
				matIndex = 0;
		}
	}
	*/

	/* only one light for now, no need to select lights
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		if (mods & GLFW_MOD_SHIFT) {
			lightIndex--;
			if (lightIndex < 0)
				lightIndex = MAXLIGHTS - 1;
		}
		else {
			lightIndex++;
			if (lightIndex >= MAXLIGHTS)
				lightIndex = 0;
		}
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		if (mods & GLFW_MOD_SHIFT) {
			lights[lightIndex]->downX();
		}
		else {
			lights[lightIndex]->upX();
		}
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		if (mods & GLFW_MOD_SHIFT) {
			lights[lightIndex]->downY();
		}
		else {
			lights[lightIndex]->upY();
		}
	}
	*/

	/* only one program for now, will add different programs
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (mods & GLFW_MOD_SHIFT) {
			progIndex--;
			if (progIndex < 0)
				progIndex = MAXPROGS - 1;
		}
		else {
			progIndex++;
			if (progIndex >= MAXPROGS)
				progIndex = 0;
		}
	}
	*/
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = (mods & GLFW_MOD_SHIFT) != 0;
		bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
		bool alt   = (mods & GLFW_MOD_ALT) != 0;
		camera->mouseClicked((float)xmouse, (float)ymouse, shift, ctrl, alt);
		
	}
}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		//dont move cahmerah 
		//camera->mouseMoved((float)xmouse, (float)ymouse);
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// This function is called once to initialize the scene and OpenGL
static void init()
{
	// Initialize time.
	glfwSetTime(0.0);
	
	// Set background color.
	glClearColor(1.f, 1.f, 1.f, 1.f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	int i;
	for (i = 0; i < MAXPROGS; i++) {
		prog = new Program();
		if (i == PHONG) {
			prog->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "tile.glsl");
		}
		else if (i == OUTLN) {
			prog->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "outline.glsl");
		}
		prog->setVerbose(true);
		prog->init();
		prog->addAttribute("aPos");
		prog->addAttribute("aNor");
		prog->addAttribute("aTex");
		prog->addUniform("MV");
		prog->addUniform("P");
		prog->addUniform("lightPos");
		prog->addUniform("lightInt");
		prog->addUniform("threshold");
		prog->addUniform("ka");
		prog->addUniform("kd");
		prog->addUniform("ks");
		prog->addUniform("s");
		prog->addUniform("selected");
		progs.push_back(prog);
	}
	for (int i = MAT_MIN; i < MAT_MAX; i++) {
		mats.push_back(new Material(i));
	}

	lights.push_back(new Light(FRONT));

	camera = make_shared<Camera>();
	camera->setInitDistance(2.0f);
	
	for (i = MIN_SHAPE; i < MAX_SHAPE; i++) {
		Shape * shape = new Shape();
		switch (i) {
		case SQUARE:
			OBJFILE = "square.obj";
			break;
		case CUBE:
			OBJFILE = "cube.obj";
			break;
		default:
			throw invalid_argument("bad shape");
			break;
		}
		shape->loadMesh(RESOURCE_DIR + OBJFILE);
		shape->fitToUnitBox();
		shape->init();
		shapes.push_back(shape);
	}
	
	for (i = 0; i < 200; i++) {
		objs.push_back(new Object(shapes[SQUARE]));
	}


	game = new Battleship();
	Object * obj;
	for (i = 0; i < 2; i++) {
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				int index = i * 100 + x * 10 + y;
				obj = objs[index];
				obj->setMTrans(Vector3f(-5 + x * 1.1f, -5 + y * 1.1f, 0));
			}
		}
	}
	select_obj = new Object(shapes[SQUARE]);
	select_obj->setJScale(1.25f);
	select_obj->setMScale(.07f);
	select_obj->setMat(mats[MAT_SELECT]);


	GLSL::checkError(GET_FILE_LINE);
}

// This function is called every frame to draw the scene.
static void render()
{
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'w']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);
	
	// Matrix stacks
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);
	prog = progs[progIndex];
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, P->topMatrix().data());
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV->topMatrix().data());
	glUniform3f(prog->getUniform("lightPos"), lights[FRONT]->getX(), lights[FRONT]->getY(), lights[FRONT]->getZ());
	glUniform1f(prog->getUniform("lightInt"), lights[FRONT]->getIntensity());
	glUniform1f(prog->getUniform("threshold"), THRESHOLD);
	vector<Object *>::iterator it;
	
	Object * obj;

	float xboardiff = .5;
	// draw player board
	MV->pushMatrix();
	MV->translate(-xboardiff, 0, 0);
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			int index = x * 10 + y;

			obj = objs[index];
			obj->setMat(mats[game->getPlayerSquareMat(x, y)]);
			obj->draw(MV.get(), prog);
		}
	}
	MV->popMatrix();
	// end player board 
	
	// draw computer board
	MV->pushMatrix();
	MV->translate(xboardiff, 0, 0);
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			int index = x * 10 + y + 100;
			obj = objs[index];
			if (select_sq.x() == x && select_sq.y() == y)
				obj->setSelected(1);
			else
				obj->setSelected(0);
			obj->setMat(mats[game->getComputerSquareMat(x, y)]);
			obj->draw(MV.get(), prog);
		}
	}
	select_obj->setMTrans(Vector3f(-5 + select_sq.x() * 1.1, -5 + select_sq.y() * 1.1, 0));
	select_obj->draw(MV.get(), prog);
	MV->popMatrix();
	// end computer board

	prog->unbind();
	


	MV->popMatrix();
	P->popMatrix();
	
	GLSL::checkError(GET_FILE_LINE);
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");
	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "Battleship", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	glGetError(); // A bug in glewInit() causes an error that we can safely ignore.
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	GLSL::checkVersion();
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Set char callback.
	glfwSetCharCallback(window, char_callback);
	// Set cursor position callback.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Set mouse button callback.
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Set the window resize call back.
	glfwSetFramebufferSizeCallback(window, resize_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


int main2(int argc, char * argv[]) {
	Battleship * game = new Battleship();
	game->printBoard();
	int x, y;
	cin >> x >> y;
	while (x != 11 && y != 11) {
		game->playerGuess(x, y);
		game->printBoard();
		cin >> x >> y;
	}
	return 0;
}