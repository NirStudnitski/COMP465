/* 
Warbird Simulation - Phase 2+3

Comp 465

Team Members:
Nir Studnitski
Megan Kim
*/

# define __Windows__ // define your target operating system
# include "../includes465/include465.hpp"  
# include <fstream>

# include "Ruber.hpp"
# include <GL/glut.h>
# include <stdio.h>
#include "mesh.hpp"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

// Shapes
const int nAsteroids = 200;
const int nNonAstObj = 8; // number of non-asteroid objects
const int numSphere = 5; //number of planets and moons
const int numOBJ = 24; // number of OBJ meshes
const int nModels = nNonAstObj + nAsteroids + numOBJ;

float roll = 0; //left and right keys
float thrust = 0; // 'a' for more thrust, 'z' for less
float pitch = -0.025f; //up and down keys

const int nFacets = 4416;
const int nFacetsWB = 17022;
const int nFacetsMoon = 1104;
const int nFacetsMissile = 252;
const int nFacetsMissileSite = 54;

const int nFacetsAsteroid = 118;
const int nFacetsAsteroid2 = 82;
const int nFacetsAsteroid3 = 32;
const int nFacetsAsteroid4 = 20;
const int nFacetsAsteroid5 = 20;

float lightMitigator = 0.4f;

int trackShip = 6;
float healthValue = 5.0f;

int modelID; // to be used in vertex, shader and and other arrays
/*  0 = ruber
	1 = unum	
	2 = warbird
	3 = duo
	4 = duo moon
	5 = duo moon 2
	6 = missile
	7 = missile site
	8 = asteroid
	9 = asteroid2
	10 = asteroid3
	11 = asteroid4
	12 = asteroid5
*/


ruber * shape[nModels];

Mesh * mesh;
Shader * shader;
Texture * texture;

Mesh * meshRuber;
Shader * shaderRuber;
Texture * textureRuber;

Mesh * meshUnum;
Shader * shaderUnum;
Texture * textureUnum;

Mesh * meshDuo;
Shader * shaderDuo;
Texture * textureDuo;

//texture meshes
Mesh * textGrav, *textVel, *textMiss, *textOn, *textOff, *health, *healthBar, *speedBar;
Shader * shaderGrav, *shaderVel, *shaderMiss, *shaderOn, *shaderOff, *shaderHealth, *shaderHealthBar, *shaderSpeedBar;

Mesh *lllMesh[10];
Shader *lllShader[10];

Mesh *laser;
Shader *laserShader;
Texture * textureLaser;


Camera * camera;
Transform * transform;

bool armDeathStar = true; //when this is armed, death star will fire when facing the WB
bool deathStarDestroyed = false;
bool invincableMode = false;
glm::vec3 unumToWB, unumHoleLocation, tempVec;
float timeOfLastLaser = 0;

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
	"missileSite.tri",
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
	nFacetsWB * 3,
	nFacets * 3,
	nFacetsMoon * 3,
	nFacetsMoon * 3,
	nFacetsMissile * 3,
	nFacetsMissileSite * 3,
	nFacetsAsteroid * 3,
	nFacetsAsteroid2 * 3,
	nFacetsAsteroid3 * 3,
	nFacetsAsteroid4 * 3,
	nFacetsAsteroid5 * 3
	
};

float radius[nNonAstObj] =
{
	200.0f, //ruber
	20.0f, //unum
	40.0f, //duo
	10.0f, //primus
	15.0f, //secundus
	10.0f, //warbird
	25.0f, //missile
	3.0f //missile site
};

// vectors for "model"
glm::vec4 vertex[];
glm::vec3 normal[];
glm::vec4 diffuseColorMaterial[];
 

//locations informations send to update
glm::mat4 warBTrans = glm::mat4();
glm::mat4 missileSiteTrans = glm::mat4();
glm::mat4 unumTrans = glm::mat4(), duoTrans;
bool planetGravity = false;

float boundingRadius[nModels];  
int Index = 0;  // global variable indexing into VBO arrays

				// display state and "state strings" for title display
				// window title strings
char baseStr[100] = "Warbird: Nir and Megan! ";
char fpsStr[15], upsStr[15], viewStr[30];
char titleStr[100];

char warp = 'z';

GLuint vPosition[nModels], vColor[nModels], vNormal[nModels];

GLuint vao[nModels];  // VertexArrayObject
GLuint buffer[nModels+3*numOBJ];
GLuint shaderProgram[1];
char * vertexShaderFile[1] = { "simpleVertex.glsl" };
char * fragmentShaderFile[1] = {"simpleFragment.glsl" };
GLuint MVP;  // Model View Projection matrix's handle
GLuint ROT;  // rotation matrix's handle
GLuint TOT;  // tanslationMatrix2's handle
glm::mat4 projectionMatrix;     // set in reshape()
glm::mat4 modelMatrix;          // set in shape[i]-->updateDraw()
glm::mat4 viewMatrix;           // set in keyboard()
glm::mat4 ModelViewProjectionMatrix; // set in display();
glm::mat4 behindShipView; // to be used in seeing behind the warbird

//uniform variables to be passed to shader
glm::mat4 rotationMatrix2;
glm::mat4 translationMatrix2;
int windowWidth = 1600;
int windowHeight = 800;
//two suns: ruber and duo******************************************

//ruber is made up of 7 light points inside its sphere
glm::vec3 ruberPos = 	glm::vec3(0.0f, 0.0f, 0.0f); //position
GLuint PR;  //handle


glm::mat4 duoModelMat;
GLuint PD;  //handle


glm::vec4 ruberLightColor = glm::vec4(0.6f,0.7f,1.0f,1.0f);
GLuint CR;  //handle


glm::vec4 duoLightColor = glm::vec4(1.0f, 0.2f, 0.3f, 1.0f);
GLuint CD;  //handle


//distance to each sun - for intensity calculations
float distanceToR;
float distanceToD;

//fractional intensity of each sun
float intensityR;
GLuint intensR;


float intensityD;
GLuint intensD;


// normalized pointers to the suns' direction
glm::vec3 R;
GLuint dirR;


glm::vec3 posD;
GLuint dirD;


// normalized pointers to the camera's direction
glm::vec3 viewVec;
GLuint VV;


//*******************************************************


									 // vectors and values for lookAt
glm::vec3 eye, at, up;
GLuint shaderID=0;
GLuint shaderHandle;

// rotation variables
glm::mat4 identity(1.0f);
glm::mat4 rotation;

int timerDelay[4] = { 40, 100, 250, 500 }, frameCount = 0;  // A delay of 40 milliseconds is 25 updates / second
int timeQ = 0;
double currentTime, lastTime, timeInterval;
float timeOfShot = -1.0f;
int missilesFired = 1;


void init(void) {
	

	
	shaderProgram[0] = loadShaders(vertexShaderFile[0], fragmentShaderFile[0]);
	
	
	glGenVertexArrays(nModels-numOBJ, vao);
	
	glGenBuffers(nModels-numOBJ, buffer);

	for (int i = 0; i < nModels-numOBJ; i++)
	{
		
		
		//assign the correct modelID
		if (i >= nNonAstObj && i < nNonAstObj + nAsteroids) modelID = (i - nNonAstObj) % 5 + nNonAstObj;
		else modelID = i;
		
		 if (modelID != 0 && modelID !=3 && modelID != 1) boundingRadius[i] = loadModelBuffer(modelFile[modelID], nVertices[modelID], vao[i], buffer[i], shaderProgram[shaderID],
			vPosition[i], vColor[i], vNormal[i], "vPosition", "vColor", "vNormal");
		
		
		
		if (boundingRadius[i] == -1.0f)  exit(1);
		
	}
	
	MVP = glGetUniformLocation(shaderProgram[0], "ModelViewProjection");
	ROT = glGetUniformLocation(shaderProgram[0], "rotation");
	TOT = glGetUniformLocation(shaderProgram[0], "translation");

	//ruber's seven light points
	PR = glGetUniformLocation(shaderProgram[0], "posR");
	

	PD = glGetUniformLocation(shaderProgram[0], "transD");

	CR = glGetUniformLocation(shaderProgram[0], "colR");
	shaderHandle = glGetUniformLocation(shaderProgram[0], "shaderNumber");
	CD = glGetUniformLocation(shaderProgram[0], "colD");
	
	

	//these distances will passes squared( raisedto the power of 2)
	intensD = glGetUniformLocation(shaderProgram[0], "intensityD");
	intensR = glGetUniformLocation(shaderProgram[0], "intensityR");
	
	dirR = glGetUniformLocation(shaderProgram[0], "R");
	dirD = glGetUniformLocation(shaderProgram[0], "posD");
	VV = glGetUniformLocation(shaderProgram[0], "view");

	


	
	

	// set render state values
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	printf("number of models = %i", nModels);
	// create shape
	for (int i = 0; i < nModels; i++) {
		shape[i] = new ruber(i, nAsteroids);
		//shape[i]->setSize(radius[i], boundingRadius[i]);
	}
	mesh = new Mesh("./sphere.obj", vao, buffer, nModels-numOBJ,0, false);
	shader = new Shader("./basicShader");
	texture = new Texture("./ruberText2.jpg");

	meshRuber = new Mesh("./sphere.obj", vao, buffer, nModels-numOBJ,1, false);
	shaderRuber = new Shader("./basicShader");
	textureRuber = new Texture("./starFieldC.jpg");

	meshUnum = new Mesh("./deathS.obj", vao, buffer, nModels-numOBJ, 2, false);
	shaderUnum = new Shader("./basicShaderUnum");
	textureUnum = new Texture("./unum.jpg");

	meshDuo = new Mesh("./sphere.obj", vao, buffer, nModels-numOBJ, 3, false);
	shaderDuo = new Shader("./basicShader");
	textureDuo = new Texture("./duo.jpg");

	textGrav = new Mesh("./gravity.obj", vao, buffer, nModels-numOBJ, 4, true);
	shaderGrav = new Shader("./basicShaderText");

	textVel = new Mesh("./velocity.obj", vao, buffer, nModels - numOBJ, 5, true);
	shaderVel = new Shader("./basicShaderText");

	textMiss = new Mesh("./missiles.obj", vao, buffer, nModels - numOBJ, 6, true);
	shaderMiss = new Shader("./basicShaderText");

	textOn = new Mesh("./on.obj", vao, buffer, nModels - numOBJ, 7, true);
	shaderOn = new Shader("./basicShaderText");

	textOff = new Mesh("./off.obj", vao, buffer, nModels - numOBJ, 8, true);
	shaderOff = new Shader("./basicShaderText");

	health = new Mesh("./health.obj", vao, buffer, nModels - numOBJ, 20, true);
	shaderHealth = new Shader("./basicShaderText");

	healthBar = new Mesh("./healthBar.obj", vao, buffer, nModels - numOBJ, 21, true);
	shaderHealthBar = new Shader("./basicShaderText");

	speedBar = new Mesh("./healthBar.obj", vao, buffer, nModels - numOBJ, 22, true);
	shaderSpeedBar = new Shader("./basicShaderText");

	laser = new Mesh("./stars.obj", vao, buffer, nModels - numOBJ, 19, false);
	laserShader = new Shader("./basicShader");
	textureLaser = new Texture("./laser.jpg");

	for (int i = 0; i < 10; i++)
	{
		lllMesh[i] = new Mesh("./lll.obj", vao, buffer, nModels - numOBJ, 9+i, true);
		lllShader[i] = new Shader("./basicShaderText");
	}
	


	Transform transform;
	Camera camera(eye, glm::radians(45.0f), (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0f, 10000.0f);
	
	
	lastTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)w / (GLfloat)h, 1.0f, 10000.0f);
	
}

void drawString(void * font, char *s) {
	unsigned int i;
	glColor3f(0.0, 1.0, 0.0);
	


	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, (int) s[i]);
}

bool checkForCollision = true;
void checkCollision() {
	float objDistance; //used to find distance between objects
	
	glm::vec3 objPos = getPosition(shape[2]->getOrientationMatrix()); //finding pos of warbird
	if (shape[2] && checkForCollision && !invincableMode) {
		for (int i = 0; i < nNonAstObj; i++) { //checking for collision on all planets and moons
			if (i != 2 && i!=6) {
				objDistance = distance(objPos, getPosition(shape[i]->getOrientationMatrix()));
				if (objDistance < (radius[i] + radius[5] + 100)) {
					checkForCollision = false;
					//showVec3("ship", objPos);
					//showVec3("other", getPosition(shape[i]->getOrientationMatrix()));
					//printf(" %f", objDistance);
					printf("You Died");
					healthValue = 0.0f;
				}
			}
		}
	}
}

void checkMissileCollision() {
	float objDistance; //used to find distance between objects

	glm::vec3 objPos = getPosition(shape[6]->getOrientationMatrix()); //finding pos of warbird
	
		for (int i = 0; i < nNonAstObj; i++) 
		{ //checking for collision on all planets and moons
			if (i == 7)
			{
				objDistance = distance(objPos, getPosition(shape[i]->getOrientationMatrix()));
				if (objDistance < 40)
				{
					deathStarDestroyed = true;
					timeOfShot = -1.0f;
				}
			}
			else if (i != 2 && i!=6) 
			{
				objDistance = distance(objPos, getPosition(shape[i]->getOrientationMatrix()));
				if (objDistance < 10)
					timeOfShot = -1.0f;
			}
				
			
		}
		
	
}

void checkLaserCollision() 
{
	float objDistance; //used to find distance between objects

	glm::vec3 objPos = getPosition(shape[227]->getOrientationMatrix()); //finding pos of warbird
	objDistance = distance(objPos, getPosition(shape[2]->getOrientationMatrix()));
	if (objDistance < 40) healthValue -= 0.2f;
		
}


void updateTitle() {
	strcpy(titleStr, baseStr);
	strcat(titleStr, viewStr);
	strcat(titleStr, fpsStr);
	// printf("title string = %s \n", titleStr);
	glutSetWindowTitle(titleStr);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// update model matrix, set MVP, draw
	for (int ia = 0; ia < nModels - numOBJ; ia++)
	{
		if (ia >= nNonAstObj && ia < nNonAstObj + nAsteroids)
		{
			glUseProgram(shaderProgram[0]); //3
			modelMatrix = shape[ia]->getModelMatrix(ia);
			ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
			rotationMatrix2 = shape[ia]->getTranslationMatrix(ia);
			translationMatrix2 = shape[ia]->getTranslationMatrix(ia);
			duoModelMat = shape[3]->getModelMatrix(3);

			//distances to each sun (already squared)
			distanceToR = translationMatrix2[3][0] * translationMatrix2[3][0] +
				translationMatrix2[3][1] * translationMatrix2[3][1] +
				translationMatrix2[3][2] * translationMatrix2[3][2];
			distanceToR *= lightMitigator; //give ruber more intensity

			distanceToD = (translationMatrix2[3][0] - duoModelMat[3][0])*(translationMatrix2[3][0] - duoModelMat[3][0]) +
				(translationMatrix2[3][1] - duoModelMat[3][1])*(translationMatrix2[3][1] - duoModelMat[3][1]) +
				(translationMatrix2[3][2] - duoModelMat[3][2])*(translationMatrix2[3][2] - duoModelMat[3][2]);


			// light intensity is proportional to the inverse sqare of distance
			intensityR = (float)1 / distanceToR;
			intensityD = (float)1 / distanceToD;

			//fractional intensity
			float sum = (intensityR + intensityD) / 3;

			intensityR = intensityR / sum;
			intensityD = intensityD / sum;
			//intensityD *= (1800 - sqrt(distanceToD)) / 1200;
			//normalised pointer vectors to Ruber and Duo
			R = normalize(glm::vec3(-translationMatrix2[3][0], -translationMatrix2[3][1], -translationMatrix2[3][2]));

			posD = normalize(glm::vec3(translationMatrix2[3][0] - duoModelMat[3][0],
				translationMatrix2[3][1] - duoModelMat[3][1],
				translationMatrix2[3][2] - duoModelMat[3][2]));






			glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
			glUniformMatrix4fv(ROT, 1, GL_FALSE, glm::value_ptr(rotationMatrix2));
			glUniformMatrix4fv(TOT, 1, GL_FALSE, glm::value_ptr(translationMatrix2));
			glUniformMatrix4fv(PD, 1, GL_FALSE, glm::value_ptr(duoModelMat));
			glUniform3fv(dirD, 1, glm::value_ptr(posD));
			glUniform3fv(dirR, 1, glm::value_ptr(R));

			glUniform4fv(CR, 1, glm::value_ptr(ruberLightColor));
			glUniform4fv(CD, 1, glm::value_ptr(duoLightColor));
			shaderID = 3;
			glUniform1i(shaderHandle, shaderID);
			glUniform1f(intensD, intensityD);
			glUniform1i(shaderHandle, shaderID);
			glUniform1f(intensR, intensityR);

			glBindVertexArray(vao[ia]);
			if (ia >= nNonAstObj && ia < nNonAstObj + nAsteroids) modelID = (ia - nNonAstObj) % 5 + nNonAstObj;
			else modelID = ia;
			glDrawArrays(GL_TRIANGLES, 0, nVertices[modelID]);
		}
		else if (ia == 2) //warbird
		{
			glUseProgram(shaderProgram[0]); //1
			modelMatrix = shape[ia]->getModelMatrix(ia);
			ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
			rotationMatrix2 = shape[ia]->getModelMatrix(ia);
			translationMatrix2 = shape[ia]->getTranslationMatrix(ia);
			duoModelMat = shape[3]->getModelMatrix(3);

			//distances to each sun (already squared)
			distanceToR = translationMatrix2[3][0] * translationMatrix2[3][0] +
				translationMatrix2[3][1] * translationMatrix2[3][1] +
				translationMatrix2[3][2] * translationMatrix2[3][2];
			distanceToR *= lightMitigator; //give ruber more intensity

			distanceToD = (translationMatrix2[3][0] - duoModelMat[3][0])*(translationMatrix2[3][0] - duoModelMat[3][0]) +
				(translationMatrix2[3][1] - duoModelMat[3][1])*(translationMatrix2[3][1] - duoModelMat[3][1]) +
				(translationMatrix2[3][2] - duoModelMat[3][2])*(translationMatrix2[3][2] - duoModelMat[3][2]);



			// light intensity is proportional to the inverse sqare of distance
			intensityR = (float)1 / distanceToR;
			intensityD = (float)1 / distanceToD;

			//fractional intensity
			float sum = (intensityR + intensityD) / 3;

			intensityR = intensityR / sum;
			intensityD = intensityD / sum;
			//normalised pointer vectors to Ruber and Duo
			R = normalize(glm::vec3(-translationMatrix2[3][0], -translationMatrix2[3][1], -translationMatrix2[3][2]));
			posD = normalize(glm::vec3(-translationMatrix2[3][0] + duoModelMat[3][0], -translationMatrix2[3][1]
				+ duoModelMat[3][1], -translationMatrix2[3][2] + duoModelMat[3][2]));


			viewVec = normalize(glm::vec3(-translationMatrix2[3][0] + eye.x,
				-translationMatrix2[3][1] + eye.y,
				-translationMatrix2[3][2] + eye.z));

			glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
			glUniformMatrix4fv(ROT, 1, GL_FALSE, glm::value_ptr(rotationMatrix2));
			glUniformMatrix4fv(TOT, 1, GL_FALSE, glm::value_ptr(translationMatrix2));
			glUniformMatrix4fv(PD, 1, GL_FALSE, glm::value_ptr(duoModelMat));
			glUniform3fv(dirD, 1, glm::value_ptr(posD));
			glUniform3fv(dirR, 1, glm::value_ptr(R));
			glUniform3fv(VV, 1, glm::value_ptr(viewVec));
			shaderID = 2;
			glUniform1i(shaderHandle, shaderID);
			glUniform4fv(CR, 1, glm::value_ptr(ruberLightColor));
			glUniform4fv(CD, 1, glm::value_ptr(duoLightColor));

			glUniform1f(intensD, intensityD);
			glUniform1f(intensR, intensityR);

			//glUniform3fv(PR, 1,  glm::value_ptr(ruberPos));
			//glUniform3fv(PD, 1, glm::value_ptr(duoPos));
			glBindVertexArray(vao[ia]);
			if (ia >= nNonAstObj && ia < nNonAstObj + nAsteroids) modelID = (ia - nNonAstObj) % 5 + nNonAstObj;
			else modelID = ia;

			//if the warbird is out of health due to colisions or lasers, it will dissapear
		if(healthValue >0)	glDrawArrays(GL_TRIANGLES, 0, nVertices[modelID]);
		}
		else if (ia == 4 || ia == 5 )
		{
			
			glUseProgram(shaderProgram[0]);
			modelMatrix = shape[ia]->getModelMatrix(ia);
			ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
			rotationMatrix2 = shape[ia]->getModelMatrix(ia);
			translationMatrix2 = shape[ia]->getModelMatrix(ia);
			duoModelMat = shape[3]->getModelMatrix(3);

			//distances to each sun (already squared)
			distanceToR = translationMatrix2[3][0] * translationMatrix2[3][0] +
				translationMatrix2[3][1] * translationMatrix2[3][1] +
				translationMatrix2[3][2] * translationMatrix2[3][2];
			distanceToR *= lightMitigator; //give ruber more intensity

			distanceToD = (translationMatrix2[3][0] - duoModelMat[3][0])*(translationMatrix2[3][0] - duoModelMat[3][0]) +
				(translationMatrix2[3][1] - duoModelMat[3][1])*(translationMatrix2[3][1] - duoModelMat[3][1]) +
				(translationMatrix2[3][2] - duoModelMat[3][2])*(translationMatrix2[3][2] - duoModelMat[3][2]);


			// light intensity is proportional to the inverse sqare of distance
			intensityR = (float)1 / distanceToR;
			intensityD = (float)1 / distanceToD;

			//fractional intensity
			float sum = (intensityR + intensityD) / 3;

			intensityR = intensityR / sum;
			intensityD = intensityD / sum;
			//normalised pointer vectors to Ruber and Duo
			R = normalize(glm::vec3(-translationMatrix2[3][0], -translationMatrix2[3][1], -translationMatrix2[3][2]));
			posD = normalize(glm::vec3(translationMatrix2[3][0] - duoModelMat[3][0], translationMatrix2[3][1]
				- duoModelMat[3][1], translationMatrix2[3][2] - duoModelMat[3][2]));




			glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
			glUniformMatrix4fv(ROT, 1, GL_FALSE, glm::value_ptr(rotationMatrix2));
			glUniformMatrix4fv(TOT, 1, GL_FALSE, glm::value_ptr(translationMatrix2));
			glUniformMatrix4fv(PD, 1, GL_FALSE, glm::value_ptr(duoModelMat));
			glUniform3fv(dirD, 1, glm::value_ptr(posD));
			glUniform3fv(dirR, 1, glm::value_ptr(R));
			shaderID = 3;
			glUniform1i(shaderHandle, shaderID);
			glUniform4fv(CR, 1, glm::value_ptr(ruberLightColor));
			glUniform4fv(CD, 1, glm::value_ptr(duoLightColor));

			glUniform1f(intensD, intensityD);
			glUniform1f(intensR, intensityR);

			
			glBindVertexArray(vao[ia]);

			glDrawArrays(GL_TRIANGLES, 0, nVertices[ia]);
		}
		else if (ia == 3)//duo (a red sun)
		{
			glUseProgram(shaderProgram[0]); //
			glUniform4fv(CD, 1, glm::value_ptr(duoLightColor));
			modelMatrix = shape[ia]->getModelMatrix(ia);
			ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

			glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
			shaderID = 1;
			glUniform1i(shaderHandle, shaderID);
			glBindVertexArray(vao[ia]);
			if (ia >= nNonAstObj && ia < nNonAstObj + nAsteroids) modelID = (ia - nNonAstObj) % 5 + nNonAstObj;
			else modelID = ia;
			//glDrawArrays(GL_TRIANGLES, 0, nVertices[modelID]);
		}
		else if (ia == 6)//missiles
		{
			glUseProgram(shaderProgram[0]);
			glUniform4fv(CR, 1, glm::value_ptr(ruberLightColor));
			modelMatrix = shape[ia]->getModelMatrix(ia);
			ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

			glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
			shaderID = 0;
			glUniform1i(shaderHandle, shaderID);
			glBindVertexArray(vao[ia]);
			if (ia >= nNonAstObj && ia < nNonAstObj + nAsteroids) modelID = (ia - nNonAstObj) % 5 + nNonAstObj;
			else modelID = ia;
			glDrawArrays(GL_TRIANGLES, 0, nVertices[modelID]);
		}
	}	
	shader->Bind();
	texture->Bind();
	modelMatrix = shape[0]->getModelMatrix(0);
	shader->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	mesh->Draw(vao, buffer, nModels-numOBJ, 0);
	
	shaderRuber->Bind();
	textureRuber->Bind();
	modelMatrix = shape[209]->getModelMatrix(209);
	shaderRuber->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	meshRuber->Draw(vao, buffer, nModels-numOBJ, 1);

	modelMatrix = shape[1]->getModelMatrix(1);
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	rotationMatrix2 = glm::rotate(modelMatrix, -0.02f, glm::vec3(0, 1, 0));
	translationMatrix2 = shape[1]->getModelMatrix(1);
	duoModelMat = shape[3]->getModelMatrix(3);

	//distances to each sun (already squared)
	distanceToR = translationMatrix2[3][0] * translationMatrix2[3][0] +
		translationMatrix2[3][1] * translationMatrix2[3][1] +
		translationMatrix2[3][2] * translationMatrix2[3][2];
	distanceToR *= lightMitigator; //give ruber more intensity

	distanceToD = (translationMatrix2[3][0] - duoModelMat[3][0])*(translationMatrix2[3][0] - duoModelMat[3][0]) +
		(translationMatrix2[3][1] - duoModelMat[3][1])*(translationMatrix2[3][1] - duoModelMat[3][1]) +
		(translationMatrix2[3][2] - duoModelMat[3][2])*(translationMatrix2[3][2] - duoModelMat[3][2]);


	// light intensity is proportional to the inverse sqare of distance
	intensityR = (float)1 / distanceToR;
	intensityD = (float)1 / distanceToD;

	//fractional intensity
	float sum = (intensityR + intensityD) / 3;

	intensityR = intensityR / sum;
	intensityD = intensityD / sum;
	//normalised pointer vectors to Ruber and Duo
	R = normalize(glm::vec3(-translationMatrix2[3][0], -translationMatrix2[3][1], -translationMatrix2[3][2]));
	posD = normalize(glm::vec3(translationMatrix2[3][0] - duoModelMat[3][0], translationMatrix2[3][1]
		- duoModelMat[3][1], translationMatrix2[3][2] - duoModelMat[3][2]));
	
	shaderUnum->Bind();
	textureUnum->Bind();
	shaderUnum->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera, R, posD, ruberLightColor, duoLightColor, intensityR, intensityD, rotationMatrix2);
	meshUnum->Draw(vao, buffer, nModels-numOBJ, 2);

	shaderDuo->Bind();
	textureDuo->Bind();
	modelMatrix = shape[3]->getModelMatrix(3);
	shaderDuo->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	meshDuo->Draw(vao, buffer, nModels-numOBJ, 3);

	shaderGrav->Bind();
	modelMatrix = shape[212]->getModelMatrix(0);
	shaderGrav->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	textGrav->Draw(vao, buffer, nModels - numOBJ, 4);

	shaderVel->Bind();
	modelMatrix = shape[213]->getModelMatrix(0);
	shaderVel->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	textVel->Draw(vao, buffer, nModels - numOBJ, 5);

	shaderMiss->Bind();
	modelMatrix = shape[214]->getModelMatrix(0);
	shaderMiss->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	textMiss->Draw(vao, buffer, nModels - numOBJ, 6);

	shaderOn->Bind();
	modelMatrix = shape[215]->getModelMatrix(0);
	shaderOn->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	textOn->Draw(vao, buffer, nModels - numOBJ, 7);

	shaderOff->Bind();
	modelMatrix = shape[216]->getModelMatrix(0);
	shaderOff->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	textOff->Draw(vao, buffer, nModels - numOBJ, 8);

	shaderHealth->Bind();
	modelMatrix = shape[228]->getModelMatrix(0);
	shaderHealth->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	health->Draw(vao, buffer, nModels - numOBJ, 20);

	shaderHealthBar->Bind();
	modelMatrix = shape[229]->getModelMatrix(0);
	shaderHealthBar->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	healthBar->Draw(vao, buffer, nModels - numOBJ, 21);

	shaderSpeedBar->Bind();
	modelMatrix = shape[230]->getModelMatrix(0);
	shaderSpeedBar->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	speedBar->Draw(vao, buffer, nModels - numOBJ, 22);

	laserShader->Bind();
	textureLaser->Bind();
	modelMatrix = shape[227]->getModelMatrix(0);
	laserShader->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
	laser->Draw(vao, buffer, nModels - numOBJ, 19);


	for (int i = 0; i < 10; i++)
	{
		lllShader[i]->Bind();
		modelMatrix = shape[217+i]->getModelMatrix(0);
		lllShader[i]->Update(modelMatrix, viewMatrix, projectionMatrix, *transform, *camera);
		lllMesh[i]->Draw(vao, buffer, nModels - numOBJ, 9+i);
	}
	
	glutSwapBuffers();
	if (invincableMode) healthValue = 5.0f;
	if (healthValue <= 0) missilesFired = 11;
	frameCount++;
	// see if a second has passed to set estimated fps information
	currentTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
	timeInterval = currentTime - lastTime;
	if (timeInterval >= 1000) {
		sprintf(fpsStr, " fps %4d", (int)(frameCount / (timeInterval / 1000.0f)));
		sprintf(upsStr, " timeQuantum %i", (timerDelay[timeQ]));
		lastTime = currentTime;
		frameCount = 0;
		updateTitle();
	}
	
}



// Animate scene objects by updating their transformation matrices
// timerDelay = 40, or 25 updates / second
void update(int i) {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(timerDelay[timeQ], update, 1);
	
	//update locations to be sent to update
	unumTrans = shape[1]->getTranslationMatrix(1);
	missileSiteTrans = shape[7]->getTranslationMatrix(7);
	warBTrans = shape[2]->getModelMatrix(2);
	duoTrans = shape[3]->getTranslationMatrix(3);
	
	checkCollision();
	checkMissileCollision();
	checkLaserCollision();
	
	 //die-down of roll and pitch
	 if (pitch < 0)
	 {
		 if (pitch > -0.001f) pitch = 0;
		 else pitch += 0.001f;
	 }
	 else
	 {
		 if (pitch < 0.001f) pitch =0; 
		 else pitch -= 0.001f;
	 }

	 if (roll < 0)
	 {
		 if (roll > -0.001f) roll = 0;
		 else roll += 0.001f;
	 }
	 else
	 {
		 if (roll < 0.001f) roll = 0;
		 else roll -= 0.001f;
	 }
	
	 float correction;
	 glm::vec3 right;
	 glm::vec3 upTemp;

		 switch(trackShip)
	 {
		 case 1: //warbird view
		 

			 behindShipView = shape[2]->getModelMatrix(2);

			 eye = glm::vec3(behindShipView[3][0], behindShipView[3][1] + 100, behindShipView[3][2] + 250);
			 at = glm::vec3(behindShipView[3][0], behindShipView[3][1], behindShipView[3][2]);
			 up = glm::vec3(behindShipView[1][0], behindShipView[1][1], behindShipView[1][2]);
			 upTemp = eye - at;
			 right = glm::cross(upTemp, up);
			 up = glm::normalize(glm::cross(right, upTemp));
			 strcpy(viewStr, " Ship View");
			 viewMatrix = glm::lookAt(eye, at, up);


		  break;

	case 2: //behind ship view
	 
		 behindShipView = shape[2]->getModelMatrix(2);

		 eye = glm::vec3(behindShipView[3][0] + behindShipView[2][0] * 10, behindShipView[3][1] + behindShipView[2][1] * 10, behindShipView[3][2] + behindShipView[2][2] * 10);
		 at = glm::vec3(behindShipView[3][0], behindShipView[3][1], behindShipView[3][2]);
		 up = glm::vec3(behindShipView[1][0], behindShipView[1][1], behindShipView[1][2]);
		 strcpy(viewStr, " Behind Ship View");
		 viewMatrix = glm::lookAt(eye, at, up);
	 break;
	case 3: //cokpit view
	
		if (thrust < 0) correction = 1 - thrust / 10;
		else correction = 1 + thrust / 10;

		behindShipView = shape[2]->getModelMatrix(2);
		eye = glm::vec3(behindShipView[3][0] - behindShipView[2][0] * 3* correction, behindShipView[3][1] - behindShipView[2][1] * 3 * correction, behindShipView[3][2] - behindShipView[2][2] * 3 * correction);
		at = glm::vec3(behindShipView[3][0] - behindShipView[2][0] * 4 * correction, behindShipView[3][1] - behindShipView[2][1] * 4 * correction, behindShipView[3][2] - behindShipView[2][2] * 4 * correction);
		up = glm::vec3(behindShipView[1][0], behindShipView[1][1], behindShipView[1][2]);
		strcpy(viewStr, " Cockpit View");
		viewMatrix = glm::lookAt(eye, at, up);
	 break;

	case 4: //Unum view
		behindShipView = shape[1]->getModelMatrix(1);
		eye = glm::vec3(behindShipView[3].x, behindShipView[3].y + 400.0f, behindShipView[3].z);
		at = glm::vec3(behindShipView[3].x, 0.0f, behindShipView[3].z);
		up = glm::vec3(0.0f, 0.0f, -1.0f);
		strcpy(viewStr, " Unum View");
		viewMatrix = glm::lookAt(eye, at, up);
		break;

	case 5: //Duo view
		behindShipView = shape[3]->getModelMatrix(3);
		eye = glm::vec3(behindShipView[3].x, behindShipView[3].y + 400.0f, behindShipView[3].z);
		at = glm::vec3(behindShipView[3].x, behindShipView[3].y, behindShipView[3].z);
		up = glm::vec3(0.0f, 0.0f, -1.0f);
		strcpy(viewStr, " Duo View");
		viewMatrix = glm::lookAt(eye, at, up);
		break;

	case 6: //initial
		// initially use a front view
		eye = glm::vec3(0.0f, 800.0f, 2000.0f);  
		at = glm::vec3(0.0f, 0.0f, 0.0f);  
		up = -glm::normalize(glm::cross((glm::vec3(1.0f, 0.0f, 0.0f)), eye));  
		viewMatrix = glm::lookAt(eye, at, up);
		strcpy(viewStr, " Initial view");
		break;

	case 7:
		eye = glm::vec3(0.0f, 500.0f, 2000.0f);  
		at = glm::vec3(0.0f, 0.0f, 0.0f);  
		up = -glm::normalize(glm::cross((glm::vec3(1.0f, 0.0f, 0.0f)), eye));
		viewMatrix = glm::lookAt(eye, at, up);
		strcpy(viewStr, " Front view");
		break;

	case 8:
		eye = glm::vec3(1000.0f, 250.0f, 0.0f);   
		at = glm::vec3(0.0f, 0.0f, 0.0f);   
		up = -glm::normalize(glm::cross((glm::vec3(0.0f, 0.0f, -1.0f)), eye));
		viewMatrix = glm::lookAt(eye, at, up);
		strcpy(viewStr, " Right view");
		break;

	case 9:
		eye = glm::vec3(0.0f, 3000.0f, 0.0f);  
		at = glm::vec3(0.0f, 0.0f, 0.0f);     
		up = glm::vec3(0.0f, 0.0f, -1.0f);   
		strcpy(viewStr, " Top view");
		viewMatrix = glm::lookAt(eye, at, up);
		break;
	}

		 for (int i = 0; i < nModels - numOBJ; i++)
		 {
			 if (i!=2) shape[i]->update(i, currentTime, nAsteroids, roll, thrust, pitch, unumTrans, missileSiteTrans, warBTrans, timeOfShot);
			 else shape[i]->update(i, currentTime, nAsteroids, roll, thrust, pitch, unumTrans, duoTrans, missileSiteTrans, warBTrans, timeOfShot, planetGravity);
		 }
	for (int i = nModels - numOBJ; i < nModels; i++)
	{
		 if (i < 212 ) shape[i]->update(i, currentTime, nAsteroids, roll, thrust, pitch, unumTrans, missileSiteTrans, warBTrans, timeOfShot);
		 else if (i == 227)
		 {
	
			 if (armDeathStar && !deathStarDestroyed) 
			 {
				
				 unumTrans = shape[1]->getModelMatrix(1);
				 float distanceOfWBToMS =	 (missileSiteTrans[3][0] - warBTrans[3][0])*(missileSiteTrans[3][0] - warBTrans[3][0]) +
											 (missileSiteTrans[3][1] - warBTrans[3][1])*(missileSiteTrans[3][1] - warBTrans[3][1]) +
											 (missileSiteTrans[3][2] - warBTrans[3][2])*(missileSiteTrans[3][2] - warBTrans[3][2]);

				 float distanceOfWBToUnum =	 (unumTrans[3][0] - warBTrans[3][0])*(unumTrans[3][0] - warBTrans[3][0]) +
											 (unumTrans[3][1] - warBTrans[3][1])*(unumTrans[3][1] - warBTrans[3][1]) +
											 (unumTrans[3][2] - warBTrans[3][2])*(unumTrans[3][2] - warBTrans[3][2]);

			
				 unumHoleLocation = glm::vec3(missileSiteTrans[3][0], missileSiteTrans[3][1], missileSiteTrans[3][2]);
				 unumToWB = -glm::normalize(glm::vec3(unumHoleLocation.x - warBTrans[3][0], unumHoleLocation.y - warBTrans[3][1], unumHoleLocation.z- warBTrans[3][2]));
				
				 if ( distanceOfWBToMS < distanceOfWBToUnum) //the death star is pointing at the warbird
				 {
					 armDeathStar = false;
					 timeOfLastLaser = currentTime;
				 }
			 }
			 shape[i]->update(currentTime, timeOfLastLaser, unumTrans, warBTrans, unumToWB, unumHoleLocation);
			 if (timeOfLastLaser < currentTime - 500 && healthValue > 0) armDeathStar = true;
		 }
		 else shape[i]->update(i, planetGravity, eye, at, up, missilesFired, healthValue, thrust);
	 }
}

// Quit or set the view
void keyboard(unsigned char key, int x, int y) {
	
	switch (key) {
	case 033: case 'q':  case 'Q': exit(EXIT_SUCCESS); break;
	case 'b': case 'B':  // front view
		trackShip = 7;
		 break;
	case 'r': case 'R':
		trackShip = 8;
		 break;
	case 'p': case 'P':  // top view
		trackShip = 9;
		 break;

	case 't': case'T': //time quantum 
		timeQ = (timeQ + 1) % 4;
		break;

	case 'g': case 'G':  // planet gravity
		planetGravity = !planetGravity;
		break;

	case 'w': case 'W': //warping
		switch (warp) {
		case 'z':
			warp = 'x';
			shape[2]->warping(shape[1]->getTranslationMatrix(1), 1, shape[2]->getModelMatrix(2));
			trackShip = 2;
			break;
		case 'x':
			warp = 'z';
			shape[2]->warping(shape[3]->getModelMatrix(3), -1, shape[2]->getModelMatrix(2));
			trackShip = 2;
			break;
		default:
			warp = 'z';
			break;
		}
		break;
	case 'v': case 'V':  // toggle view
		if (trackShip!=9) trackShip++;
		else trackShip = 1;
		break;

	case 'i': case 'I':  // invincable mode
		invincableMode = !invincableMode;
		break;

	case '1':   // follow ship view
		trackShip = 1;
		 break;
	case '2':   // follow ship behind view
		trackShip = 2;
		break;

	case '3':   // cockpit view
		trackShip = 3;
		break;

	case '4':
		trackShip = 4;
		break;

	case '5':
		trackShip = 5;
		break;

	case 'a': case 'A':  
		thrust+= 1.0f;
		 break;
	case 'z': case 'Z':
		thrust -= 1.0f;
		break;
	case 'f': case 'F':
		if (missilesFired<=10) timeOfShot = glutGet(GLUT_ELAPSED_TIME);
		missilesFired++;
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

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitContextVersion(3, 3);
	
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Warbird: Nir and Megan!");
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
	glutTimerFunc(timerDelay[timeQ], update, 1);
	glutIdleFunc(display);
	glutMainLoop();
	printf("done\n");
	return 0;
}


