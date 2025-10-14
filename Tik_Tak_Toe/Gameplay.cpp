#include "Gameplay.h"

int Gameplay::get_ui_size() const
{
	std::string input;

	std::cout << "[Game msg] Setting a size of the field [3; 5; 7; 9];" << std::endl;
	std::cout << "\t[Input msg] Please enter a size of field: ";

	std::getline(std::cin, input);

	if (Config::isInteger(input)) {
		std::cout << "\t\t[Game msg] You entered: " << input << std::endl;
	}
	else
	{
		throw ExceptionErrorInt("[Error msg] ExceptionInt error. You entered not a number... please repeat");
	}

	return std::stoi(input);
}

void Gameplay::create_a_field()
{
	while (true)
	{
		try
		{
			int size = get_ui_size();
			field_ptr = new Field(size);

			break;
		}
		catch (ExceptionErrorSize& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (ExceptionErrorInt& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (ExceptionError e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

Gameplay::en_Gameplay_Type Gameplay::take_a_type()
{
	std::string input;

	std::cout << "[Game msg] Would you like to play with another player[0] or with an AI agent[1]?" << std::endl;
	std::cout << "\t[Input msg] Please enter a type of game [0; 1]: ";
	std::getline(std::cin, input);

	if (Config::isInteger(input)) {
		int choice = std::stoi(input);

		if (choice != P_vs_P && choice != P_vs_AI)
		{
			throw ExceptionErrorGmpType("[Error msg] ExceptionGmpType error.There is no this type of game... please repeat");
		}

		std::cout << "\t\t[Game msg] You entered: " << input << std::endl;

		switch (choice)
		{
		case P_vs_P:
			return P_vs_P;
		case P_vs_AI:
			return P_vs_AI;
		}
	}
	else
	{
		throw ExceptionErrorInt("[Error msg] ExceptionInt error. You entered not a number... please repeat");
	}
}

char Gameplay::take_a_sign() const
{
	char c = '#';
	std::string input;

	std::cout << "[Game msg] Now you have to choose a figure for you [x or o]." << std::endl;
	std::cout << "\t[Input msg] Please enter \'x\' or \'o\': ";
	std::getline(std::cin, input);

	if (input.size() == 1 && (input[0] == 'x' || input[0] == 'o'))
		c = input[0];
	else
		throw ExceptionErrorFigureType("[Error msg] \'x\' or \'o\'... please repeat", input[0]);

	std::cout << "\t\t[Game msg] You entered: " << c << std::endl;

	return c;
}

void Gameplay::delete_old_data()
{
	delete field_ptr;
}

en_AI_dif_levels Gameplay::get_dif_level()
{
	en_AI_dif_levels dif_level = ai_min_level;
	std::string input;

	std::cout << "[Game msg] Now you have to choose a difficulty level of AI." << std::endl;
	std::cout << "\t[Input msg] Please enter a level[0, 1, 2]: ";
	std::getline(std::cin, input);

	if (Config::isInteger(input))
	{
		dif_level = static_cast<en_AI_dif_levels>(stoi(input));

		if (dif_level != ai_min_level && dif_level != ai_mid_level && dif_level != ai_max_level)
			throw ExceptionErrorDifLevel("[Error msg] We don't have that level, please repeat...");
	}
	else
	{
		throw ExceptionErrorInt("[Error msg] ExceptionInt error. You entered not a number... please repeat");
	}

	std::cout << "\t\t[Game msg] You entered: " << dif_level << std::endl;

	return dif_level;
}

void Gameplay::create_players()
{
	delete player_1_ptr;
	delete player_2_ptr;

	en_AI_dif_levels dif_level = ai_min_level;

	while (true)
	{
		try
		{
			this->gmp_type = take_a_type();
			break;
		}
		catch (ExceptionErrorInt& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (ExceptionErrorGmpType& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (ExceptionErrorDifLevel& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	if (gmp_type == P_vs_AI)
	{
		while (true)
		{
			try
			{
				dif_level = get_dif_level();
				break;
			}
			catch (ExceptionErrorInt& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (ExceptionErrorDifLevel& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	char player_1_f = '#';
	char player_2_f = '#';

	while (true)
	{
		try
		{
			player_1_f = take_a_sign();
			player_2_f = (player_1_f == 'x') ? 'o' : 'x';

			break;
		}
		catch (ExceptionErrorFigureType& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	this->player_1_ptr = new Human_Player(player_1_f);

	switch (gmp_type)
	{
	case P_vs_P:
		this->player_2_ptr = new Human_Player(player_2_f);
		break;
	case P_vs_AI:
		this->player_2_ptr = new AI_Player(player_2_f, dif_level);
		break;
	}
}

void Gameplay::gameplay_state()
{
	bool switch_gmp_type_flag = true;
	bool game_continue_flag = true;

	while (game_continue_flag)
	{
		if (switch_gmp_type_flag)
		{
			create_players();
			switch_gmp_type_flag = false;
		}

		delete_old_data();

		create_a_field();

		game_process();

		game_continue_flag = finish_state(switch_gmp_type_flag);
	}

	print_gmp_info();
}

void Gameplay::game_process()
{
	enum en_turn { first_player, second_player };
	int max_turns = static_cast<int>(pow(field_ptr->get_field_size(), 2));
	int count_turns = 0;
	int pl_turn = 0;

	while (!check_game_field(player_1_ptr) && !check_game_field(player_2_ptr) && count_turns < max_turns)
	{
		if (gmp_type == P_vs_P)
			field_ptr->print_pole();
		else if (gmp_type == P_vs_AI && pl_turn == first_player)
			field_ptr->print_pole();

		switch (pl_turn)
		{
		case first_player:
			try {
				player_1_ptr->pl_play_turn(field_ptr);
				pl_turn += 1;
				count_turns += 1;
			}
			catch (ExceptionErrorFieldCoordChar& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (ExceptionErrorIndex& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (ExceptionErrorInt& e)
			{
				std::cout << e.what() << std::endl;
			}

			break;
		case second_player:
			try {
				player_2_ptr->pl_play_turn(field_ptr);
				pl_turn = 0;
				count_turns += 1;
			}
			catch (ExceptionErrorFieldCoordChar& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (ExceptionErrorIndex& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (ExceptionErrorInt& e)
			{
				std::cout << e.what() << std::endl;
			}

			break;
		}
	}
}

bool Gameplay::finish_state(bool& switch_gmp_type_flag)
{
	std::string input;
	field_ptr->print_pole();

	if (player_1_ptr->get_win_flag())
		win_msg(player_1_ptr);
	else if (player_2_ptr->get_win_flag())
		win_msg(player_2_ptr);
	else
		draw_msg();

	std::cout << std::endl;
	std::cout << "[Game msg] Would you like to play again or not?" << std::endl;
	std::cout << "\t[Input msg] Please enter your response[y | n/exit]: ";
	std::getline(std::cin, input);

	std::cout << std::endl;

	if (input == "n" || input == "exit")
	{
		std::cout << "[Game msg] Have a good day.) Exiting..." << std::endl;
		return false;
	}

	std::cout << "[Game msg] Would you like to switch the game type: " << to_string_gmp_type(gmp_type) << "?" << std::endl;
	std::cout << "\t[Input msg] Please enter your response [y/yes | n/no]: ";
	std::getline(std::cin, input);
	std::cout << std::endl;

	if (input == "y" || input == "yes")
	{
		switch_gmp_type_flag = true;
	}
	else
	{
		switch_gmp_type_flag = false;
	}

	return true;
}

void Gameplay::win_msg(Player* player)
{
	std::cout << "[Win msg] Congrats " << player->get_name() << " you've won this game!!!" << std::endl;
}

void Gameplay::draw_msg()
{
	std::cout << "[Draw msg] Nobody has won this game " << std::endl;
}

bool Gameplay::check_game_field(Player* player)
{
	bool win_flag = true;

	win_flag = field_ptr->check_win_for(player->get_mask());

	if (win_flag)
	{
		player->set_win_flag(true);
		player->inc_score();

		return true;
	}
	else
	{
		return false;
	}
}

void Gameplay::play_turn(Player* player)
{
	int i{ 0 }, j{ 0 };

	player->pl_play_turn(field_ptr);
}

std::string Gameplay::to_string_game_state(en_Gameplay_State state) const {
	switch (state) {
	case Null_State: return "Null";
	case Start_State: return "Start";
	case Game_State: return "Game";
	case End_State: return "End";
	default: return "Unknown";
	}
}

std::string Gameplay::to_string_gmp_type(en_Gameplay_Type type) const {
	switch (type) {
	case P_vs_P: return "Player vs Player";
	case P_vs_AI: return "Player vs AI";
	default: return "Unknown";
	}
}

std::string Gameplay::to_string_player_type(en_Player_Type type) const {
	switch (type) {
	case H_player: return "Human";
	case AI_player: return "AI";
	case None_Player_Type: return "None";
	default: return "Unknown";
	}
}

void Gameplay::gmp_start()
{
	gameplay_state();
}

void Gameplay::print_gmp_info() const
{
	const std::string border = "+------------------------------------------+";
	const int label_width = 18;
	const int value_width = 28;

	std::cout << border << '\n';
	std::cout << "|           Gameplay Info                  |\n";
	std::cout << border << '\n';

	std::cout << "| " << std::setw(label_width) << std::left << "Game State:"
		<< std::setw(value_width) << std::left << to_string_game_state(this->game_state) << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Game Type:"
		<< std::setw(value_width) << std::left << to_string_gmp_type(this->gmp_type) << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 1 Name:"
		<< std::setw(value_width) << std::left << this->player_1_ptr->get_name() << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 1 Type:"
		<< std::setw(value_width) << std::left << to_string_player_type(this->player_1_ptr->get_player_type()) << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 1 Figure:"
		<< std::setw(value_width) << std::left << this->player_1_ptr->get_figure() << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 1 Score:"
		<< std::setw(value_width) << std::left << this->player_1_ptr->get_score() << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 2 Name:"
		<< std::setw(value_width) << std::left << this->player_2_ptr->get_name() << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 2 Type:"
		<< std::setw(value_width) << std::left << to_string_player_type(this->player_2_ptr->get_player_type()) << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 2 Figure:"
		<< std::setw(value_width) << std::left << this->player_2_ptr->get_figure() << "|\n";

	std::cout << "| " << std::setw(label_width) << std::left << "Player 2 Score:"
		<< std::setw(value_width) << std::left << this->player_2_ptr->get_score() << "|\n";

	std::cout << border << '\n';
}