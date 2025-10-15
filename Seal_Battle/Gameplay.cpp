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

void Gameplay::print_info(EnPlayers p_turn) // доработать вывод чтобы на вражеской карте не было видно вражеских кораблей до из поражения
{
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
		for (size_t i = 0; i < p1_fleet.size() && fleet_idx < Config::row_size; ++i, ++fleet_idx)
		{
			std::string name = p1_fleet[i].get()->get_ship_name();
			std::string ship_type = p1_fleet[i].get()->get_ship_type_str();

			size_t crew = p1_fleet[i].get()->get_ship_complement();
			size_t size = p1_fleet[i].get()->get_ship_size();

			// Форматирование строки таблицы
			char buffer[100];
			snprintf(buffer, 100, "| %-18s | %-12s | %5zu  | %5zu  |",
				name.c_str(), ship_type.c_str(), crew, size);
			fleet_info[fleet_idx] = buffer;
		}

		for (size_t i = 0; i < Config::row_size; i++)
		{
			player_2.get()->get_field()->print_raw(litera, i, this->ptr_player_2->get_cur_state());
			printf(" |    ");
			player_1.get()->get_field()->print_raw(litera, i, this->ptr_player_1->get_cur_state());
			printf(" |   %s\n", fleet_info[i].c_str());
			litera++;
			if (i < Config::row_size - 1)
			{
				printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
			}
		}
		break;

	case EN_PLAYER_2:
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

		for (size_t i = 0; i < Config::row_size; i++)
		{
			player_1.get()->get_field()->print_raw(litera, i, this->ptr_player_1->get_cur_state());
			printf(" |    ");
			player_2.get()->get_field()->print_raw(litera, i, this->ptr_player_2->get_cur_state());
			printf(" |   %s\n", fleet_info[i].c_str());
			litera++;
			if (i < Config::row_size - 1)
			{
				printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
			}
		}
		break;
	}

	// Нижняя рамка карт
	printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
}

std::string Gameplay::give_player_name()
{
	std::string p_name;

	std::cin >> p_name;

	return p_name;
}

GameModuleData Gameplay::gameplay_start()
{
	system("cls");

	std::cout << "[Chief Officer] Please introduce yourself (Player One): ";
	std::string p1_name = this->give_player_name();
	std::cout << std::endl;
	std::cin.ignore();

	ptr_player_1 = std::make_shared<Player>(p1_name, EN_PLAYER_1, config);

	std::cout << "[Chief Officer] Please introduce yourself (Player Two): ";
	std::string p2_name = this->give_player_name();
	std::cout << std::endl;
	std::cin.ignore();  // очищаем буфер от '\n'

	ptr_player_2 = std::make_shared<Player>(p2_name, EN_PLAYER_2, config);

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

	while (game_flag)
	{
		// переделать ввод на перехват клавишь для отрисовки поля с маркером !! в этом модуле 
		// после выбора через enter координаты выбранной точки пробрасываются в ход игрока и оттуда может прилететь исключение если точка не верна
		GameModuleData data{ EN_GAMEPLAY_CODE, EN_NONE_OPT };

		if (this->ptr_player_1->get_cur_state())
		{
			data = player_turn_fun(ptr_player_1, ptr_player_2);
		}
		else
		{
			data = player_turn_fun(ptr_player_2, ptr_player_1);
		}

		switch (data.game_module_code)
		{
		case EN_MENU_MANAGER_CODE:
			return data;
		case EN_GAMEPLAY_CODE:
			break;
		}
	}

	return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
}

GameModuleData Gameplay::player_turn_fun(std::shared_ptr<Player> ptr_player, std::shared_ptr<Player> ptr_rival)
{
	system("cls");
	
	while (ptr_player->get_cur_state())
	{
		print_info(ptr_player->get_player_id()); // переписать эту хуйню на зависимость от id игрока а не от блядской переменной тру фолз

		Point fire_point;

		try
		{
			fire_point = ptr_player.get()->make_turn();
		}
		catch (ExceptionExitCode& e)
		{
			std::cout << e.what() << std::endl;
			return GameModuleData{ EN_MENU_MANAGER_CODE, EN_PAUSE_GAME };
		}

		// дополнить проверку результата удара тем, что это может быть не просто пустая клетка(тогда мимо) 
		//		но и уже обстрелянная(тогда новый запрос на выстрел) если же попали тогда новый выстрел

		EnFireOptions shot_result = ptr_rival.get()->get_field()->check_fire_point(fire_point);

		switch (shot_result)
		{
		case EN_HIT:
			ptr_rival.get()->get_field()->give_fire_point(fire_point);
			ptr_rival.get()->get_fleet_damage(fire_point);

			if (ptr_rival.get()->get_fleet()->get_size_of_oper_fleet() == 0)
			{
				std::cout << "Player 1 has won!" << std::endl;
				return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
			}

			break;

		case EN_MISSED:
			ptr_rival.get()->get_field()->give_fire_point(fire_point);
			ptr_player->set_cur_state(false);
			ptr_rival->set_cur_state(true);
			break;

		case EN_ERROR_COORDS:
			std::cout << "[Again please]" << std::endl;
			break;
		}
	}

	return GameModuleData{ EN_GAMEPLAY_CODE, EN_NONE_OPT };
}

GameModuleData Gameplay::end_game()
{
	return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
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