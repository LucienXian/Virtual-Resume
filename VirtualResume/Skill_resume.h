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
		t = new TextRender();
		CreateResume();
		github="github:xxxxxxx";
		blog="blog:   xxxxxxxxx";
		mysql="MySQL   90%";
		operating_system="Linux    60%";
		java="Java    55%";
		python = "Python     70%";
		certificates = "Certificates :";
		certificate1="CET6";
		certificate2 = "CET4";
		profile="PROFILE";
		skills="Skills :";
	}
	virtual void draw_resume(Shader& shader) {

		t->shader.use();
		t->shader.setMat4("view", view);
		t->shader.setMat4("projection", projection);
		glm::mat4 model;
		model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(0, 1.0f, 0));
		t->shader.setMat4("model", model);

		t->draw(profile, 0.0f, 12.0f, -8.5f, 0.013f, glm::vec3(0.964706, 0.713726, 0.317647));
		t->draw(certificates, 0.0f, 7.2f, -9.1f, 0.011f, glm::vec3(0.509804, 1, 1));
		t->draw(certificate2, 0.0f, 6.3f, -7.5f, 0.008f, glm::vec3(0.509804, 1, 1));
		t->draw(certificate1, 0.0f, 5.5f, -7.5f, 0.008f, glm::vec3(0.509804, 1, 1));
		t->draw(skills, 0.0f, 8.2f, -4.5f, 0.010f, glm::vec3(0.509804, 1, 1));
		t->draw(github, 0.0f, 10.5f, -4.2f, 0.010f, glm::vec3(0.509804, 1, 1));
		t->draw(blog, 0.0f, 9.5f, -4.2f, 0.010f, glm::vec3(0.509804, 1, 1));
		t->draw(mysql, 0.0f, 7.62f, 4.4f, 0.008f, glm::vec3(1, 1, 1));
		t->draw(operating_system, 0.0f, 6.9f, 2.2f, 0.008f, glm::vec3(1, 1, 1));
		t->draw(java, 0.0f, 6.35f, 1.2f, 0.008f, glm::vec3(1, 1, 1));
		t->draw(python, 0.0f, 5.9f, 3.0f, 0.008f, glm::vec3(1, 1, 1));
		for (int i = 0; i < objs.size(); i++)
		{
			//cout << objs.size();
			glm::mat4 model;
			model = glm::translate(obj_model[i], _pos);
			model = glm::scale(model, _size);
			shader.use();
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
	string github;
	string blog;
	string mysql;
	string operating_system;
	string java;
	string python;
	string certificates;
	string certificate1;
	string certificate2;
	string profile;
	string skills;

	vector <Model>  objs;
	vector <glm::mat4> obj_model, text_model;
	vector <string> texts;
	//TextRender t;
	void CreateResume() {
		Model total = Model("model\\skills/skill1.obj");
		objs.push_back(total);
		glm::mat4 pos;
		obj_model.push_back(pos);
	}
	
};