#pragma once

#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

enum EnPlayers
{
	EN_PLAYER_1,
	EN_PLAYER_2
};

enum EnFieldPointType
{
	EN_EMPTY_POINT,
	EN_FIRED_POINT,
	EN_SHIP_POINT,
	EN_INTERVAL_ZONE,
	EN_DESTROY_COMPARTMENT
};

enum EnFireOptions
{
	EN_MISSED,
	EN_ERROR_COORDS,
	EN_HIT
};

enum EnSystemCode
{
	EN_RESET_CODE,
	EN_OK_CODE
};

enum EnGameModuleCodes
{
	EN_GAMEPLAY_CODE,
	EN_MENU_MANAGER_CODE,
	EN_EXIT_CODE
};

enum EnKeys
{
	EN_ENTER_KEY = 13,    // Enter (ASCII-код)
	EN_SPACE_KEY = 32,    // Пробел (ASCII-код)
	EN_ARROW_CODE = 224,
	EN_LEFT_KEY = 75,     // Стрелка влево (расширенный код после 224)
	EN_RIGHT_KEY = 77,    // Стрелка вправо (расширенный код после 224)
	EN_TOP_KEY = 72,      // Стрелка вверх (расширенный код после 224)
	EN_BOTTOM_KEY = 80,   // Стрелка вниз (расширенный код после 224)
	EN_ESC_KEY = 27,      // Esc (ASCII-код)
	EN_DELETE_KEY = 83    // Delete (расширенный код после 224)
};

enum EnMenuOptions
{
	EN_PM_CONTINUE,
	EN_PM_NEW_GAME,
	EN_SAVE_GAME,
	EN_PAUSE_GAME,
	EN_LOAD_GAME,
	EN_SETTINGS,
	EN_BACK_MAIN_MENU,
	EN_EXIT_GAME,
	EN_DIFFICULTY,
	EN_NONE_OPT
};

enum EnGameTypes
{
	EN_MAIN_MENU,
	EN_PAUSE_MENU,
	EN_SETTING_MENU,
	EN_LOAD_MENU,
	EN_START_GAMEPLAY,
	EN_PAUSE_GAMEPLAY,
	EN_LOAD_GAMEPLAY,
	EN_CONTINUE_GAMEPLAY
};

enum EnPlayerModes
{
	EN_PLAYER_VS_AI,
	EN_PLAYER_VS_PLAYER
};

class Config
{
public:
	static const size_t row_size = 10;
	static const size_t col_size = 10;
	static const size_t ship_names_count = 200;
	static const size_t crue_names_count = 4000;
	static const size_t ship_names_max = 200;
private:
	std::vector<std::string> ship_names;

	void get_ship_names_from_file()
	{
		size_t word_count = 0;
		std::string word;

		std::ifstream in_stream("ship_names.txt");

		if (in_stream.is_open())
		{
			do
			{
				in_stream >> word;

				if (word == " ") {
					continue;
				}

				ship_names.push_back(word.substr(1, word.size() - 2));
				word_count += 1;

			} while (word != "" && word_count < Config::ship_names_count);
		}
		in_stream.close();
	}

public:

	Config()
	{
		//srand(time(NULL));
		get_ship_names_from_file();

		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(ship_names.begin(), ship_names.end(), g);
	}

	const std::vector<std::string> get_ship_names() const
	{
		return this->ship_names;
	}
};