#define TINYOBJLOADER_IMPLEMENTATION
#include "Model.hpp"
#include"SOIL.h"
#include<iostream>
#include<stdlib.h>
#include "glm/glm/gtc/matrix_transform.hpp"

Model::Model(std::string folder, std::string fileName, bool rotate, glm::vec3 offset) {
	if (fileName.empty())
		inputfile_ = baseFolderPath_ + "cube.obj";
	else if (folder.empty())
		inputfile_ = baseFolderPath_ + fileName;
	else
		inputfile_ = baseFolderPath_ + folder + fileName;

	modelFolderPath_ = baseFolderPath_ + folder;

	matrix_ = glm::translate(matrix_, offset);

	rotate_ = rotate;

	initialized_ = false;
	//privateInit();
	loadModel();
}


Model::~Model() {

}


void Model::privateInit() {
	
}


void Model::privateRender() {

	
	glDisable(GL_CULL_FACE);
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	for each (auto shape in shapes_) {
		shape->render();
	}

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glEnable(GL_CULL_FACE);
}


void Model::privateUpdate() {
	if (rotate_)
		matrix_ = glm::rotate_slow(matrix_, 0.01f, glm::vec3(0.f, 1.f, 0.f));


}


void Model::loadModel() {


	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	//const std::string path = "D:\\fluidNsimulation\\FluidMechanics\\fluidSimulation\\gfx\\";
	//const std::string modelPath = path + "lifeboat.obj";
	bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile_.c_str(), modelFolderPath_.c_str());


	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}
	
	if (!ret) {
		exit(1);
	}
	std::map <std::string, GLuint> texPaths;

	
	for (size_t i = 0; i < shapes.size(); i++) {

		std::vector<unsigned int> indexArray;
		std::vector<glm::vec3> vertexArray;
		std::vector<glm::vec3> normalArray;
		std::vector<glm::vec2> texCoords;

		auto currentShape = shapes[i];

		indexArray.clear();
		vertexArray.clear();
		normalArray.clear();
		texCoords.clear();

		assert((currentShape.mesh.indices.size() % 3) == 0);

		unsigned int i1 = 0;
		unsigned int i2 = 0;
		unsigned int i3 = 0;

		for (size_t f = 0; f < currentShape.mesh.indices.size() / 3; f++) {

			i1 = currentShape.mesh.indices[3 * f + 0];
			i2 = currentShape.mesh.indices[3 * f + 1];
			i3 = currentShape.mesh.indices[3 * f + 2];

			indexArray.push_back(i1);
			indexArray.push_back(i2);
			indexArray.push_back(i3);
		}

		assert((currentShape.mesh.positions.size() % 3) == 0);

		for (size_t v = 0; v < currentShape.mesh.positions.size() / 3; v++) {

			vertexArray.push_back(glm::vec3(currentShape.mesh.positions[3 * v + 0],
				currentShape.mesh.positions[3 * v + 1], currentShape.mesh.positions[3 * v + 2]));
		}


		assert((currentShape.mesh.normals.size() % 3) == 0);

		for (size_t v = 0; v < currentShape.mesh.normals.size() / 3; v++) {

			normalArray.push_back(glm::vec3(currentShape.mesh.normals[3 * v + 0], currentShape.mesh.normals[3 * v + 1], currentShape.mesh.normals[3 * v + 2]));
		}

		// Calculate normals http://forum.devmaster.net/t/calculating-normals-of-a-mesh/6065/5 25/5-16
		if (normalArray.empty()) {

			normalArray = std::vector<glm::vec3>(vertexArray.size(), glm::vec3(0, 0, 0));

			for (unsigned int i = 0; i < indexArray.size(); i += 3) {

				auto p1 = vertexArray[indexArray[i + 0]];
				auto p2 = vertexArray[indexArray[i + 1]];
				auto p3 = vertexArray[indexArray[i + 2]];

				glm::vec3 v1 = p2 - p1;
				glm::vec3 v2 = p3 - p1;

				glm::vec3 v3 = p3 - p2;
				glm::vec3 v4 = p1 - p2;

				glm::vec3 v5 = p1 - p3;
				glm::vec3 v6 = p2 - p3;

				glm::vec3 normal = glm::cross(v1, v2);

				normalArray[indexArray[i + 0]] += normal;
				normalArray[indexArray[i + 1]] += normal;
				normalArray[indexArray[i + 2]] += normal;
			}

			for each (auto n in normalArray) {
				n = glm::normalize(n);
			}
		}


		assert((currentShape.mesh.texcoords.size() % 2) == 0);

		for (size_t t = 0; t < currentShape.mesh.texcoords.size() / 2; t++) {

			texCoords.push_back(glm::vec2(currentShape.mesh.texcoords[2 * t + 0], currentShape.mesh.texcoords[2 * t + 1]));
		}

		// Load materials

		GLuint texID = 0;
		glm::vec3 color;

		if (currentShape.mesh.material_ids.size() > 0) {

			int currentMatID = currentShape.mesh.material_ids[0];

			if (materials.size() > 0) {

				if (currentMatID < materials.size()) {

					auto c = materials[currentMatID].diffuse;
					color = glm::vec3(c[0], c[1], c[2]);


					// NB: check for dupe textures
					if (!(materials[currentMatID].diffuse_texname).empty()) {

						std::string textureFile = modelFolderPath_ + materials[currentMatID].diffuse_texname;

						if (texPaths.find(textureFile) == texPaths.end()) {
							
							//std::cout << "Loading texture " << textureFile << std::endl;

							texID = SOIL_load_OGL_texture
								(
								textureFile.c_str(),
								SOIL_LOAD_AUTO,
								SOIL_CREATE_NEW_ID,
								SOIL_FLAG_INVERT_Y
								);

							if (texID == 0)
								
								std::cerr << "SOIL loading error:" << SOIL_last_result() << std::endl;
							else
								texPaths.insert(std::pair<std::string, GLuint>(textureFile, texID));
						}
						else {

							texID = texPaths[textureFile];
						}
					}
				}
			}
		}

		auto shape = std::make_shared<Shape>(vertexArray, indexArray, normalArray, texCoords, texID, color);
		shapes_.push_back(shape);
	}

	int g = 5;


}
