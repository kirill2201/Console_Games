#include "Config.h"
#include "Field.h"

bool Config::isInteger(const std::string& str)
{
	std::istringstream iss(str);
	int x;

	iss >> std::ws;
	if (!(iss >> x)) return false;
	iss >> std::ws;

	return iss.eof();
}

void Config::read_2_nums(int& i, int& j)
{
	std::string input;

	std::getline(std::cin, input);

	std::istringstream iss(input);

	if (iss >> i >> j && iss.eof()) {}
	else {
		throw ExceptionErrorInt("[Error msg] ExceptionInt i and j should be numbers");
	}
}

bool Config::check_coord_size(Field* field_ptr, int coord)
{
	if (coord < 0 || coord > field_ptr->get_field_size())
		return false;

	return true;
}

bool Config::check_field_pos(Field* field_ptr, int i, int j)
{
	if ((*field_ptr)[i][j] != '#')
		return false;

	return true;
}