#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


class Parser final{
	private:
		std::ifstream file;
		std::vector<std::string> code{};
		std::vector<std::string> map_keys{};
		std::map<std::string, std::string> object_variables{ {} };
		
		size_t index = -1, ObjectIndex, BracketIndex, LastBracketIndex, VariableIndex, CONTENT_FLAG, pos_separator, ERROR_FLAG;
		std::string line{};
		size_t pos{};

	public:
		void FileParse(std::string sFile);
		void Reparse(std::string sFile);
		std::string GetVarValue(std::string VarName);
		void GetVariablesFromObject(std::string ObjectName);
};
