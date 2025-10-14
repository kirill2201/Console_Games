#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include "..\Tik_Tak_Toe\Field.h"
#include "..\Tik_Tak_Toe\Player.h"
#include "..\Tik_Tak_Toe\Config.h"

class Gameplay
{
private:
	enum en_Gameplay_State { Null_State = -1, Start_State, Game_State, End_State };
	enum en_Gameplay_Type { None_Gmp_Type = -1, P_vs_P, P_vs_AI };

	Field* field_ptr{ nullptr };
	Player* player_1_ptr{ nullptr };
	Player* player_2_ptr{ nullptr };

	en_Gameplay_State game_state{ Null_State };
	en_Gameplay_Type gmp_type{ None_Gmp_Type };

	int get_ui_size() const;

	void create_a_field();

	en_Gameplay_Type take_a_type();

	char take_a_sign() const;

	void delete_old_data();

	en_AI_dif_levels get_dif_level();

	void create_players();

	void gameplay_state();

	void game_process();

	bool finish_state(bool& switch_flag);

	void win_msg(Player* player);

	void draw_msg();

	bool check_game_field(Player* player);

	void play_turn(Player* player);

	std::string to_string_game_state(en_Gameplay_State state) const;

	std::string to_string_gmp_type(en_Gameplay_Type type) const;

	std::string to_string_player_type(en_Player_Type type) const;

public:
	Gameplay()
	{
		/*std::cout << "constructor Gameplay" << std::endl;*/
	}
	~Gameplay() {
		/*std::cout << "constructor ~Gameplay" << std::endl;*/
		delete field_ptr;
		delete player_1_ptr;
		delete player_2_ptr;
	}
	void gmp_start();
	void print_gmp_info() const;
};