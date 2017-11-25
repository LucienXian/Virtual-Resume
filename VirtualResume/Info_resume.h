#pragma once
#include "Resume.h"

class Info_resume : public Resumes {
public:
	Info_resume(glm::vec3 pos, glm::vec3 size):_pos(pos), _size(size){
		resume = Model("model\\info/info.obj");
	}
	virtual void draw_resume(Shader& shader) {
		resume.Draw(shader);
	}
	virtual void set_pos(glm::vec3 new_pos) {
		_pos = new_pos;
	}
	virtual void set_size(glm::vec3 new_size) {
		_size = new_size;
	}
private:
	glm::vec3 _pos;
	glm::vec3 _size;
	Model resume;
};