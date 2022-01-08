#include "parser.h"


int main()
{
	Parser fileparse;

	fileparse.FileParse("script.jtgs");
	fileparse.GetVariablesFromObject("ObjectName");

	std::cout << "VALUE:"  << fileparse.GetVarValue("variable") << "\n";

	return 0;
}