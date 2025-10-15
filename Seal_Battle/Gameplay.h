#pragma once

#include "GameModule.h"
#include "Player.h"

class Gameplay : public GameModule
{
private:
	Config config;
	EnGameTypes cur_gameplay_mode;
	EnPlayerModes player_game_mode;

	bool player_turn;
	std::shared_ptr<Player> ptr_player_1;
	std::shared_ptr<Player> ptr_player_2;

public:
	Gameplay(EnGameTypes gmp_code, const Player& player_1, const Player& player_2) : GameModule(EN_GAMEPLAY_CODE)
	{
		this->player_turn = true;
		this->cur_gameplay_mode = gmp_code;
		this->player_game_mode = EN_PLAYER_VS_PLAYER;

		ptr_player_1 = std::make_shared<Player>(player_1);
		ptr_player_2 = std::make_shared<Player>(player_2);

		middle_game();
	}

	Gameplay(EnGameTypes gmp_code) : GameModule(EN_GAMEPLAY_CODE)
	{
		this->player_game_mode = EN_PLAYER_VS_PLAYER; // !!! поправить позже

		this->player_turn = true;
		this->cur_gameplay_mode = gmp_code;
	}

	GameModuleData module_process(EnMenuOptions option) override;

	void print_info(EnPlayers p_turn);

	std::string give_player_name();

	GameModuleData gameplay_start();

	GameModuleData middle_game();

	GameModuleData player_turn_fun(std::shared_ptr<Player> ptr_player, std::shared_ptr<Player> ptr_rival);

	GameModuleData end_game();

	GameModuleData gameplay_load();

	GameModuleData gameplay_continue_load();

	const Config& get_config() const;
	EnGameTypes get_cur_gameplay_mode() const;
	EnPlayerModes get_player_game_mode() const;

	const std::shared_ptr<Player> get_ptr_player_1() const;
	const std::shared_ptr<Player> get_ptr_player_2() const;
};