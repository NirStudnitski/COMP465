
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class unum {

private:

	int id;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	float radians;
	bool orbital;

public:

	unum(int number) {
		id = number;  // for debugging
		int random = rand();   // random num 0..MAXINT
		scaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 50, 50));
		rotationMatrix = glm::mat4();  // no initial orientation
									   //set cube's  rotation axis and rotation radians
		rotationAxis = glm::vec3(0, 1, 0);
		// rotate between 0.1 and 2.0 degrees
		radians = glm::radians(40.0f);
		// random initial placement +/- 500 from origin in X, Y, Z
		//translationMatrix = glm::translate(glm::mat4(),
		//	glm::vec3(-500 + rand() % 1000, -500 + rand() % 1000, -500 + rand() % 1000));
		// determine rotation type
		if (random % 2 == 0)
			orbital = true;
		else
			orbital = false;
	}

	glm::mat4 getModelMatrix() {
		if (orbital) // orbital rotation
			return(rotationMatrix * translationMatrix * scaleMatrix);
		else  // center rotation
			return(translationMatrix * rotationMatrix * scaleMatrix);
	}

	void update() {
		rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);
		//translationMatrix = glm::translate(translationMatrix, translation);
	}
};
