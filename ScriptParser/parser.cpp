#define SPACE_CHAR " "
#define TAB_CHAR "\t"
#define NLINE_CHAR "\n"

#include "parser.h"

void Parser::FileParse(std::string sFile)
{
	if (file.open(sFile), !file.good())
	{
		std::cout << "Something wrong with file" << '\n';
		file.close();
	}
	else {
		while(getline(file, line), line != SPACE_CHAR && line != TAB_CHAR && line != NLINE_CHAR)
		{
			code.emplace_back(line);

			if (file.eof()) {
				break;
			}

		}
	}

	line = "";
	pos = 0;

}

void Parser::Reparse(std::string sFile)
{
	file.close();
	code.clear();
	Parser::FileParse(sFile);
}

std::string Parser::GetVarValue(std::string VarName)
{
	return object_variables[VarName];
}

void Parser::GetVariablesFromObject(std::string ObjectName)
{
	object_variables.clear();
	for (const auto& val : code) {
		index++;
		if (pos = val.find("[" + ObjectName + "]"), pos != std::string::npos)
		{
			ObjectIndex = index;
			std::cout <<"Found object: " << val << " at " << ObjectIndex << "\n";
			for (size_t i = ObjectIndex; i < code.size(); i++) {
				if (code[i].find("{") != std::string::npos)
				{
					index++;
					BracketIndex = index;
					std::cout << "Found first bracket: " << code[i] << " at " << BracketIndex << "\n";
					CONTENT_FLAG = 1;
					break;
				}
				else {
					CONTENT_FLAG = 0;
				}
			}

			if (CONTENT_FLAG != 0)
			{
				for (size_t i = BracketIndex; i < code.size(); i++) {
					if (pos_separator = code[i].find(":"), pos_separator != std::string::npos)
					{
						index++;
						VariableIndex = index;
						std::string var_name = code[i].substr(0, pos_separator);
						std::string var_value = code[i].substr(pos_separator+1, code[i].size());
						var_name.erase(std::remove(var_name.begin(), var_name.end(), '\t'), var_name.end());
						var_name.erase(std::remove(var_name.begin(), var_name.end(), ' '), var_name.end());
						var_value.erase(std::remove(var_value.begin(), var_value.end(), '\t'), var_value.end());
						var_value.erase(std::remove(var_value.begin(), var_value.end(), ' '), var_value.end());
						var_value.erase(std::remove(var_value.begin(), var_value.end(), '\"'), var_value.end());
						var_value.erase(std::remove(var_value.begin(), var_value.end(), '\''), var_value.end());
						std::cout << "Found " << VariableIndex << " variable: " << " at " << VariableIndex << "\n";
						std::cout << "With name:" << var_name << "\n";
						std::cout << "And Value:" << var_value << "\n";
						object_variables.insert(std::pair <std::string, std::string> (var_name, var_value));

					}
					if (code[i].find("}") != std::string::npos)
					{
						break;
					}
				}
			}
			break;
		}

	}

	if (object_variables.size() > 0) {
		for (const auto& [key, _] : object_variables) 
		{
			map_keys.emplace_back(key);
		}
	}

	if (CONTENT_FLAG == 0)
	{
		std::cout << "SYNTAX ERROR AT: " << index << "\n";
		file.close();
		code.clear();
		object_variables.clear();
		line = "";
		pos = 0;
	}

	index = 0;
	
}