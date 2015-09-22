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

	ruber(int number) {
		id = number;  // for debugging
		int random = rand();   // random num 0..MAXINT
		
		rotationMatrix = glm::mat4();  // no initial orientation
		
		switch (number)
		{
		case 0: //ruber
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(200, 200, 200));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(-20.0f);
			break;

		case 1: //unum
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 50, 50));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(4.0f);
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
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(2.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(1200,0.0f, 0.0f));
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
		
		case 6: //Asteroids
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(35, 20, 23));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(0.1f + (random % 20) / 10.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-500 + rand() % 1000, -500 + rand() % 1000, -500 + rand() % 1000));
			break;
		}		
	}
	
	glm::mat4 getModelMatrix(int i) {
		
			return(rotationMatrix * translationMatrix * scaleMatrix);
			
	}

	void update(int i, double t) {
		
		double sAmp = sin(t/300);
		double cAmp = cos(t / 300);
		double sAmp2 = sin(t / 500);
		double cAmp2 = cos(t / 500);

		 if (i == 4) // moons
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(1200+ 100*sAmp, 0.0f, 100 * cAmp));

		 else if (i == 5) // moons
			 translationMatrix = glm::translate(glm::mat4(), glm::vec3(1200 + 200 * sAmp2, 0.0f, 200 * cAmp2));
			
			rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);
	}
};
