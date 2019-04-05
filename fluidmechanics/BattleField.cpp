#include "BattleField.hpp"
#include<iostream>
#include <vector>


BattleField::BattleField(glm::vec3 startPos, glm::vec3 step, int mode)
{
	gridX_ = 32;
	gridZ_ = 512;
	mode_ = mode;
	step_ = step;
	pos_ = startPos;
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
	//matrix_ = glm::translate(matrix_, getPos());
	Array();
	
	if (this->mode_ == 0)
	{
		loadArea1();
		loadHMap();
		loadLMap();
		
	}
	else if (this->mode_ == 1)
	{
		loadArea2();
		loadHMap();
		loadLMap();
		

	}

	//applying shader
/*
	shader_.initShaders("C:\\Users\\Dinesh\\Documents\\Visual Studio 2015\\Projects\\spaceFighter\\Shader\\battlefield");
	shader_.enable();
	GLint tex;
	tex = glGetUniformLocation(shader_.getProg(), "tex"); //color - fragmentshader
	glUniform1i(tex, 0);
	
	GLint tex1;
	tex1 = glGetUniformLocation(shader_.getProg(), "tex1");  //height - vertexshader
	glUniform1i(tex1, 1);

	GLint tex2;
	tex2 = glGetUniformLocation(shader_.getProg(), "tex2"); //light	- fragmentshader
	glUniform1i(tex2, 2);
	shader_.disable();
	*/

}
void BattleField::loadArea1()
{
	
	tex_2D_Area1 = SOIL_load_OGL_texture
		(
			"C:\\Users\\Dinesh\\Documents\\Visual Studio 2015\\Projects\\spaceFighter\\IMAGES\\1.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	std::cout << "check battle field" << std::endl;
	if (tex_2D_Area1 == 0)
	{
		printf("SOIL loading error : '%s'\n", SOIL_last_result());
	}
}

void BattleField::loadArea2()
{
	tex_2D_Area2 = SOIL_load_OGL_texture("C:\\Users\\Dinesh\\Documents\\Visual Studio 2015\\Projects\\spaceFighter\\IMAGES\\field.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (tex_2D_Area2 == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}


	// Create vertex arrays
	 
void BattleField::Array()
{
	
	for (int z = -gridZ_; z < 0; z++)
	{
		for (int x = 0; x < gridX_; x++)
		{

			vertexArray_.push_back(glm::vec3((x-gridX_/2)*10,0,z*10));
			float tX = std::abs(float(x) / float(gridX_ - 1));
			float tZ = std::abs(float(z + gridZ_) / float(gridZ_ - 1));
			
			texCordArray_.push_back(glm::vec2(tX, tZ));

		}
	}
	//joining the 2d coordinate
	glPrimitiveRestartIndex(MAXINT);

	for (unsigned int t = 0; t < vertexArray_.size()-gridX_; t++)
	{
		arrayIndex.push_back(t);
		arrayIndex.push_back(t + gridX_);
		if (((t + 1) % gridX_) == 0)
			arrayIndex.push_back(MAXINT);
	}
	
}

void BattleField::Area1()
{

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2D_Area1);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, hMap);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lMap);
	glEnableClientState(GL_VERTEX_ARRAY); // enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]); // set vertex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, &texCordArray_[0]);
	glEnable(GL_PRIMITIVE_RESTART);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glDrawElements(GL_QUAD_STRIP, arrayIndex.size(), GL_UNSIGNED_INT, &arrayIndex[0]);
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays 
	glDisable(GL_PRIMITIVE_RESTART);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

}


void BattleField::Area2()
{

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2D_Area2);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, hMap);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lMap);
	glEnableClientState(GL_VERTEX_ARRAY); // enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]); // set vertex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, &texCordArray_[0]);
	glEnable(GL_PRIMITIVE_RESTART);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glDrawElements(GL_QUAD_STRIP, arrayIndex.size(), GL_UNSIGNED_INT, &arrayIndex[0]);
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays 
	glDisable(GL_PRIMITIVE_RESTART);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

}

void BattleField::loadHMap()
{
	hMap = SOIL_load_OGL_texture("C:\\Users\\Dinesh\\Documents\\Visual Studio 2015\\Projects\\spaceFighter\\IMAGES\\lightMap.bmp",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (hMap == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	
	}

}
void BattleField::loadLMap()
{
	lMap = SOIL_load_OGL_texture("C:\\Users\\Dinesh\\Documents\\Visual Studio 2015\\Projects\\spaceFighter\\IMAGES\\lightMapSea.bmp",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (lMap == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	
}

void BattleField::privateRender()
{		// Render the battlefield
	//shader_.enable();
	if (this->mode_ == 0)
	{
		Area1();

	}
	else if (this->mode_ == 1)
	{
		Area2();
	}
	//shader_.disable();
}

void BattleField::privateUpdate()
{
	pos_ += step_;
	if (pos_.z < gridZ_ * 10)
	{
//		matrix_ = glm::translate(matrix_, getStep());
	}
	else
	{
		pos_.z = -gridZ_ * 10.0f;
	//	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -gridZ_*20.0f));
	}
	
}
glm::vec3 BattleField::getPos() const
{
	return pos_;
}
glm::vec3 BattleField::getStep() const
{
	return step_;
}

