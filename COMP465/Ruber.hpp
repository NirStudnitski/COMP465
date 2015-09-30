# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class ruber {

private:

	int id;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	glm::vec3 rotationAxisPitch;
	glm::vec3 rotationAxisRoll;
	glm::vec3 selfRotationAxis;

	// for unum's eliptical orbit calculations
	glm::vec3 velocity = glm::vec3(0.0f, 5.0f, 10.0f); //unum's initial velocity
	float gravConst = 100.0f;
	glm::vec3 gravity; //for unum
	float distance;


	float radians;
	const int nNonAstObj = 7; // number of non-asteroid objects
	bool orbit = true;
	
	
	//void printText2D(const char * text, int x, int y, int size);
	//void cleanupText2D();


public:

	ruber(int number, int nAst) {
		id = number;  
		int random = rand()%200; 
		
		float randomf = rand() / 1000;

		rotationMatrix = glm::mat4();  

		if (number >= nNonAstObj && number < nNonAstObj + nAst)
		{
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30+random%20, 30 + random % 20, 30 + random % 20));
			rotationAxis = glm::vec3(0, 0.9, 0.0);
			switch (number % 6)
			{
				case 0:
					selfRotationAxis = glm::vec3(0.5, 0.0, 0.5);
					break;
				case 1:
					selfRotationAxis = glm::vec3(0.0, 0.5, 0.5);
					break;
				case 2:
					selfRotationAxis = glm::vec3(0.5, 0.5, 0.0);
					break;
				case 3:
					selfRotationAxis = glm::vec3(0.0, 0.0, 0.5);
					break;
				case 4:
					selfRotationAxis = glm::vec3(0.0, 0.5, 0.0);
					break;
				case 5:
					selfRotationAxis = glm::vec3(0.5, 0.0, 0.0);
					break;
			}
			radians = glm::radians(1.4f - (float) random/250);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3((500+ random)* cos(randomf), 0.0f, (500 + random)* sin(randomf)));
		}
		else
		{
			switch (number) {
			case 0: //ruber
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(300, 300, 300));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(-20.0f);
				break;

			case 1: //unum
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(100, 100, 100));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(0.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(800, 0.0f, 0.0f));
				break;

			case 2: //warbird
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(20, 20, 20));
				rotationAxis = glm::vec3(0, 0, 1);
				radians = glm::radians(0.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 400.0, 1400.0f));
				orbit = false;
				break;

			case 3: //Duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(60, 60, 60));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(4.30f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1200, 0.0f, 0.0f));
				break;

			case 4: //Duo's outer moon - suspended between duo and ruber
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(40, 40, 40));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(0.30f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1100, 0.0f, 0.0f));
				break;

			case 5: //Duo's moon orbiting duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(0.30f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1000, 0.0f, 0.0f));
				break;

			case 6: //missile
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, -30));
				rotationAxis = glm::vec3(1, 0, 0);
				rotationMatrix = glm::rotate(rotationMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
				radians = glm::radians(0.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(280.0f, 0.0, 1080.0f));
				orbit = false;
				break; 
			}
		}
	}

	

	glm::mat4 getModelMatrix(int i) {
		
		if (orbit == true) {
			return(rotationMatrix * translationMatrix * scaleMatrix);
		}
		else
			return(translationMatrix * rotationMatrix * scaleMatrix);
			
	}

	glm::mat4 getTranslationMatrix(int i) {

		
			return translationMatrix;

	}
	glm::mat4 getRotationMatrix(int i) {


		return rotationMatrix;

	}

	void update(int i, double t, int nAst, float roll, float thrust, float pitch) {
		
		// for the moons' orbit around duo
		double sAmp = sin(t / 300);
		double cAmp = cos(t / 300);
		
	// this code makes unum's orbit eliptical, due to gravity from the sun
		if (i == 1) //unum
		{
			distance = translationMatrix[3][0] * translationMatrix[3][0]
				+ translationMatrix[3][1] * translationMatrix[3][1]
				+ translationMatrix[3][2] * translationMatrix[3][2];
			gravity = glm::vec3(-translationMatrix[3][0] *gravConst / distance, 
				-translationMatrix[3][1] * gravConst / distance, 
				-translationMatrix[3][2] * gravConst / distance );
			velocity.x += gravity.x;
			velocity.y += gravity.y;
			velocity.z += gravity.z;
			translationMatrix[3][0] += velocity.x ;
			translationMatrix[3][1] += velocity.y;
			translationMatrix[3][2] += velocity.z;
		}

		
		else if (i == 2) //warbird
		{
			//roll and pitch
			rotationAxisPitch = glm::vec3(translationMatrix[0][0], translationMatrix[0][1], translationMatrix[0][2]);
			rotationAxisRoll = glm::vec3(translationMatrix[2][0], translationMatrix[2][1], translationMatrix[2][2]);
			rotationMatrix = glm::rotate(rotationMatrix, pitch, rotationAxisPitch);
			rotationMatrix = glm::rotate(rotationMatrix, roll, rotationAxisRoll);

			//thrust
			for (int i = 0; i < 3;i++) // move in the direction of 'at' times thrust
				translationMatrix[3][i] -= rotationMatrix[2][i]*thrust;
		}
		else if (i == 4) // moon orbiting duo
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(1200 + 100 * sAmp, 0.0f, 100 * cAmp));


		else if (i >= nNonAstObj && i < nNonAstObj + nAst) // ateroids rotation around center
			translationMatrix = glm::rotate(translationMatrix, radians*20, selfRotationAxis);

		if (i == 6) // missile
		{
			return;
		}
			
		if (i!=2)	rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);
		
	}
};
