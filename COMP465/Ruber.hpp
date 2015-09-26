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
	float radians;
	const int nNonAstObj = 7; // number of non-asteroid objects
	bool orbit = true;
	
	
	void printText2D(const char * text, int x, int y, int size);
	void cleanupText2D();


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
			radians = glm::radians(3.6f - (float) random/100);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3((500+ random)* cos(randomf), 0.0f, (500 + random)* sin(randomf)));
		}
		else
		{
			switch (number) {
			case 0: //ruber
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(400, 400, 400));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(-20.0f);
				break;

			case 1: //unum
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(100, 100, 100));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(1.5f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(800, 0.0f, 0.0f));
				break;

			case 2: //warbird
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 50, -50));
				rotationAxis = glm::vec3(0, 0, 1);
				radians = glm::radians(0.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 0.0, 1000.0f));
				orbit = false;
				break;

			case 3: //Duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(60, 60, 60));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(1.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1200, 0.0f, 0.0f));
				break;

			case 4: //Duo's outer moon - suspended between duo and ruber
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(1.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1100, 0.0f, 0.0f));
				break;

			case 5: //Duo's moon orbiting duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(1.0f);
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

	void update(int i, double t, int nAst, float roll, float thrust, float pitch) {
		
		// for the moons' orbit around duo
		double sAmp = sin(t / 300);
		double cAmp = cos(t / 300);
		
	


		if (i == 2) //warbird
		{
			//roll and pitch
			rotationAxisPitch = glm::vec3(rotationMatrix[0][0], rotationMatrix[0][1], rotationMatrix[0][2]);
			rotationAxisRoll = glm::vec3(rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2]);
			rotationMatrix = glm::rotate(rotationMatrix, pitch, rotationAxisPitch);
			rotationMatrix = glm::rotate(rotationMatrix, roll, rotationAxisRoll);

			//thrust
			for (int i = 0; i < 3;i++) // move in the direction of 'at' times thrust
				translationMatrix[3][i] -= rotationMatrix[2][i]*thrust;
		}
		else if (i == 4) // moon orbiting duo
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(1200 + 100 * sAmp, 0.0f, 100 * cAmp));


		else if (i >= nNonAstObj && i < nNonAstObj + nAst) // ateroids rotation around center
			translationMatrix = glm::rotate(translationMatrix, radians*5, selfRotationAxis);

		if (i == 6) // missile
		{
			return;
		}
			
		if (i!=2)	rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);
		
	}
};
