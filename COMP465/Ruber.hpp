
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
			radians = glm::radians(-200.0f);
			break;

		case 1: //unum
			scaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 50, 50));
			rotationAxis = glm::vec3(0, 1, 0);
			radians = glm::radians(40.0f);
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

		}
		
		
			
	}
	
	glm::mat4 getModelMatrix(int i) {
		
			if (i==0) return(rotationMatrix * translationMatrix * scaleMatrix);
			else return(rotationMatrix * translationMatrix * scaleMatrix*0.1f);
		
	}

	void update() {
		rotationMatrix = glm::rotate(rotationMatrix, radians/10, rotationAxis);
		//translationMatrix = glm::translate(translationMatrix, translation);
	}
};
