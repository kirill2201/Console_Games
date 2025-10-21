#pragma once

#include <stack>
#include <fstream>
#include "json.hpp"

#include "Gameplay.h"
#include "MenuManager.h"

using json = nlohmann::json;

struct SavedGameplayData
{
	Config config;
	EnGameTypes cur_gameplay_mode;

	std::shared_ptr<Player> p1_data;
	std::shared_ptr<Player> p2_data;
};

class Game
{
	std::vector<std::shared_ptr<SavedGameplayData>> saves;

	std::stack<std::shared_ptr<GameModule>> game_modules;

	std::shared_ptr<MenuManager> ptr_menu_manager;
	std::shared_ptr<Gameplay> ptr_gameplay;

	// Функция для центрирования текста
	void show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const
	{
		system("cls");

		for (size_t i = 0; i < sz_words; i++)
		{
			if (i == idx)
			{
				std::cout << "> ";
			}
			std::cout << words[i] << std::endl;
		}
	}

	void printCentered(const std::vector<std::string>& art);

	void logo_show();

	void save_player_data(const std::shared_ptr<Player>& ptr_player, std::shared_ptr<GameField>& ptr_player_field, std::shared_ptr<Fleet>& ptr_player_fleet,
		std::map<Point, std::shared_ptr<Ship>>& player_point_to_ship_dict, size_t& player_id, size_t& player_point_count, std::string& player_name, bool& player_cur_state);

	void save_fleet_data(std::shared_ptr<Fleet>& ptr_player_fleet, std::vector<std::shared_ptr<Ship>>& fleet,
		std::vector<std::shared_ptr<Ship>>& wasted_ships, size_t& size_def_fleet, size_t& size_oper_fleet, size_t& size_wasted_fleet);

	void save_game();

	GameModuleData load_game();
public:
	Game()
	{

	}

	void game_process();
};