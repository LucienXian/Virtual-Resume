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
		expected1 = "Expected job";
		//job = "Manager";
		job = this->resume_text["job"];
		expected2 = "Expected industry";
		//industry = "Internet";
		industry = this->resume_text["industry"];
		expected3 = "Expected place";
		//place = "Hangzhou";
		place = this->resume_text["place"];
		expected4 = "Expected salary";
		//salary = "15K -- 20K";
		salary = this->resume_text["salary"];
		CreateResume();
	}
	virtual void draw_resume(Shader& shader) {

		for (int i = 0; i < objs.size(); i++)
		{
			//cout << objs.size();
			glm::mat4 model;
			model = glm::translate(obj_model[i], _pos);
			switch (i)
			{
			case 0: break;
			case 1: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					break;	
			case 2: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					model = glm::rotate(model, (float)(0.5*glfwGetTime()), glm::vec3(0, 1.0, 0));
					break;
			case 3: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
				    model = glm::rotate(model, (float)(-1*glfwGetTime()), glm::vec3(0, 1.0, 0));
				    break;
			case 4: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					break;
			case 5: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					model = glm::rotate(model, (float)(-0.15*glfwGetTime()), glm::vec3(0, 1.0, 0));
					break;
			case 6: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					model = glm::rotate(model, (float)(0.3*glfwGetTime()), glm::vec3(0, 1.0, 0));
					break;
			case 7: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					model = glm::rotate(model, (float)(2*glfwGetTime()), glm::vec3(0, 1.0, 0));
					break;
			case 8: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					break;
			case 9: model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					model = glm::rotate(model, (float)(0.3*glfwGetTime()), glm::vec3(0, 1.0, 0));
					break;
			case 10:model = glm::rotate(model, (float)glm::radians(15.0), glm::vec3(0.0, 0.0, 1.0));
					break;
			default:
				break;
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
		t->draw(expected1, 0.0f, 10.2f, 5.5f, 0.013f, glm::vec3(1,1,1));
		t->draw(job, 0.0f, 10.2f, 1.7f, 0.01f, glm::vec3(0.552941, 0.811765, 0.94902));
		t->draw(expected2, 0.0f, 8.9f, 5.5f, 0.013f, glm::vec3(1, 1, 1));
		t->draw(industry, 0.0f, 8.9f, 1.7f, 0.01f, glm::vec3(0.552941, 0.811765, 0.94902));
		t->draw(expected3, 0.0f, 7.6f, 5.5f, 0.013f, glm::vec3(1, 1, 1));
		t->draw(place, 0.0f, 7.7f, 1.7f, 0.01f, glm::vec3(0.552941, 0.811765, 0.94902));
		t->draw(expected4, 0.0f, 6.3f, 5.5f, 0.013f, glm::vec3(1, 1, 1));
		t->draw(salary, 0.0f, 6.3f, 1.7f, 0.01f, glm::vec3(0.552941, 0.811765, 0.94902));

	}
	virtual void set_pos(glm::vec3 new_pos) {
		_pos = new_pos;
	}
	virtual void set_size(glm::vec3 new_size) {
		_size = new_size;
	}
	virtual void set_text(unordered_map<string, string> input) {
		this->resume_text = input;
	}
private:
	unordered_map<string, string> resume_text;
	glm::vec3 _pos;
	glm::vec3 _size;
	string expected1;
	string job;
	string expected2;
	string industry;
	string expected3;
	string place;
	string expected4;
	string salary;
	//TextRender t;
	void CreateResume() {
		Model text = Model("model\\job_intention/text.obj");
		Model fifth = Model("model\\job_intention/fifth.obj");
		Model fifth_1 = Model("model\\job_intention/fifth_1.obj");
		Model fifth_2 = Model("model\\job_intention/fifth_2.obj");
		Model fourth = Model("model\\job_intention/fourth.obj");
		Model third = Model("model\\job_intention/third.obj");
		Model second = Model("model\\job_intention/second.obj");
		Model first = Model("model\\job_intention/first.obj");
		Model fourth_1= Model("model\\job_intention/3_circle1.obj");
		Model fourth_2 = Model("model\\job_intention/3_circle2.obj");
		Model fourth_line = Model("model\\job_intention/3_line.obj");
		objs.push_back(text);
		objs.push_back(fifth);
		objs.push_back(fifth_1);
		objs.push_back(fifth_2);
		objs.push_back(fourth);
		objs.push_back(fourth_1);
		objs.push_back(fourth_2);
		objs.push_back(fourth_line);
		objs.push_back(third);
		objs.push_back(second);
		objs.push_back(first);


		glm::mat4 pos;
		obj_model.push_back(pos);
		glm::mat4 poscircle;
		poscircle = glm::translate(poscircle, glm::vec3(0.0, 0.0, -6.8));

		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);

		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);

		obj_model.push_back(poscircle);
		obj_model.push_back(poscircle);
	}

};