#pragma once

#include <stack>
#include <fstream>
#include "json.hpp"

#include "Gameplay.h"
#include "MenuManager.h"

using json = nlohmann::json;

// Вспомогательные функции для конвертации enum'ов в строки
//
//std::string enGameTypesToString(EnGameTypes mode) {
//	switch (mode) {
//	case 	EN_MAIN_MENU:
//		return "EN_MAIN_MENU";
//	case EN_PAUSE_MENU:
//		return "EN_PAUSE_MENU";
//	case EN_SETTING_MENU:
//		return "EN_SETTING_MENU";
//	case EN_LOAD_MENU:
//		return "EN_LOAD_MENU";
//	case EN_START_GAMEPLAY:
//		return "EN_START_GAMEPLAY";
//	case EN_PAUSE_GAMEPLAY:
//		return "EN_PAUSE_GAMEPLAY";
//	case EN_LOAD_GAMEPLAY:
//		return "EN_LOAD_GAMEPLAY";
//
//	default: return "Unknown";
//	}
//}
//
//std::string enPlayerModesToString(EnPlayerModes mode) {
//	switch (mode) {
//	case EN_PLAYER_VS_PLAYER: return "PlayerVsPlayer";
//	case EN_PLAYER_VS_AI: return "PlayerVsAI";
//	default: return "Unknown";
//	}
//}
//
//std::string enShipTypeToString(EnShipType type) {
//	switch (type) {
//	case EN_BATTLESHIP: return "EN_BATTLESHIP";
//	case EN_CRUISER: return "EN_CRUISER";
//	case EN_DESTROYER: return "EN_DESTROYER";
//	case EN_TORPEDO_BOAT: return "EN_TORPEDO_BOAT";
//	default: return "EN_UNKNOWN";
//	}
//}
//
//std::string enFieldPointTypeToString(EnFieldPointType type) {
//	switch (type) {
//	case EN_EMPTY_POINT: return "EN_EMPTY_POINT";
//	case EN_FIRED_POINT: return "EN_FIRED_POINT";
//	case EN_SHIP_POINT: return "EN_SHIP_POINT";
//	case EN_INTERVAL_ZONE: return "EN_INTERVAL_ZONE";
//	default: return "EN_UNKNOWN";
//	}
//}
//
//std::string enShipCompartmentTypeToString(EnShipCompartmentType type) {
//	switch (type) {
//	case EN_BOW: return "EN_BOW";
//	case EN_MIDDLE: return "EN_MIDDLE";
//	case EN_STERN: return "EN_STERN";
//	default: return "EN_UNKNOWN";
//	}
//}

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

	void load_game();
public:
	Game()
	{

	}

	void game_process();
};