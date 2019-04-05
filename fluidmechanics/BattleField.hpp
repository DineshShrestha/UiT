#pragma once

#include <windows.h>
#include<GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include"C:\Users\Dinesh\Documents\Visual Studio 2015\Projects\spaceFighter\include\SOIL\SOIL.h"
#include "sceneobject.hpp"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

class BattleField : public SceneObject
{
	public:
		BattleField(glm::vec3 startPos, glm::vec3 step, int mode);
		~BattleField();

  protected:
		virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

		glm::vec3 getStep() const;
		glm::vec3 getPos() const;

		void Array();
		void Area1();
		void Area2();
		void loadArea1();
		void loadArea2();
		void loadHMap();
		void loadLMap();
	private:
		std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
		std::vector< glm::vec2 > texCordArray_;// texture coord array
		std::vector <glm::uint> arrayIndex;
		GLuint hMap;
		GLuint lMap;
		GLuint tex_2D_Area1;
		GLuint tex_2D_Area2;
		int gridX_;
		int gridZ_;
		glm::vec3 step_;
		glm::vec3 pos_;
		int mode_;
		
		//GLfloat fogColor_[4] = { 0.5f, 0.5f,0.5f, 0.5f };
		//Shader shader_;
		//unsigned int indexArray[3][5];
		//int vertices[];
    
};

