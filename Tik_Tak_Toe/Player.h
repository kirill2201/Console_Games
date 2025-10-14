#pragma once

#include <string>

#include "..\Tik_Tak_Toe\Exceptions.h"
#include "..\Tik_Tak_Toe\Config.h"
#include "..\Tik_Tak_Toe\Field.h"

class Player
{
protected:
	static int p_num;

	en_Player_Type player_type{ None_Player_Type };
	std::string name;
	Field::Mask player_mask;

	char player_figure;
	bool win_flag{ false };
	int score{ 0 };
	

	void set_figure(char c);

public:
	Player(en_Player_Type p_type, char c) : player_type(p_type)
	{
		name = "player_" + std::to_string(p_num);

		set_figure(c);
		p_num += 1;
	}
	virtual ~Player() { p_num -= 1; }

	char get_figure() const;

	const std::string& get_name() const;

	en_Player_Type get_player_type() const;
	bool get_win_flag() const;
	void set_win_flag(bool flag);
	int get_score() const;
	void inc_score();

	Field::Mask& get_mask()
	{
		return this->player_mask;
	}

	virtual void pl_play_turn(Field* field_ptr) = 0;
};

class Human_Player : public Player
{
public:
	Human_Player(char c) : Player(H_player, c)
	{
	}

	void pl_play_turn(Field* field_ptr) override
	{
		int i{ 0 }, j{ 0 };

		std::printf("[Game msg] %s Please enter your cooords[i,j]: ", get_name().c_str());
		Config::read_2_nums(i, j);

		if (Config::check_coord_size(field_ptr, i) && Config::check_coord_size(field_ptr, j))
		{
			if (Config::check_field_pos(field_ptr, i, j))
			{
				field_ptr->change_the_field(i, j, get_figure());

				player_mask.push_back(i * field_ptr->get_field_size() + j);
			}
			else {
				throw ExceptionErrorFieldCoordChar("[Error msg] ExceptionCoordChar this case is already picked... try again");
			}
		}
		else {
			throw ExceptionErrorIndex("[Error msg] ExceptionIndex i and j should be in size", i, j);
		}
	}
};

class AI_Player : public Player
{
	en_AI_dif_levels level{ ai_min_level };

public:
	AI_Player(char c, en_AI_dif_levels level) : Player(AI_player, c), level(level)
	{
	}

	void pl_play_turn(Field* field_ptr) override
	{
		int pos{ 0 };

		switch (level)
		{
		case ai_min_level:
			pos = random_ai_move(field_ptr);
			break;
		case ai_mid_level:
			pos = gridy_ai_move(field_ptr);
			break;
		case ai_max_level:
			pos = random_ai_move(field_ptr);
			break;
		}

		if (pos == -1)
			throw ExceptionErrorFieldCoordChar("[Error msg] AI had an error pos");

		field_ptr->change_the_field(pos, this->get_figure());

		int row = pos / field_ptr->get_field_size();
		int col = pos % field_ptr->get_field_size();

		player_mask.push_back(row * field_ptr->get_field_size() + col);
	}

	// Random AI
	int random_ai_move(Field* field_ptr)
	{
		auto available_moves = field_ptr->get_available_pos();

		if (available_moves.empty())
			return -1;

		return available_moves[rand() % available_moves.size()];
	}

	// Gridi AI
	int gridy_ai_move(Field* field_ptr)
	{
		Field::Mask availabale_pos = field_ptr->get_available_pos();
		std::vector<Field::Mask> win_masks = field_ptr->get_win_masks();

		char our_figure = this->get_figure() == 'x' ? 'x' : 'o';
		char rival_figure = our_figure == 'x' ? 'o' : 'x';

		size_t pos_num = 0;

		// try to win

		for (int av_pos : availabale_pos)
		{
			Field::Mask temp_mask = this->get_mask();
			temp_mask.push_back(av_pos);

			for (Field::Mask win_mask : win_masks)
			{
				bool win = true;

				for (int pos : win_mask)
				{
					if (std::find(temp_mask.begin(), temp_mask.end(), pos) == temp_mask.end())
					{
						win = false;
						break;
					}
				}
				if (win)
					return av_pos;
			}
		}

		// try not to lose

		for (int av_pos : availabale_pos)
		{
			Field::Mask temp_mask = field_ptr->get_mask_for_fig(rival_figure);
			temp_mask.push_back(av_pos);

			for (Field::Mask win_mask : win_masks)
			{
				bool defeat = true;

				for (int pos : win_mask)
				{
					if (std::find(temp_mask.begin(), temp_mask.end(), pos) == temp_mask.end())
					{
						defeat = false;
						break;
					}
				}
				if (defeat)
					return av_pos;
			}
		}

		// random
		pos_num = random_ai_move(field_ptr);

		return pos_num;
	}

	// minimax AI
	int minimax_ai_move(Field* field_ptr)
	{
		return 0;
	}
};