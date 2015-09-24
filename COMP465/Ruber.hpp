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
	float radians;

public:

	ruber(int number, int nAst) {
		id = number;  
		int random = rand()%200;   
		float randomf = rand() / 1000;

		rotationMatrix = glm::mat4();  // no initial orientation

		if (number >= 6 && number < 6 + nAst)
		{
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(20+random%20, 20 + random % 20, 20 + random % 20));
			rotationAxis = glm::vec3(0, 0.9, 0.1);
			radians = glm::radians(4.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3((300+ random)* cos(randomf), 0.0f, (300 + random)* sin(randomf)));
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
				radians = glm::radians(3.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(800, 0.0f, 0.0f));
				break;

			case 2: //warbird
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 50, -50));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(0.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, -300.0f, 1000.0f));
				break;

			case 3: //Duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(60, 60, 60));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(2.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1200, 0.0f, 0.0f));
				break;

			case 4: //Duo's moon
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(2.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1300, 0.0f, 0.0f));
				break;

			case 5: //Duo's moon
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(2.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(1100, 0.0f, 0.0f));
				break;

			}
		}
	}
	
	glm::mat4 getModelMatrix(int i) {
		
			return(rotationMatrix * translationMatrix * scaleMatrix);
			
	}

	void update(int i, double t) {
		
		// for the moons' orbit around duo
		double sAmp = sin(t / 300);
		double cAmp = cos(t / 300);
		double sAmp2 = sin(t / 500);
		double cAmp2 = cos(t / 500);

		if (i == 4) // moons
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(1200 + 100 * sAmp, 0.0f, 100 * cAmp));

		else if (i == 5) // moons
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(1200 + 200 * sAmp2, 0.0f, 200 * cAmp2));
			
			rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);
	}
};
