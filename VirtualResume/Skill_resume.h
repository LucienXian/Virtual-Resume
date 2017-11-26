#pragma once
#include "Resume.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include "TextRender.h"
class Skill_resume : public Resumes {
public:
	Skill_resume(glm::vec3 pos, glm::vec3 size) :_pos(pos), _size(size) {
		CreateResume();
	}
	virtual void draw_resume(Shader& shader) {

		for (int i = 0; i < objs.size(); i++)
		{
			//cout << objs.size();
			glm::mat4 model;
			model = glm::translate(obj_model[i], _pos);
			model = glm::scale(model, _size);
			shader.setMat4("model", model);
			objs[i].Draw(shader);
		}
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


	vector <Model>  objs;
	vector <glm::mat4> obj_model, text_model;
	vector <string> texts;
	//TextRender t;
	void CreateResume() {
		Model total = Model("model\\skills/skill.obj");
		objs.push_back(total);
		glm::mat4 pos;
		obj_model.push_back(pos);
	}
	
};