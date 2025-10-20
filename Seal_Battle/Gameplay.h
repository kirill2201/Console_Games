#pragma once

#include <Queue>

#include "GameModule.h"
#include "Player.h"

//struct SavedGameplayData;

class Gameplay : public GameModule
{
private:
	Config config;
	EnGameTypes cur_gameplay_mode;
	EnPlayerModes player_game_mode;

	std::queue<std::string> other_game_messages;

	bool player_turn;
	std::shared_ptr<Player> ptr_player_1;
	std::shared_ptr<Player> ptr_player_2;

public:
	Gameplay(std::shared_ptr<Player> ptr_p1, std::shared_ptr<Player> ptr_p2, EnGameTypes gmp_code) : GameModule(EN_GAMEPLAY_CODE)
	{
		this->ptr_player_1 = ptr_p1;
		this->ptr_player_2 = ptr_p2;

		this->cur_gameplay_mode = gmp_code;
	}

	Gameplay(EnGameTypes gmp_code) : GameModule(EN_GAMEPLAY_CODE)
	{
		this->player_game_mode = EN_PLAYER_VS_PLAYER;

		this->player_turn = true;
		this->cur_gameplay_mode = gmp_code;
	}

	GameModuleData module_process(EnMenuOptions option) override;

	void print_info(EnPlayers p_turn, size_t row, size_t col);

	std::string give_player_name();

	void show_ai_menu(const std::vector<std::string>& options, size_t menu_options_sz, size_t ptr_idx);

	GameModuleData gameplay_start();

	GameModuleData middle_game();
	
	GameModuleData end_game(std::list<std::string>& game_messages);

	GameModuleData player_turn_fun(std::shared_ptr<Player> ptr_player, std::shared_ptr<Player> ptr_rival, Point& fire_point);

	GameModuleData gameplay_load();

	GameModuleData gameplay_continue_load();

	// new: accept saves produced by Game::load_game()
	//void set_saves(const std::vector<std::shared_ptr<SavedGameplayData>>& saves);

	const Config& get_config() const;
	EnGameTypes get_cur_gameplay_mode() const;
	EnPlayerModes get_player_game_mode() const;

	const std::shared_ptr<Player> get_ptr_player_1() const;
	const std::shared_ptr<Player> get_ptr_player_2() const;
};