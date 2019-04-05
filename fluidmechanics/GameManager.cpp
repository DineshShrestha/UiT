#include "GameManager.hpp"
#include<iostream>


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Set default OpenGL states
	glEnable(GL_CULL_FACE);

	// Adding the camera to the scene
	cam_.reset(new Camera());

	/*
	battlefield1_.reset(new BattleField(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 3.0f), 0));
	this->addSubObject(battlefield1_);*/

	auto boat = std::make_shared<Model>("gfx\\","lifeboat.obj", false);
	model_.push_back(boat);
	this->addSubObject(boat);
	//std::cout << "game manager ";
	boat_.reset(new ParticleGenerators());
	this->addSubObject(boat_);
//	explosion_.reset(new ParticleGenerators(0));
	//this->addSubObject(explosion_);

	//beam_.reset(new ParticleGenerators(1));
	//this->addSubObject(beam_);


}

void GameManager::privateRender()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "opengl error:" << gluErrorString(err) << std::endl;
	std::cout.flush();

	GLfloat light_pos[] = { 1.0, 2.0, 3.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	GLfloat fogColor[4] = { 0.3f,0.3f,0.0f, 1.0f };

	//activate fog
	glEnable(GL_FOG);
	//specify the equation to be used
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	// specify parameters
	glFogf(GL_FOG_DENSITY, 0.20f);
	glFogf(GL_FOG_START, 300.0f);
	glFogf(GL_FOG_END, 1500.0f);

	// per-pixel fog calculations
	glHint(GL_FOG_HINT, GL_NICEST);



}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
}


std::shared_ptr<Camera> GameManager::getCam() 
{
  return cam_;
}


std::shared_ptr<ParticleGenerators> GameManager::getParticle()
{
	return boat_ ;
}

