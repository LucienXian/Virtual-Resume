#pragma once
#include "model.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TextRender.h"
class Resumes {
public:
	Resumes(){}
	virtual void draw_resume(Shader& shader) = 0;
	virtual void set_pos(glm::vec3) = 0;
	virtual void set_size(glm::vec3) = 0;
	void setmat4(glm::mat4 view, glm::mat4 projection)
	{
		this->projection = projection;
		this->view = view;
	}
protected:
	glm::mat4 view;
	glm::mat4 projection;
	vector <Model>  objs;
	vector <glm::mat4> obj_model;
	TextRender *t;
};