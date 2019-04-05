#pragma once
#include <GL/glew.h>
#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output
#include <GL\gl.h>					// Header File For The OpenGL32 Library
#include <GL\glu.h>					// Header File For The GLu32 Library

#include <GL/freeglut.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "sceneobject.hpp"
#include"datahandler.hpp"
#include "C:\Users\Dinesh\Documents\Visual Studio 2015\Projects\spaceFighter\include\SOIL\SOIL.h"


#define	MAX_PARTICLES	3000		// Number Of Particles To Create

class ParticleGenerators : public SceneObject
{
public:
	ParticleGenerators();
	~ParticleGenerators();
	void moveRight();
	void moveLeft();
	void moveForward();
	void moveBackward();

protected:
	void privateInit();
	void privateRender();
    void privateUpdate();
	void boatFloat();

private:

	typedef struct						// Create A Structure For Particle
	{
		bool	active;					// Active (Yes/No)
		float	life;					// Particle Life
		float	fade;					// Fade Speed
		float	r;						// Red Value
		float	g;						// Green Value
		float	b;						// Blue Value
		float	x;						// X Position
		float	y;						// Y Position
		float	z;						// Z Position
		float	xi;						// X Direction
		float	yi;						// Y Direction
		float	zi;						// Z Direction
		float	xg;						// X Gravity
		float	yg;						// Y Gravity
		float	zg;						// Z Gravity
	}
	particles;							// Particles Structure

	particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)

	GLfloat colors[12][3];


	GLuint tex_2d;

	float	slowdown = 2.0f;				// Slow Down Particles
	float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
	float	yspeed;
	void explosion();
	void beam();
	int mode_;
	bool isShaderExist_;
	std::vector<Data> dP_;
	std::shared_ptr<Datahandler> f_;
};




