#pragma once
#include "Resume.h"
#include "Info_resume.h"
#include "Skill_resume.h"
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
		resume_table[id]->draw_resume(shader);
	}
	void setmat4(glm::mat4 view, glm::mat4 projection)
	{
		for (int i = 0; i < num_resume; i++) {
			resume_table[i]->setmat4(view, projection);
		}
	}
private:
	int num_resume;
	unordered_map<int, Resumes*> resume_table;
	std::vector<glm::vec3> _pos;
	std::vector<glm::vec3> _r_size;
	glm::mat4 view;
	glm::mat4 projection;
	Resumes* generateResume(int id) {	
		switch (id)
		{
		case 0: return new Info_resume(_pos[id], _r_size[id]);
		case 1: return new Skill_resume(_pos[id], _r_size[id]);
		default:
			break;
		}
		
	}
};
