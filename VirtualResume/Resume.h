#pragma once
#include "model.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Resumes {
public:
	Resumes(){}
	virtual void draw_resume(Shader& shader) = 0;
	virtual void set_pos(glm::vec3) = 0;
	virtual void set_size(glm::vec3) = 0;
};