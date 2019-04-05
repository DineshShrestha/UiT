#include"GL\glew.h"
#include <windows.h>
#include <GL/freeglut.h> 
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Input.hpp"

#include "GameManager.hpp"


#include "glm/glm/glm.hpp"
#include <iostream>

std::shared_ptr<GameManager> gm;


int window;
int oldTimeFPS;
bool keyPressed[30];
int mousePosX, mousePosY;
float moveX, moveY;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	auto error = glewInit();
	std::cout << "check" << error << std::endl;
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "openGL error:" << gluErrorString(err) << std::endl;
	std::cout.flush();

	char *buff = (char*)glGetString(GL_VERSION);
	std::cout << buff << std::endl;

	buff = (char*)glGetString(GL_VENDOR);
	std::cout << buff << std::endl;
	buff = (char*)glGetString(GL_RENDERER);
	std::cout << buff;


	gm.reset(new GameManager());
	gm->init();

	for (int i = 0; i<30; i++)
		keyPressed[i] = false;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int startFPS = glutGet(GLUT_ELAPSED_TIME);
	int deltaFPS = startFPS - oldTimeFPS;
	oldTimeFPS = startFPS;

	gm->update((1.0f / float(deltaFPS))*1000.0f);//gm->update(counter.fps());
	gm->render();

	if (keyPressed[KEY_ID_W] == true)
	{
		gm->getCam()->moveForward();
	
		//gm->getParticle()->moveForward();
	}
	if (keyPressed[KEY_ID_A] == true)
	{
		gm->getCam()->moveLeft();
		gm->getParticle()->moveLeft();
	}
	if (keyPressed[KEY_ID_D] == true)
	{
		gm->getCam()->moveRight();
		gm->getParticle()->moveRight();
	}

	if (keyPressed[KEY_ID_S] == true)
	{
		gm->getCam()->moveBackward();
		gm->getParticle()->moveBackward();
	}
	if (keyPressed[KEY_ID_SPACE] == true)  gm->getCam()->moveUp();
	if (keyPressed[KEY_ID_C] == true)      gm->getCam()->moveDown();
	
	glutSwapBuffers();
	glutPostRedisplay();

}

void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 27:
		glutDestroyWindow(window);
#ifndef _WIN32
		// Must use this with regular glut, since it never returns control to main().
		exit(0);
#endif
		break;

	case 'w':
		keyPressed[KEY_ID_W] = true;
		break;
	case 'a':
		keyPressed[KEY_ID_A] = true;
		break;
	case 's':
		keyPressed[KEY_ID_S] = true;
		break;
	case 'd':
		keyPressed[KEY_ID_D] = true;
		break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = true;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = true;
		break;
	case 'v':
		keyPressed[KEY_ID_V] = true;
		break;
	case 'b':
		keyPressed[KEY_ID_B] = true;
		break;
	default:
		glutPostRedisplay();
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		keyPressed[KEY_ID_W] = false;
		break;
	case 'a':
		keyPressed[KEY_ID_A] = false;
		break;
	case 's':
		keyPressed[KEY_ID_S] = false;
		break;
	case 'd':
		keyPressed[KEY_ID_D] = false;
		break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = false;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = false;
		break;
	case 'v':
		keyPressed[KEY_ID_V] = true;
		break;
	case 'b':
		keyPressed[KEY_ID_B] = false;
		break;

	}
}

void mousePressed(int button, int state, int posX, int posY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mousePosX = posX;
		mousePosY = posY;
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
	if (keyPressed[MOUSE_LEFT_BUTTON_DOWN])
	{
		int diffX = posX - mousePosX;
		mousePosX = posX;
		int diffY = posY - mousePosY;
		mousePosY = posY;

		// Implement quaternion based mouse move

	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//  glOrtho(-50, 700, -50, 700, -50, 50);
	gluPerspective(60.0f, float(w) / float(h), 1.0f, 3000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(10, 10);
	window = glutCreateWindow("fluidMechanics");
	init();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMoved);

	// Add other callback functions here..

	glutMainLoop();
	return 0;
}