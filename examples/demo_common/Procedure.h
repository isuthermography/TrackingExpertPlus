#pragma once

#include <string>
#include <unordered_map>

#include "ModelOBJ.h"

typedef struct Step
{
	std::vector<std::string> prereqs;
	std::string model_name;
	glm::vec3 trans, rot;
	bool completed;

	Step()
	{
		prereqs = std::vector<std::string>();
		model_name = "null";
		trans = glm::vec3(0.0, 0.0, 0.0);
		rot = glm::vec3(0.0, 0.0, 0.0);
		completed = false;
	}

	Step(std::vector<std::string> _prereqs, std::string _model,
		glm::vec3 _trans, glm::vec3 _rot)
	{
		prereqs = _prereqs;
		model_name = _model;
		trans = _trans;
		rot = _rot;
		completed = false;
	}
};

typedef struct Procedure
{
	std::string name;
	std::unordered_map<std::string, cs557::OBJModel>* _models;
	std::unordered_map<std::string, Step> _steps;
	std::vector<Procedure> _subprocs;

	Procedure()
	{
		name = "null";
		_models = new std::unordered_map<std::string, cs557::OBJModel>();
		_steps = std::unordered_map<std::string, Step>();
		_subprocs = std::vector<Procedure>();
	}
};