#pragma once

#include <windows.h>
#include"GL/glew.h"
#include <GL/gl.h>
#include<GL/freeglut.h>
#include <GL/glu.h>
#include<GL/glut.h>
#include<cmath>

#include "sceneobject.hpp"
#include "BattleField.hpp"
#include"datahandler.hpp"
#include "Camera.hpp"
#include "particleGen.hpp"
#include"datahandler.hpp"
#include"model.hpp"
#include<string>
#include<sstream>
#include<iostream>

#include<algorithm>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"


class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    //function used in main file
    std::shared_ptr<Camera> getCam();

	std::shared_ptr<ParticleGenerators> getParticle();



	
	//void enemyFire();
  protected:
    virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

	private:
		//Battle field
    std::shared_ptr<BattleField> battlefield1_;


	//spaceship

    std::shared_ptr<Camera> cam_;

	// Particle effects
	//std::shared_ptr<ParticleGenerators> explosion_;
	//std::shared_ptr<ParticleGenerators> beam_;
	std::shared_ptr<ParticleGenerators> boat_;
	std::vector<std::shared_ptr<Model>> model_;
	std::shared_ptr<Datahandler>dataHandler_;


};

