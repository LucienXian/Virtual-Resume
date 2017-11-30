#pragma once
#include "Resume.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "TextRender.h"
class Info_resume : public Resumes {
public:
	Info_resume(glm::vec3 pos, glm::vec3 size, unordered_map<string, string> input):_pos(pos), _size(size),
				resume_text(input){
		t = new TextRender();
		title = "Basic infomation";
		introduction = "INTRODUCTION";
		//text1 = "balabalaasdfasdfasdf 1";
		text1 = this->resume_text["text1"];
		//text2 = "balabalasdafasdfaf 2";
		text2 = this->resume_text["text2"];
		//text3 = "balabalaasdfdsfasdf 3";
		text3 = this->resume_text["text3"];
		hobby = "Hobbies";
		//hobby1 = "hobby1";
		hobby1 = this->resume_text["hobby1"];
		//hobby2 = "hobby2";
		hobby2 = this->resume_text["hobby2"];
		//hobby3 = "hobby3";
		hobby3 = this->resume_text["hobby3"];
		//hobby4 = "hobby4";
		hobby4 = this->resume_text["hobby4"];
		//hobby5 = "hobby5";
		hobby5 = this->resume_text["hobby5"];
		//hobby6 = "hobby6";
		hobby6 = this->resume_text["hobby6"];
		name = "Name";
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
		
		t->shader.use();
		t->shader.setMat4("view", view);
		t->shader.setMat4("projection", projection);
		glm::mat4 model;
		model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(0, 1.0f, 0));
		t->shader.setMat4("model", model);
		t->draw(title, 0.0f, 12.0f, -9.3f, 0.028f, glm::vec3(0.960784, 0.490196, 0.101961));
		t->draw(introduction, 0.0f, 10.6f, -9.2f, 0.010f, glm::vec3(0.0745098, 0.705882, 0.643137));
		t->draw(text1, 0.0f, 9.5f, -9.0f, 0.009f, glm::vec3(1.0f, 1.0f, 1.0f));
		t->draw(text2, 0.0f, 8.5f, -9.0f, 0.009f, glm::vec3(1.0f, 1.0f, 1.0f));
		t->draw(text3, 0.0f, 7.5f, -9.0f, 0.009f, glm::vec3(1.0f, 1.0f, 1.0f));
		t->draw(hobby, 0.0f, 9.3f, -1.5f, 0.015f, glm::vec3(1.0f, 1.0f, 1.0f));
		t->draw(hobby1, 0.0f, 7.8f, -3.0f, 0.013f, glm::vec3(0.0f, 1.0f, 1.0f));
		t->draw(hobby2, 0.0f, 7.8f, -0.0f, 0.013f, glm::vec3(0.0f, 1.0f, 1.0f));
		t->draw(hobby3, 0.0f, 6.3f, -3.0f, 0.013f, glm::vec3(0.0f, 1.0f, 1.0f));
		t->draw(hobby4, 0.0f, 6.3f, -0.0f, 0.013f, glm::vec3(0.0f, 1.0f, 1.0f));
		t->draw(hobby5, 0.0f, 4.8f, -3.0f, 0.013f, glm::vec3(0.0f, 1.0f, 1.0f));
		t->draw(hobby6, 0.0f, 4.8f, -0.0f, 0.013f, glm::vec3(0.0f, 1.0f, 1.0f));
		t->draw(name, 0.0f, 7.8f, 5.2f, 0.015f, glm::vec3(0.0f, 1.0f, 1.0f));
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
	string title;
	string info;
	string introduction;
	string text1;
	string text2;
	string text3;
	string hobby;
	string hobby1, hobby2, hobby3, hobby4, hobby5, hobby6;
	string name;
	//TextRender t;
	void CreateResume() {
		Model total = Model("model\\info/info1.obj");
		objs.push_back(total);
		glm::mat4 pos;
		obj_model.push_back(pos);
	}
	
};