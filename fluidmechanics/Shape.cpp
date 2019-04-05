#include "Shape.hpp"

Shape::Shape(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals,
	std::vector<glm::vec2> texCoords, GLuint texID, glm::vec3 color) {

	vertexArray_ = vertices;
	indexArray_ = indices;
	normalArray_ = normals;
	texCoords_ = texCoords;
	texID_ = texID;
	color_ = color;

	isTextured_ = texCoords_.size() > 0;
}


Shape::~Shape() {

}


void Shape::render() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor3f(color_.x, color_.y, color_.z);

	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
	glNormalPointer(GL_FLOAT, 0, &normalArray_[0]);

	if (isTextured_)
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoords_[0]);

	glDrawElements(GL_TRIANGLES, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);
}
