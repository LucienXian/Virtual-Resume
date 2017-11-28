#pragma once
#include "Resume.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include "TextRender.h"
class Job_intention_resume : public Resumes {
public:
	Job_intention_resume(glm::vec3 pos, glm::vec3 size) :_pos(pos), _size(size) {
		t = new TextRender();

		CreateResume();
	}
	virtual void draw_resume(Shader& shader) {

		for (int i = 0; i < objs.size(); i++)
		{
			//cout << objs.size();
			glm::mat4 model;
			model = glm::translate(obj_model[i], _pos);
			if (i > 0) {
				model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
				model = glm::rotate(model, (float)(0.1*glfwGetTime()), glm::vec3(0, 1.0, 0));
			}
			
			model = glm::scale(model, _size);
			shader.setMat4("model", model);
			objs[i].Draw(shader);
		}

		t->shader.use();
		t->shader.setMat4("view", view);
		t->shader.setMat4("projection", projection);
		glm::mat4 model;
		model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(0, 1.0f, 0));
		t->shader.setMat4("model", model);

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

	//TextRender t;
	void CreateResume() {
		Model text = Model("model\\job_intention/text.obj");
		Model fifth = Model("model\\job_intention/fifth.obj");
		Model fourth = Model("model\\job_intention/fourth.obj");
		objs.push_back(text);
		objs.push_back(fifth);
		objs.push_back(fourth);


		glm::mat4 pos;
		obj_model.push_back(pos);
		glm::mat4 poscircle;
		poscircle = glm::translate(poscircle, glm::vec3(0.0, 0.0, -7.3));
		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);
	}

};