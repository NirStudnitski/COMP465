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
	char * speedS = "blklk";

	const float PI = 3.14159f;

	// for unum's eliptical orbit calculations
	glm::vec3 velocity = glm::vec3(0.0f, 5.0f, 10.0f); //unum's initial velocity
	glm::vec3 mVelocity = glm::vec3(0.0f, 0.0f, 0.0f); //missile direction
	
	float gravConst = 100.0f;
	float missileForceConst = 6.0f; //how quickly the missile updates its direction
	glm::vec3 gravity; //for unum
	glm::vec3 forceOnMissile;
	
	float distance;


	float radians;
	float radiansD = 0.5f; //radians for duo
	const int nNonAstObj = 8; // number of non-asteroid objects
	bool orbit = true;
	
	

public:

	ruber(int number, int nAst) {
		id = number;  
		int random = rand()%200; 
		float randomf = rand() / 1000.0f;

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
			//radians = glm::radians(0.0f);
			translationMatrix = glm::translate(glm::mat4(),
				glm::vec3((500+ random)* cos(randomf), 0.0f, (500 + random)* sin(randomf)));
		}
		else if (number > 211)
		{
			if (number == 227)
			{
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(20, 1, 1));
				
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 820.0, 2000.0f));
				orbit = false;
			}
			
			else if (number == 229) //health bar
			{
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.1f, 1, 1.5f));
				rotationMatrix = glm::rotate(glm::mat4(1.0f), 1.57f, glm::vec3(1, 0, 0));

				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 200.0, 1300.0f));
				orbit = false;
			}

			else if (number == 230) //speed bar
			{
				
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.1f, 1, 1.5f));
				rotationMatrix = glm::rotate(glm::mat4(1.0f), 1.57f, glm::vec3(1, 0, 0));

				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 200.0, 1300.0f));
				orbit = false;
		
			}
			else 
			{
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(5, 5, 5));
				rotationMatrix = glm::rotate(glm::mat4(1.0f), 1.57f, glm::vec3(1, 0, 0));

				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 200.0, 1300.0f));
				orbit = false;
			}
		}
		else
		{
			switch (number) {
			case 0: //ruber
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(300, 300, 300));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(-0.50f);
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
				rotationAxis = glm::vec3(1, 0,0 );
				radians = glm::radians(-1.8f);
				
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0, 600.0, 1750.0f));
				

				orbit = false;
				break;

			case 3: //Duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(60, 60, 60));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(radiansD);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(-1200, 0.0f, 0.0f));
				break;

			case 4: //Duo's outer moon - suspended between duo and ruber
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(40, 40, 40));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(radiansD);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(-1100, 0.0f, 0.0f));
				break;

			case 5: //Duo's moon orbiting duo
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(radiansD);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(-1000, 0.0f, 0.0f));
				break;

			case 6: //missile
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(20, 20, -20));
				rotationAxis = glm::vec3(1, 0, 0);
				rotationMatrix = glm::rotate(rotationMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
				radians = glm::radians(0.0f);
				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(0.0f, 0.0, 10000.0f));
				orbit = false;
				break; 

			case 7: //missile site for unum
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(30, 30, 30));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(0.0f);

				translationMatrix = glm::translate(glm::mat4(),
					glm::vec3(800, 0.0f, 0.0f));
				break;

			case 209: // star sphere
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(6000, 6000, 6000));
				rotationAxis = glm::vec3(0, 1, 0);
				radians = glm::radians(0.05f);
				
				break;
			
			
			}
		}
	}

	void warping(glm::mat4 transMatrix, glm::mat4 rotMatrix) {
		glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(0, 400.0f, 0));
		translationMatrix = rotMatrix * transMatrix * translation;
		rotationMatrix = glm::rotate(glm::mat4(), -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	

	glm::mat4 getModelMatrix(int i) {

		if (i <212 || i==227 || i==230 || i==229) 
		{
			if (orbit) return(rotationMatrix * translationMatrix * scaleMatrix);
			else return(translationMatrix * rotationMatrix * scaleMatrix);
		}
		else return translationMatrix;
			
	}

	glm::mat4 getTranslationMatrix(int i) {

		
			return translationMatrix;

	}
	glm::mat4 getRotationMatrix(int i) {


		return rotationMatrix;

	}

	//text update
	void update(int i, bool gravity, glm::vec3 eye, glm::vec3 at, glm::vec3 up, int missilesFired, float health, float thrust)
	{
		
		glm::vec3 atN = glm::normalize(at);
		glm::vec3 upN = glm::normalize(up);
		glm::vec3 towards = glm::normalize(eye - at);
		glm::vec3 rightN = glm::cross(upN, towards);
		float rightOffset, upOffset;

		translationMatrix[3][0] = eye.x - towards.x*100.0f;
		translationMatrix[3][1] = eye.y - towards.y*100.0f;
		translationMatrix[3][2] = eye.z - towards.z*100.0f;

		translationMatrix[2][0] = 0;
		translationMatrix[2][1] = 0;
		translationMatrix[2][2] = 0;

		translationMatrix[1][0] = upN.x;
		translationMatrix[1][1] = upN.y;
		translationMatrix[1][2] = upN.z;

		translationMatrix[0][0] = rightN.x;
		translationMatrix[0][1] = rightN.y;
		translationMatrix[0][2] = rightN.z;

		if (i >= 217 && i < 227)
		{
			int missileIndex = i - 217;
			if (10 - missilesFired < missileIndex) missileIndex += 1000;
			rightOffset = -55.0f + 1*missileIndex;
			upOffset = -20.0f;
			translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
			translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
			translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;
		}
		
		else switch (i)
		{
			case 212: //gravity
			
				rightOffset = -75.0f;
				upOffset = -40.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;

				break;

			case 213: //velocity

				rightOffset = -75.0f;
				upOffset = -30.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;

				break;

			case 214: //missiles

				rightOffset = -75.0f;
				upOffset = -20.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;

				break;

			case 215: //on

				rightOffset = -55.0f;
				if (!gravity) rightOffset -= 100;
				upOffset = -40.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;

				break;

			case 216: //off

				rightOffset = -55.0f;
				if (gravity) rightOffset -= 100;
				upOffset = -40.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;

				break;

			case 228: //health

				rightOffset = -75.0f;
				
				upOffset = -10.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;
				

				break;
				
			case 229: //health bar

				rightOffset = -60.0f + health;
				
				upOffset = -8.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.1f + health, 1, 1.5f));

				break;

			case 230: //speed bar
				if (thrust < 0) thrust *= -1;
				rightOffset = -60.0f +thrust;
				upOffset = -28.0f;
				translationMatrix[3][0] += rightN.x*rightOffset + upN.x*upOffset;
				translationMatrix[3][1] += rightN.y*rightOffset + upN.y*upOffset;
				translationMatrix[3][2] += rightN.z*rightOffset + upN.z*upOffset;
				
				scaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.1f+thrust, 1, 1.5f));
				break;

		}
	}



	//warbird update only
	void update(int i, double t, int nAst, float roll, float thrust, float pitch,
		glm::mat4 unumTrans, glm::mat4 duoTrans, glm::mat4 missileSiteTrans, glm::mat4 warBTrans, float timeOfShot, bool planetGravity)

	{


		//roll and pitch
		rotationAxisPitch = glm::vec3(translationMatrix[0][0], translationMatrix[0][1], translationMatrix[0][2]);
		rotationAxisRoll = glm::vec3(translationMatrix[2][0], translationMatrix[2][1], translationMatrix[2][2]);
		rotationMatrix = glm::rotate(rotationMatrix, pitch, rotationAxisPitch);
		rotationMatrix = glm::rotate(rotationMatrix, roll, rotationAxisRoll);

		//thrust
		for (int i = 0; i < 3; i++) // move in the direction of 'at' times thrust
			translationMatrix[3][i] -= rotationMatrix[2][i] * thrust;

		if (planetGravity)
		{
			float ruberMass = 1000, duoMass = 100, unumMass = 200;
			glm::vec3 toRuber = glm::vec3(warBTrans[3][0], warBTrans[3][1], warBTrans[3][2]);
			glm::vec3 toUnum = glm::vec3(warBTrans[3][0] - unumTrans[3][0], warBTrans[3][1] - unumTrans[3][1], warBTrans[3][2] - unumTrans[3][1]);
			glm::vec3 toDuo = glm::vec3(warBTrans[3][0] - duoTrans[3][0], warBTrans[3][1] - duoTrans[3][1], warBTrans[3][2] - duoTrans[3][2]);
			float inverseD2RuberSquared = 1.0f / glm::dot(toRuber, toRuber);
			float inverseD2UnumSquared = 1.0f / glm::dot(toUnum, toUnum);
			float inverseD2DuoSquared = 1.0f / glm::dot(toDuo, toDuo);

			glm::vec3 grav = toRuber*ruberMass*inverseD2RuberSquared + toUnum*unumMass*inverseD2UnumSquared + toDuo*duoMass*inverseD2DuoSquared;
			translationMatrix[3][0] -= grav.x;
			translationMatrix[3][1] -= grav.y;
			translationMatrix[3][2] -= grav.z;

		}
	}
	void update(int i, double t, int nAst, float roll, float thrust, float pitch, 
				glm::mat4 unumTrans, glm::mat4 missileSiteTrans, glm::mat4 warBTrans, float timeOfShot) 
	{

		

		// this code makes unum's orbit eliptical, due to gravity from the sun
		if (i == 1 ) //unum
		{
			translationMatrix = glm::rotate(translationMatrix, 0.02f, glm::vec3(0, 1, 0));

			distance = translationMatrix[3][0] * translationMatrix[3][0]
				+ translationMatrix[3][1] * translationMatrix[3][1]
				+ translationMatrix[3][2] * translationMatrix[3][2];
			gravity = glm::vec3(-translationMatrix[3][0] * gravConst / distance,
				-translationMatrix[3][1] * gravConst / distance,
				-translationMatrix[3][2] * gravConst / distance);
			velocity.x += gravity.x;
			velocity.y += gravity.y;
			velocity.z += gravity.z;
			translationMatrix[3][0] += velocity.x;
			translationMatrix[3][1] += velocity.y;
			translationMatrix[3][2] += velocity.z;

		}


		
		
		else if (i == 4) // moon orbiting duo
		{
			double sAmp = sin(t / 1600);
			double cAmp = cos(t / 1600);
			translationMatrix = glm::translate(glm::mat4(), glm::vec3(-1200 + 100 * sAmp, 0.0f, 100 * cAmp));
		}

		else if (i >= nNonAstObj && i < nNonAstObj + nAst) // ateroids rotation around center
			translationMatrix = glm::rotate(translationMatrix, radians * 20, selfRotationAxis);

		if (i == 6 ) // missile
		{
			if (timeOfShot > 0)
			{
				if (t < timeOfShot + 39) //first frame
				{
					translationMatrix = warBTrans;
					for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) translationMatrix[i][j] *= 0.04f;
					
					mVelocity = glm::vec3(0, 0, 0);
					forceOnMissile = -0.05f * glm::vec3(warBTrans[2][0], warBTrans[2][1], warBTrans[2][2]);
					
				}
				else if (t < timeOfShot + 2000)
				{
					
					mVelocity += forceOnMissile;

					translationMatrix[3][0] += mVelocity.x;
					translationMatrix[3][1] += mVelocity.y;
					translationMatrix[3][2] += mVelocity.z;
				}
				else if (t < timeOfShot + 20000)
				{
					//missile experience a constant force guiding them towards the missile site. guidance kicks in after t>2000 
					glm::vec3 helper = glm::normalize(glm::vec3((missileSiteTrans[3][0] - translationMatrix[3][0]),
						(missileSiteTrans[3][1] - translationMatrix[3][1]),
						(missileSiteTrans[3][2] - translationMatrix[3][2])));
					forceOnMissile = helper * missileForceConst;



					mVelocity += forceOnMissile;
					mVelocity = glm::normalize(mVelocity)*10.0f; //limit the magnitude of mVelocity

					translationMatrix[3][0] += mVelocity.x;
					translationMatrix[3][1] += mVelocity.y;
					translationMatrix[3][2] += mVelocity.z;

					glm::vec3 direction = -glm::normalize(forceOnMissile);
					translationMatrix[2][0] = direction.x;
					translationMatrix[2][1] = direction.y;
					translationMatrix[2][2] = direction.z;

				}
				else
				{
					//return to hidden location outside of frustrum 
					translationMatrix = glm::translate(glm::mat4(),
						glm::vec3(0.0f, 0.0, 10000.0f));
				}
			}
		}
		if (i == 7) // missile site for unum
		{
			float angle = -t / 2550.0f;
			double sAmp = sin(angle);
			double cAmp = cos(angle);
			translationMatrix = unumTrans;
			
			translationMatrix = glm::rotate(translationMatrix, -1.57f, glm::vec3(1,0,0));
			translationMatrix = glm::rotate(translationMatrix, 3.14f, glm::vec3(0, 1, 0));
			translationMatrix = glm::rotate(translationMatrix, -0.02f, glm::vec3(1, 0, 0));
			translationMatrix[3][0] += 110 * cAmp;
			translationMatrix[3][2] += 110 * sAmp;
			

			
		}
		if (i==3) translationMatrix = glm::rotate(translationMatrix, -0.03f, glm::vec3(0, 1, 0));

		if (i != 2 )	rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);



		
	}
};
