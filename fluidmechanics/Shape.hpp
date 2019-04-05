#pragma once

#include "SceneObject.hpp"

class Shape {

public:
	Shape(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texCoords = std::vector<glm::vec2>(), GLuint texID = 0, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f));
	~Shape();
	void render();

private:
	std::vector<glm::vec3> vertexArray_;
	std::vector<glm::vec3> normalArray_;
	std::vector<unsigned int> indexArray_;
	std::vector<glm::vec2> texCoords_;
	GLuint texID_;
	bool isTextured_;
	glm::vec3 color_;
};