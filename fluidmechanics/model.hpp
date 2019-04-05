#pragma once
#include "SceneObject.hpp"
#include "../tinyobjloader/tiny_obj_loader.h"
#include"glm\glm\matrix.hpp"

#include "Shader.hpp"
#include "Shape.hpp"

#include <thread>

class Model : public SceneObject {

public:
	Model(std::string folder, std::string fileName, bool rotate, glm::vec3 offset = glm::vec3(0.f, 0.f, 0.f));
	~Model();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	bool initialized_;

	void loadModel();

	std::vector<std::shared_ptr<Shape>> shapes_;

	std::string inputfile_;
	const std::string baseFolderPath_ = "D:\\fluidNsimulation\\FluidMechanics\\fluidSimulation\\";
	std::string modelFolderPath_;
	

	bool rotate_;

	std::shared_ptr<Shader> shader_;
};
