#include "Gameplay.h"

GameModuleData Gameplay::module_process(EnMenuOptions option)
{
	// сделать обработку приходящих кодов

	GameModuleData new_option{ EN_MENU_MANAGER_CODE, EN_NONE_OPT };

	switch (option)
	{
	case EN_PM_NEW_GAME:
		this->cur_gameplay_mode = EN_START_GAMEPLAY;
		break;
	case EN_PM_CONTINUE:
		this->cur_gameplay_mode = EN_CONTINUE_GAMEPLAY;
		break;
	case EN_PAUSE_GAME:
		this->cur_gameplay_mode = EN_PAUSE_GAMEPLAY;
		break;
	}

	switch (this->cur_gameplay_mode)
	{
	case EN_START_GAMEPLAY:
		new_option = this->gameplay_start();
		break;
	case EN_CONTINUE_GAMEPLAY:
		new_option = this->gameplay_continue_load();
		break;

	case EN_PAUSE_GAMEPLAY:
		return GameModuleData{ EN_MENU_MANAGER_CODE, EN_PAUSE_GAME };
	}

	return new_option;
}

void Gameplay::print_info(EnPlayers p_turn, size_t row_u_ptr, size_t col_u_ptr)
{
	system("cls");

	std::string p_name;
	std::shared_ptr<Player> player_1 = ptr_player_1;
	std::shared_ptr<Player> player_2 = ptr_player_2;

	// Заголовки карт: ширина 31 символ, текст центрирован
	printf("+======================================================+    +======================================================+   +====================+==============+========+========+\n");
	printf("|                     Attack Map                       |    |                      Your Fleet                      |   |        Name        |      Type    |  Crew  |  Size  |\n");
	printf("|      0    1    2    3    4    5    6    7    8    9  |    |      0    1    2    3    4    5    6    7    8    9  |   |                    |              |        |        |\n");
	printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +=====================================================+\n");

	auto p1_field = player_1.get()->get_field()->get_field();
	auto p1_fleet = player_1.get()->get_fleet()->get_current_fleet();

	auto p2_field = player_2.get()->get_field()->get_field();
	auto p2_fleet = player_2.get()->get_fleet()->get_current_fleet();

	std::vector<std::string> fleet_info(Config::row_size);

	//Заполнение таблицы флота
	size_t fleet_idx = 0;
	// Вывод карт и таблицы
	wchar_t litera = L'A';

	switch (p_turn)
	{
	case EN_PLAYER_1:
		p_name = ptr_player_1->get_player_name();
		for (size_t i = 0; i < p1_fleet.size() && fleet_idx < Config::row_size; ++i, ++fleet_idx)
		{
			std::string name = p1_fleet[i].get()->get_ship_name();
			std::string ship_type = p1_fleet[i].get()->get_ship_type_str();

			size_t crew = p1_fleet[i]->get_ship_complement();
			size_t size = p1_fleet[i].get()->get_ship_size();

			// Форматирование строки таблицы
			char buffer[100];
			snprintf(buffer, 100, "| %-18s | %-12s | %5zu  | %5zu  |",
				name.c_str(), ship_type.c_str(), crew, size);
			fleet_info[fleet_idx] = buffer;
		}

		for (size_t row_i = 0; row_i < Config::row_size; row_i++)
		{
			if (row_i == row_u_ptr)
			{
				player_2.get()->get_field()->print_row_with_u_ptr(litera, row_i, col_u_ptr, this->ptr_player_2->get_cur_state());
			}
			else
			{
				player_2.get()->get_field()->print_row(litera, row_i, this->ptr_player_2->get_cur_state());
			}
			printf(" |    ");

			player_1.get()->get_field()->print_row(litera, row_i, this->ptr_player_1->get_cur_state());
			printf(" |   %s\n", fleet_info[row_i].c_str());
			litera++;

			if (row_i < Config::row_size - 1)
			{
				printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
			}
		}
		break;

	case EN_PLAYER_2:
		p_name = ptr_player_2->get_player_name();
		for (size_t i = 0; i < p2_fleet.size() && fleet_idx < Config::row_size; ++i, ++fleet_idx)
		{
			std::string name = p2_fleet[i].get()->get_ship_name();
			std::string ship_type = p2_fleet[i].get()->get_ship_type_str();

			size_t crew = p2_fleet[i].get()->get_ship_complement();
			size_t size = p2_fleet[i].get()->get_ship_size();

			// Форматирование строки таблицы
			char buffer[100];
			snprintf(buffer, 100, "| %-18s | %-12s | %5zu  | %5zu  |",
				name.c_str(), ship_type.c_str(), crew, size);
			fleet_info[fleet_idx] = buffer;
		}

		for (size_t row_i = 0; row_i < Config::row_size; row_i++)
		{
			if (row_i == row_u_ptr)
			{
				player_1->get_field()->print_row_with_u_ptr(litera, row_i, col_u_ptr, this->ptr_player_1->get_cur_state());
			}
			else
			{
				player_1.get()->get_field()->print_row(litera, row_i, this->ptr_player_1->get_cur_state());
			}
			printf(" |    ");

			player_2.get()->get_field()->print_row(litera, row_i, this->ptr_player_2->get_cur_state());
			printf(" |   %s\n", fleet_info[row_i].c_str());
			litera++;
			if (row_i < Config::row_size - 1)
			{
				printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
			}
		}
		break;
	}


	// Нижняя рамка карт
	printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
	std::cout << std::endl;

	std::cout << "[Chief Officer] Captain " << p_name << ", it's your turn to fire! Use the arrow keys or W/A/S/D to move the target marker, and press Enter to fire. Press Esc to pause the game." << std::endl;
}

std::string Gameplay::give_player_name()
{
	std::string p_name;

	std::cin.clear();

	std::cin >> p_name;
	std::cin.ignore(Config::max_sz_stream, '\n');

	return p_name;
}

void Gameplay::show_ai_menu(const std::vector<std::string>& options, size_t menu_options_sz, size_t ptr_idx)
{
	system("cls");
	std::cout << "[Game] Would you like to play PvP or PvE:\n\n";

	for (size_t i = 0; i < menu_options_sz; i++)
	{
		if (i == ptr_idx)
		{
			std::cout << "> " << options[i] << "\n";
		}
		else
		{
			std::cout << "  " << options[i] << "\n";
		}
	}
	std::cout << std::endl;
}

GameModuleData Gameplay::gameplay_start()
{
	std::cin.clear();
	std::cin.ignore(Config::max_sz_stream, '\n');


	// AI/Human options menu
	EnPlayerModes game_mode = EN_PLAYER_VS_PLAYER;
	std::vector<std::string> options = { "PvE", "PvP" };
	size_t ptr_idx = 0;
	size_t menu_options_sz = options.size();

	// Начальная отрисовка меню
	show_ai_menu(options, menu_options_sz, ptr_idx);

	while (true)
	{
		// Обновление состояния клавиш
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;
		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current)
		{
			if (ptr_idx > 0)
			{
				--ptr_idx;
				show_ai_menu(options, menu_options_sz, ptr_idx);
			}
			// Ожидание отпускания клавиши
			while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			{
				Sleep(10);
			}
		}

		// Обработка нажатия клавиши ВНИЗ/S
		if (down_current)
		{
			if (ptr_idx < menu_options_sz - 1)
			{
				++ptr_idx;
				show_ai_menu(options, menu_options_sz, ptr_idx);
			}
			// Ожидание отпускания клавиши
			while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			{
				Sleep(10);
			}
		}

		// Обработка нажатия ENTER
		if (enter_current)
		{
			// Ожидание отпускания клавиши ENTER
			while (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				Sleep(10);
			}
			break;
		}

		Sleep(50); // Небольшая задержка для снижения нагрузки на ЦП
	}

	// Установка режима игры на основе выбора
	switch (ptr_idx)
	{
	case 0: // PvE
		game_mode = EN_PLAYER_VS_AI;
		break;
	case 1: // PvP
		game_mode = EN_PLAYER_VS_PLAYER;
		break;
	}

	this->player_game_mode = game_mode;
	// end block

	system("cls");
	std::string p1_name;

	getline(std::cin, p1_name);
	p1_name.clear();

	while (true)
	{
		system("cls");
		std::cout << "[Chief Officer] Please introduce yourself (Player One): ";
		p1_name = this->give_player_name();

		if (p1_name.empty())
		{
			std::cout << "[Chief Officer] Name can\'t be empty, Captain..." << std::endl;
			continue;
		}

		std::cout << std::endl;
		break;
	}

	ptr_player_1 = std::make_shared<HumanPlayer>(p1_name, EN_PLAYER_1, config);

	switch (game_mode)
	{
	case EN_PLAYER_VS_PLAYER:
	{
		std::string p2_name;

		while (true)
		{
			std::cout << "[Chief Officer] Please introduce yourself (Player Two): ";
			p2_name = this->give_player_name();

			if (p2_name.empty())
			{
				std::cout << "[Chief Officer] Name can\'t be empty, Captain..." << std::endl;
				continue;
			}

			std::cout << std::endl;
			break;
		}

		ptr_player_2 = std::make_shared<HumanPlayer>(p2_name, EN_PLAYER_2, config);
		break;
	}
	case EN_PLAYER_VS_AI:
		ptr_player_2 = std::make_shared<AiPlayer>(EN_EASY_AI, config);
		break;
	}

	ptr_player_1.get()->set_player_fleet();
	ptr_player_1->set_cur_state(true);
	system("cls");

	ptr_player_2.get()->set_player_fleet();
	ptr_player_2->set_cur_state(false);
	system("cls");

	return this->middle_game();
}

GameModuleData Gameplay::middle_game()
{
	bool game_flag = true;

	Point fire_point{ 0,0 };

	while (game_flag)
	{
		GameModuleData data{ EN_GAMEPLAY_CODE, EN_NONE_OPT };
		EnFireOptions shot_result;

		fire_point.y = 0;
		fire_point.x = 0;

		if (ptr_player_1->get_cur_state())
		{
			data.menu_option = ptr_player_1->make_turn(fire_point);
		}
		else
		{
			data.menu_option = ptr_player_2->make_turn(fire_point);
		}

		switch (data.menu_option)
		{
		case EN_PAUSE_GAME:
			data.game_module_code = EN_MENU_MANAGER_CODE;
			return data;

		case EN_NONE_OPT:
			break;
		}

		if (ptr_player_1->get_cur_state())
		{
			data = this->player_turn_fun(ptr_player_1, ptr_player_2, fire_point);
		}
		else
		{
			data = this->player_turn_fun(ptr_player_2, ptr_player_1, fire_point);
		}

		if (data.game_module_code == EN_MENU_MANAGER_CODE)
			break;
	}

	return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
}

GameModuleData Gameplay::end_game(std::list<std::string>& game_messages)
{

	bool enter_pressed = false;
	bool esc_pressed = false;

	while (true)
	{
		bool esc_current = GetAsyncKeyState(VK_ESCAPE) & 0x8000;
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		if (enter_current && !enter_pressed)
		{
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				Sleep(10);
			}
			break;
		}

		if (esc_current && !esc_pressed)
		{
			while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				Sleep(10);
			}
			break;
		}
	}

	return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
}

GameModuleData Gameplay::player_turn_fun(std::shared_ptr<Player> ptr_player, std::shared_ptr<Player> ptr_rival, Point& fire_point)
{
	// Выбор очереди сообщений в зависимости от ID игрока
	std::list<std::string>& game_messages = ptr_player->get_player_messages();


	EnFireOptions shot_result = ptr_rival->get_field()->check_fire_point(fire_point);

	switch (shot_result)
	{
	case EN_HIT:
		game_messages.push_front("[Chief Officer] Direct hit! That'll teach them!");
		ptr_rival->get_field()->give_fire_point(fire_point);
		ptr_player->get_atack_field()->get_field()[fire_point.y][fire_point.x]->set_type(EN_DESTROY_COMPARTMENT);

		if (!ptr_rival->get_fleet_damage(fire_point))
		{
			game_messages.push_front("[Chief Officer] We've sunk an enemy ship, Captain!");
		}

		if (!ptr_rival->get_fleet()->check_situation())
		{
			std::string title = "[Chief Officer]";
			std::string main = "All enemy ships have been destroyed! Victory is ours, Captain!";
			std::string hint = "[Enter/ESC]";
			std::string msg = title + " " + main + " " + hint;

			// Minimum width for the frame
			size_t minWidth = 60;
			size_t boxWidth = msg.length() + 4; // padding left/right inside box
			if (boxWidth < minWidth) boxWidth = minWidth;

			// Draw top border
			std::cout << "+" << std::string(boxWidth - 2, '=') << "+" << std::endl;

			// Empty spacer line
			std::cout << "|" << std::string(boxWidth - 2, ' ') << "|" << std::endl;

			// Centered message line (no wrapping)
			size_t innerWidth = boxWidth - 2;
			size_t paddingLeft = 0;
			if (innerWidth > msg.length())
				paddingLeft = (innerWidth - msg.length()) / 2;
			std::cout << "|" << std::string(paddingLeft, ' ') << msg
				<< std::string(innerWidth - paddingLeft - msg.length(), ' ') << "|" << std::endl;

			// Empty spacer line
			std::cout << "|" << std::string(boxWidth - 2, ' ') << "|" << std::endl;

			// Bottom border
			std::cout << "+" << std::string(boxWidth - 2, '=') << "+" << std::endl;

			return end_game(game_messages);
		}
		break;

	case EN_MISSED:
		ptr_rival->get_field()->give_fire_point(fire_point);
		ptr_player->get_atack_field()->get_field()[fire_point.y][fire_point.x]->set_type(EN_FIRED_POINT);

		ptr_player->set_cur_state(false);
		ptr_rival->set_cur_state(true);
		break;

	case EN_ERROR_COORDS:
		game_messages.push_front("[Chief Officer] Invalid coordinates. Try again!");
		break;
	}

	if (game_messages.size() > Config::max_sz_log)
	{
		game_messages.pop_back();
	}

	return GameModuleData{ EN_GAMEPLAY_CODE, EN_NONE_OPT };
}

GameModuleData Gameplay::gameplay_load()
{
	// 1. загрузить данные по тому AI vs Human || Hum vs Hum 
	// 2. загрузить данные по флотам двух игроков
	// 3. загрузить данные по point_to_ship_dict (каждая точка на карте - ключ, а корабль значение)
	// 4. создать карты у игроков, основываясь на данных о флотах с координатами у каждого корабля
	// 5. загрузить остальную инфу:
	//    a. static size_t p_id;
	//    b. size_t point_count;
	//    c. std::string name;
	//    d. bool cur_state = false; 
	return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
}

GameModuleData Gameplay::gameplay_continue_load()
{
	return middle_game();
}

//void Gameplay::set_saves(const std::vector<std::shared_ptr<SavedGameplayData>>& saves)
//{
//	// Nothing to do if list empty
//	if (saves.empty()) return;
//
//	// Use the most-recently loaded save (last element)
//	const auto& latest_save = saves.back();
//	if (!latest_save) return;
//
//	// Restore gameplay config and mode
//	this->config = latest_save->config;
//	this->cur_gameplay_mode = latest_save->cur_gameplay_mode;
//
//	// Restore players pointers (players were constructed by Game::load_game)
//	this->ptr_player_1 = latest_save->p1_data;
//	this->ptr_player_2 = latest_save->p2_data;
//
//	// If players exist, ensure their fields are present and consistent.
//	// (load_game already restored fields/ships; here we just attach them to gameplay)
//	if (this->ptr_player_1)
//	{
//		// leave player internal state as loaded; optionally ensure turn state:
//		// if both players present and neither has cur_state true, default player_1 to true
//	}
//	if (this->ptr_player_2)
//	{
//		// same as above
//	}
//
//	// Ensure at least one player's cur_state true so gameplay loop behaves predictably
//	if (ptr_player_1 && ptr_player_2)
//	{
//		if (!ptr_player_1->get_cur_state() && !ptr_player_2->get_cur_state())
//		{
//			// default to player 1's turn
//			ptr_player_1->set_cur_state(true);
//			ptr_player_2->set_cur_state(false);
//		}
//	}
//	else if (ptr_player_1)
//	{
//		ptr_player_1->set_cur_state(true);
//	}
//	else if (ptr_player_2)
//	{
//		ptr_player_2->set_cur_state(true);
//	}
//}

const Config& Gameplay::get_config() const
{
	return this->config;
}

EnGameTypes Gameplay::get_cur_gameplay_mode() const
{
	return this->cur_gameplay_mode;
}

EnPlayerModes Gameplay::get_player_game_mode() const
{
	return this->player_game_mode;
}

const std::shared_ptr<Player> Gameplay::get_ptr_player_1() const
{
	return this->ptr_player_1;
}

const std::shared_ptr<Player> Gameplay::get_ptr_player_2() const
{
	return this->ptr_player_2;
}