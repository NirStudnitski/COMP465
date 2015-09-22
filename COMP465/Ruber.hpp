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

		switch (number) {
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

		case 6: //Asteroid 1
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(500, 0.0f, 0.0f));
			break;

		case 7: //Asteroid 2
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.1f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(500, 0.5f, 0.0f));
			break;

		case 8: //3
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.2f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(500, 0.3f, 0.0f));
			break;

		case 9: //4
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.5f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(499, 0.2f, 0.0f));
			break;
		case 10: //5
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(2.1f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(500, 0.5f, 0.4f));
			break;

		case 11: //6
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(497, 0.3f, 0.1f));
			break;

		case 12: //7
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.3f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-500 + rand() % 1000, 0.8f, 0.0f));
			break;
		case 13: //8
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(2.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-500 + rand() % 1000, 0.2f, 0.2f));
			break;

		case 14: //9
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(0.8f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-500 + rand() % 1000, 0.3f, 0.0f));
			break;

		case 15: //10
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-500, 0.9f, 0.3f));
			break;
		case 16: //11
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(1.7f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-510, 10.2f, 0.5f));
			break;

		case 17: //12
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(0.4f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(-500, 0.3f, 6.0f));
			break;

		case 18: //13
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(0.9f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(499, 0.0f, 5.0f));
			break;
		}
	}
	
	glm::mat4 getModelMatrix(int i) {
		
			return(rotationMatrix * translationMatrix * scaleMatrix);
			
	}

	void update(int i, double t) {
		
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
