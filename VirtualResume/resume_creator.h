#pragma once
#include "Resume.h"
#include "Info_resume.h"
#include <unordered_map>
#include <vector>

class Resume_creator
{
public:
	Resume_creator(std::vector<glm::vec3> pos, std::vector<glm::vec3> r_size, int numResume):
		_pos(pos), _r_size(r_size), num_resume(numResume){
		for (int i = 0; i < num_resume; i++) {
			resume_table[i] = generateResume(i);
		}
	}
	virtual ~Resume_creator() {
		for (int i = 0; i < num_resume; i++) {
			delete resume_table[i];
		}
	}
	void show_resume(int id, Shader& shader) {
		glm::mat4 model;
		model = glm::translate(model, _pos[id]);
		model = glm::scale(model, _r_size[id]);
		shader.setMat4("model", model);
		resume_table[id]->draw_resume(shader);
	}

private:
	int num_resume;
	unordered_map<int, Resumes*> resume_table;
	std::vector<glm::vec3> _pos;
	std::vector<glm::vec3> _r_size;
	Resumes* generateResume(int id) {
		switch (id)
		{
		case 0:
			return new Info_resume(_pos[id], _r_size[id]);
			break;
		default:
			return NULL;
			break;
		}
	}
};
