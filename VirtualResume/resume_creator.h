#pragma once
#include "Resume.h"
#include "Info_resume.h"
#include "Skill_resume.h"
#include "Job_intention_resume.h"
#include <unordered_map>
#include <vector>
#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_iterators.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"
#include "rapidxml-1.13\rapidxml_utils.hpp"

class Resume_creator
{
public:
	Resume_creator(std::vector<glm::vec3> pos, std::vector<glm::vec3> r_size, int numResume):
		_pos(pos), _r_size(r_size), num_resume(numResume){
		rapidxml::file<> fdoc("Resume.xml");
		rapidxml::xml_document<> doc;
		doc.parse<0>(fdoc.data());
		this->xml_root = doc.first_node();
		//initText();
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
	rapidxml::xml_node<>* xml_root;
	Resumes* generateResume(int id) {	
		switch (id)
		{
		case 0: return new Info_resume(_pos[id], _r_size[id], getXmlInfo(id));
		case 1: return new Skill_resume(_pos[id], _r_size[id]);
		case 2: return new Job_intention_resume(_pos[id], _r_size[id]);
		default:
			break;
		}	
	}
	void initText() {
		rapidxml::file<> fdoc("Resume.xml");
		rapidxml::xml_document<> doc;
		doc.parse<0>(fdoc.data());
		this->xml_root = doc.first_node();
		
	}
	unordered_map<string, string> parseXml(string item) {
		unordered_map<string, string> res;
		rapidxml::xml_node<>* resume_node = this->xml_root->first_node(item.c_str());
		
		for (rapidxml::xml_node<> *i = resume_node->first_node();
			i; i = i->next_sibling()) {
			res[i->name()] = i->value();
		}
		return res;
	}
	unordered_map<string, string> getXmlInfo(int id) {
		switch (id)
		{
		case 0:
			return parseXml("Info");
		case 1:
			return parseXml("Skill");
		case 2:
			return parseXml("Job_intention");
		default:
			break;
		}
	}
};
