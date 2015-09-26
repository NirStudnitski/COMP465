# define __Windows__ // define your target operating system
# include "../includes465/include465.hpp" 
# include <fstream>

# include "Ruber.hpp"
#include <GL/glut.h>
#include <stdio.h>

// Shapes
const int nAsteroids = 200;
const int nNonAstObj = 7; // number of non-asteroid objects
const int nModels = nNonAstObj + nAsteroids;

float roll = 0; //left and right keys
float thrust = 0; // 'a' for more thrust, 'z' for less
float pitch = 0; //up and down keys

const int nFacets = 4416;
const int nFacetsWB = 4245;
const int nFacetsMoon = 1104;
const int nFacetsMissile = 252;

const int nFacetsAsteroid = 118;
const int nFacetsAsteroid2 = 82;
const int nFacetsAsteroid3 = 16;
const int nFacetsAsteroid4 = 20;
const int nFacetsAsteroid5 = 20;


int trackShip = 0;




int modelID; // to be used in vertex, shader and and other arrays
/*  0 = ruber
	1 = unum	
	2 = warbird
	3 = duo
	4 = duo moon
	5 = duo moon 2
	6 = missile
	7 = asteroid
	8 = asteroid2
	9 = asteroid3
	10 = asteroid4
	11 = asteroid5
*/

ruber * shape[nModels];
char * speedS = "bla";

// Model for shapes
char * modelFile[] = 
{ 
	"ruber3d.tri", 
	"ruber3d.tri", 
	"warbird.tri", 
	"ruber3d.tri", 
	"moon.tri", 
	"moon.tri", 
	"missile.tri",
	"asteroid.tri",
	"asteroid2.tri",
	"asteroid3.tri",
	"asteroid4.tri",
	"asteroid5.tri"
	
};

// read how many facets in tri file

const GLuint nVertices[] = 
{ 
	nFacets * 3, 
	nFacets * 3, 
	nFacetsWB*3, 
	nFacets * 3, 
	nFacetsMoon * 3, 
	nFacetsMoon * 3, 
	nFacetsMissile * 3,
	nFacetsAsteroid * 3,
	nFacetsAsteroid2 * 3,
	nFacetsAsteroid3 * 3,
	nFacetsAsteroid4 * 3,
	nFacetsAsteroid5 * 3
	
};

// vectors for "model"
glm::vec4 vertex[];
glm::vec3 normal[];
glm::vec4 diffuseColorMaterial[];
 
float boundingRadius[nModels];  
int Index = 0;  // global variable indexing into VBO arrays

				// display state and "state strings" for title display
				// window title strings
char baseStr[100] = "Warbird: Nir and Megan! Press f, t, r for static views, and 1, 2, 3 to follow ship ";
char fpsStr[15], viewStr[15] = " front view";
char titleStr[100];

GLuint vPosition[nModels], vColor[nModels], vNormal[nModels];

GLuint vao[nModels];  // VertexArrayObject
GLuint buffer[nModels];
GLuint shaderProgram[3];
char * vertexShaderFile[3] = { "simpleVertex.glsl", "simpleVertex2.glsl" , "simpleVertex3.glsl" };
char * fragmentShaderFile = "simpleFragment.glsl";
GLuint MVP;  // Model View Projection matrix's handle
glm::mat4 projectionMatrix;     // set in reshape()
glm::mat4 modelMatrix;          // set in shape[i]-->updateDraw()
glm::mat4 viewMatrix;           // set in keyboard()
glm::mat4 ModelViewProjectionMatrix; // set in display();
glm::mat4 behindShipView; // to be used in seeing behind the warbird


									 // vectors and values for lookAt
glm::vec3 eye, at, up;


// rotation variables
glm::mat4 identity(1.0f);
glm::mat4 rotation;
int timerDelay = 40, frameCount = 0;  // A delay of 40 milliseconds is 25 updates / second
double currentTime, lastTime, timeInterval;


void init(void) {
	for (int i = 0; i < 3;i++)  shaderProgram[i] = loadShaders(vertexShaderFile[i], fragmentShaderFile);
	glUseProgram(shaderProgram[0]);

	glGenVertexArrays(nModels, vao);
	//glBindVertexArray(vao);

	// Create and initialize a buffer object
	// GLuint buffer;
	glGenBuffers(nModels, buffer);
	for (int i = 0; i < nModels; i++)
	{
		int shaderID= 0;
		if (i<=5) switch (i)
		{
			case 0: //shader for ruder
				shaderID = 0;
				break;
			case 1: //shader for Unum
				shaderID = 0;
				break;
			case 2: //shader for Warbird
				shaderID = 1;
				break;
			case 3: //shader for Duo
				shaderID = 0;
				break;
			case 4: //shader for Duo's moon
				shaderID = 2;
				break;
			case 5: //shader for Duo's moon
				shaderID = 2;
				break;
			case 6: //shader for missile
				shaderID = 0;
				break; 
			
		}
		
		//assign the correct modelID
		if (i >= nNonAstObj && i < nNonAstObj + nAsteroids) modelID = (i - nNonAstObj) % 5 + nNonAstObj;
		else modelID = i;

		boundingRadius[i] = loadModelBuffer(modelFile[modelID], nVertices[modelID], vao[i], buffer[i], shaderProgram[shaderID],
			vPosition[i], vColor[i], vNormal[i], "vPosition", "vColor", "vNormal");

		if (boundingRadius[i] == -1.0f) {
		//	printf("loadTriModel error:  returned -1.0f \n");
			exit(1);
		}

		else
		{
			//printf("loaded %s model with %7.2f bounding radius \n", modelFile, boundingRadius);
		}
	}
	
	MVP = glGetUniformLocation(shaderProgram[0], "ModelViewProjection");

	// initially use a front view
	eye = glm::vec3(0.0f, 1000.0f, 2000.0f);   // eye is 1000 "out of screen" from origin
	at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
	up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
	viewMatrix = glm::lookAt(eye, at, up);

	// set render state values
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	// create shape
	for (int i = 0; i < nModels; i++) shape[i] = new ruber(i, nAsteroids);
	

	lastTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 1.0f, 10000.0f);
}

// update and display animation state in window title
void updateTitle() {
	strcpy(titleStr, baseStr);
	strcat(titleStr, viewStr);
	strcat(titleStr, fpsStr);
	// printf("title string = %s \n", titleStr);
	glutSetWindowTitle(titleStr);
}

void drawString(void * font, char *s) {
	unsigned int i;
	glColor3f(0.0, 1.0, 0.0);
	


	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);
}







void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	// update model matrix, set MVP, draw
	for (int i = 0; i < nModels; i++) 
	{
		modelMatrix = shape[i]->getModelMatrix(i);
		ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
		
		glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		glBindVertexArray(vao[i]);
		if (i >= nNonAstObj && i < nNonAstObj + nAsteroids) modelID = (i - nNonAstObj) % 5 + nNonAstObj;
		else modelID = i;
		glDrawArrays(GL_TRIANGLES, 0, nVertices[modelID]);
	}
	
	// text on screen - desn't work yet
	/*
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0.0, 800, 0.0, 500);
	
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glRasterPos2i(10, 10);
	drawString(GLUT_BITMAP_9_BY_15, speedS);
	
	

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	*/

	
	glutSwapBuffers();

	frameCount++;
	// see if a second has passed to set estimated fps information
	currentTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
	timeInterval = currentTime - lastTime;
	if (timeInterval >= 1000) {
		sprintf(fpsStr, " fps %4d", (int)(frameCount / (timeInterval / 1000.0f)));
		lastTime = currentTime;
		frameCount = 0;
		updateTitle();
	}
}

// Animate scene objects by updating their transformation matrices
// timerDelay = 40, or 25 updates / second
void update(int i) {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(timerDelay, update, 1);
	 for (int i = 0; i < nModels; i++) shape[i]->update(i, currentTime, nAsteroids, roll, thrust, pitch);
	
	 //die-down of roll and pitch
	 if (pitch < 0) pitch += 0.001; //
	 else if (pitch > 0) pitch -= 0.001; //
	 if (roll < 0) roll += 0.001; //
	 else if (roll > 0)roll -= 0.001; //
	
	 // camera tracks ship:
	 if (trackShip!=0)
		 switch(trackShip)
	 {
		 case 1:
		 

			 behindShipView = shape[2]->getModelMatrix(2);

			 eye = glm::vec3(behindShipView[3][0], behindShipView[3][1] + 200, behindShipView[3][2] + 500);
			 at = glm::vec3(behindShipView[3][0], behindShipView[3][1], behindShipView[3][2]);
			 up = glm::vec3(behindShipView[1][0], behindShipView[1][1], behindShipView[1][2]);
			 strcpy(viewStr, " Ship View");
			 viewMatrix = glm::lookAt(eye, at, up);
		  break;
	case 2: //behind ship view
	 


		 behindShipView = shape[2]->getModelMatrix(2);

		 eye = glm::vec3(behindShipView[3][0] - behindShipView[2][0] * 10, behindShipView[3][1] - behindShipView[2][1] * 10, behindShipView[3][2] - behindShipView[2][2] * 10);
		 at = glm::vec3(behindShipView[3][0], behindShipView[3][1], behindShipView[3][2]);
		 up = glm::vec3(behindShipView[1][0], behindShipView[1][1], behindShipView[1][2]);
		 strcpy(viewStr, " behind Ship View");
		 viewMatrix = glm::lookAt(eye, at, up);
	 break;
	case 3: //cokpit view
	


		behindShipView = shape[2]->getModelMatrix(2);

		eye = glm::vec3(behindShipView[3][0] + behindShipView[2][0] * 3, behindShipView[3][1] + behindShipView[2][1] * 3, behindShipView[3][2] + behindShipView[2][2] * 3);
		at = glm::vec3(behindShipView[3][0] + behindShipView[2][0] * 4, behindShipView[3][1] + behindShipView[2][1] * 4, behindShipView[3][2] + behindShipView[2][2] * 4);
		up = glm::vec3(behindShipView[1][0], behindShipView[1][1], behindShipView[1][2]);
		strcpy(viewStr, " cockpit View");
		viewMatrix = glm::lookAt(eye, at, up);
	 break;
}
	
}

// Quit or set the view
void keyboard(unsigned char key, int x, int y) {
	
	switch (key) {
	case 033: case 'q':  case 'Q': exit(EXIT_SUCCESS); break;
	case 'f': case 'F':  // front view
		trackShip = 0;
		eye = glm::vec3(0.0f, 500.0f, 2000.0f);   // eye is 2000 "out of screen" from origin
		at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
		up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
		strcpy(viewStr, " front view"); break;
	case 'r': case 'R':
		trackShip = 0;
		eye = glm::vec3(1000.0f, 250.0f, 0.0f);   // eye is 1000 right from origin
		at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
		up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
		strcpy(viewStr, " right view"); break;
	case 't': case 'T':  // top view
		trackShip = 0;
		eye = glm::vec3(0.0f, 3000.0f, 0.0f);   // eye is 3000 up from origin
		at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin  
		up = glm::vec3(0.0f, 0.0f, -1.0f);   // camera's up is looking towards -Z vector
		strcpy(viewStr, " top view"); break;
	case '1':   // follow ship view
		trackShip = 1;
		 break;
	case '2':   // follow ship behind view
		trackShip = 2;
		break;

	case '3':   // cockpit view
		trackShip = 3;
		break;


	case 'a': case 'A':  
		thrust+= 1.0f;
		 break;
	case 'z': case 'Z':
		thrust -= 1.0f;
		break;
	
	}
		viewMatrix = glm::lookAt(eye, at, up);
		updateTitle();
	
}
void specialKey(int key, int x, int y) {
	switch (key)
	{

	case GLUT_KEY_RIGHT:  
			roll-=0.01f;
			break;
	case GLUT_KEY_LEFT: 
		roll+=0.01F;
		break;
	case GLUT_KEY_UP: 
		pitch -= 0.01f;
		break;
	case GLUT_KEY_DOWN: 
		pitch += 0.01f;
		break;
	}
	
	
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1200, 600);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Warbird: Nir and Megan! Press {f, t, r} : front view");
	// initialize and verify glew
	glewExperimental = GL_TRUE;  // needed my home system 
	GLenum err = glewInit();
	if (GLEW_OK != err)
		printf("GLEW Error: %s \n", glewGetErrorString(err));
	else {
		printf("Using GLEW %s \n", glewGetString(GLEW_VERSION));
		printf("OpenGL %s, GLSL %s\n",
			glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
	// initialize scene
	init();
	// set glut callback functions
	glutSpecialFunc(specialKey);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(timerDelay, update, 1);
	glutIdleFunc(display);
	glutMainLoop();
	printf("done\n");
	return 0;
}


