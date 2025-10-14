#pragma once
#include <string>
#include <sstream>

#include "..\Tik_Tak_Toe\Exceptions.h"

enum en_Player_Type { None_Player_Type = -1, H_player, AI_player };
enum en_AI_dif_levels { ai_min_level, ai_mid_level, ai_max_level };
enum en_field_sizes { field_min_size = 3, field_max_size = 9 };

class Field;

class Config
{
public:

	static bool isInteger(const std::string& str);

	static void read_2_nums(int& i, int& j);

	static bool check_coord_size(Field* field_ptr, int coord);

	static bool check_field_pos(Field* field_ptr, int i, int j);
};