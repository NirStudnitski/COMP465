
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
		if (number==0) scaleMatrix = glm::scale(glm::mat4(), glm::vec3(200, 200, 200)); 
		else scaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 50, 50));
		rotationMatrix = glm::mat4();  // no initial orientation
									   //set cube's  rotation axis and rotation radians
		if (number==0) rotationAxis = glm::vec3(0, 1, 0);
		else  rotationAxis = glm::vec3(0, 1.0f, 0);
		// rotate between 0.1 and 2.0 degrees
		if (number==0) radians = glm::radians(-200.0f);
		else  radians = glm::radians(40.0f);
		// random initial placement +/- 500 from origin in X, Y, Z
		if (number == 1)
		{
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3(800, 0.0f, 0.0f));
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
