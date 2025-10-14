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

void Gameplay::print_info(bool turn) // доработать вывод чтобы на вражеской карте не было видно вражеских кораблей до из поражения
{
	bool player_1_turn = turn;
	bool player_2_turn = !turn;

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

	if (player_1_turn)
	{
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
	}
	else
	{
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
	}

	// Вывод карт и таблицы
	wchar_t litera = L'A';

	if (player_1_turn)
	{
		for (size_t i = 0; i < Config::row_size; i++)
		{
			player_2.get()->get_field()->print_raw(litera, i, player_2_turn);
			printf(" |    ");
			player_1.get()->get_field()->print_raw(litera, i, player_1_turn);
			printf(" |   %s\n", fleet_info[i].c_str());
			litera++;
			if (i < Config::row_size - 1)
			{
				printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
			}
		}
	}
	else
	{
		for (size_t i = 0; i < Config::row_size; i++)
		{
			player_1.get()->get_field()->print_raw(litera, i, player_1_turn);
			printf(" |    ");
			player_2.get()->get_field()->print_raw(litera, i, player_2_turn);
			printf(" |   %s\n", fleet_info[i].c_str());
			litera++;
			if (i < Config::row_size - 1)
			{
				printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
			}
		}
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
	std::cin.ignore();

	std::cout << "[Chief Officer] Please introduce yourself (Player One): ";
	std::string p1_name = this->give_player_name();
	std::cout << std::endl;
	std::cin.ignore();

	ptr_player_1 = std::make_shared<Player>(p1_name, config);

	std::cout << "[Chief Officer] Please introduce yourself (Player Two): ";
	std::string p2_name = this->give_player_name();
	std::cout << std::endl;
	std::cin.ignore();  // очищаем буфер от '\n'

	ptr_player_2 = std::make_shared<Player>(p2_name, config);

	ptr_player_1.get()->set_player_fleet();
	system("cls");

	ptr_player_2.get()->set_player_fleet();
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
		
		system("cls");

		if (this->player_turn)
		{
			print_info(this->player_turn);

			Point fire_point;

			try
			{
				fire_point = ptr_player_1.get()->make_turn();
			}
			catch (ExceptionExitCode& e)
			{
				std::cout << e.what() << std::endl;
				return GameModuleData{ EN_MENU_MANAGER_CODE, EN_PAUSE_GAME };
			}

			// дополнить проверку результата удара тем, что это может быть не просто пустая клетка(тогда мимо) 
			//		но и уже обстрелянная(тогда новый запрос на выстрел) если же попали тогда новый выстрел

			bool shot_result = ptr_player_2.get()->get_field()->check_fire_point(fire_point);

			ptr_player_2.get()->get_field()->give_fire_point(fire_point);
			
			if (shot_result)
			{
				ptr_player_2.get()->get_fleet_damage(fire_point);


				if (ptr_player_2.get()->get_fleet()->get_size_of_oper_fleet() == 0)
				{
					std::cout << "Player 1 has won!" << std::endl;
					return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
				}

				continue;
			}

			this->player_turn = false;
		}
		else
		{
			print_info(player_turn);
			Point fire_point;

			try
			{
				fire_point = ptr_player_2.get()->make_turn();
			}
			catch (ExceptionExitCode& e)
			{
				std::cout << e.what() << std::endl;
				return GameModuleData{ EN_MENU_MANAGER_CODE, EN_PAUSE_GAME };
			}

			bool shot_result = ptr_player_1.get()->get_field()->check_fire_point(fire_point);

			if (shot_result)
			{
				ptr_player_1.get()->get_field()->give_fire_point(fire_point);
				ptr_player_1.get()->get_fleet_damage(fire_point);

				if (ptr_player_1.get()->get_fleet()->get_size_of_oper_fleet() == 0)
				{
					std::cout << "Player 2 has won!" << std::endl;
					return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
				}

				continue;
			}

			player_turn = true;
		}
	}

	return GameModuleData{ EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU };
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