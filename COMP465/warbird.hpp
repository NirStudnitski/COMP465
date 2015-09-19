
# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

class warbird {

private:

	int id;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	float radians;


public:

	warbird() 
	{
		
		scaleMatrix = glm::scale(glm::mat4(), glm::vec3(20, 20, 20));
		
		rotationMatrix = glm::mat4();  // no initial orientation
									   //set cube's  rotation axis and rotation radians
		rotationAxis = glm::vec3(0, 1, 0);
		radians = glm::radians(-200.0f);

		//location
		translationMatrix = glm::translate(glm::mat4(),
			glm::vec3(800, 0.0f, 0.0f));
		




	}

	glm::mat4 getModelMatrix(int i) {

		if (i == 0) return(rotationMatrix * translationMatrix * scaleMatrix);
		else return(rotationMatrix * translationMatrix * scaleMatrix*0.1f);

	}

	void update() {
		rotationMatrix = glm::rotate(rotationMatrix, radians / 10, rotationAxis);
		//translationMatrix = glm::translate(translationMatrix, translation);
	}
};
