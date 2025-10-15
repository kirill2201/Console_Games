#include "Game.h"

// Функция для центрирования текста
void Game::printCentered(const std::vector<std::string>& art) {
	// Получаем ширину консоли
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	// Выводим каждую строку арта с центрированием
	for (const auto& line : art) {
		int padding = (consoleWidth - line.length()) / 2;

		if (padding > 0) {
			std::cout << std::string(padding, ' ') << line << std::endl;
		}
		else {
			std::cout << line << std::endl; // Если строка шире консоли, выводим без отступов
		}
	}
}

void Game::logo_show()
{
	std::vector<std::string> logo = {
		 "oooooooooo.                .       .   oooo                     oooo         o8o              ",
		 "`888'   `Y8b             .o8     .o8   `888                     `888         `\"'              ",
		 " 888     888  .oooo.   .o888oo .o888oo  888   .ooooo.   .oooo.o  888 .oo.   oooo  oo.ooooo.   ",
		 " 888oooo888' `P  )88b    888     888    888  d88' `88b d88(  \"8  888P\"Y88b  `888   888' `88b  ",
		 " 888    `88b  .oP\"888    888     888    888  888ooo888 `\"Y88b.   888   888   888   888   888  ",
		 " 888    .88P d8(  888    888 .   888 .  888  888    .o o.  )88b  888   888   888   888   888  ",
		 "o888bood8P'  `Y888\"\"8o   \"888\"   \"888\" o888o `Y8bod8P' 8\"\"888P' o888o o888o o888o  888bod8P'  ",
		 "                                                                                  888         ",
		 "                                                                                 o888o        "
	};

	std::vector<std::string> logo_pic = {
		 "############################################################################",
		 "############################################################################",
		 "############################################################################",
		 "############################################################################",
		 "#####################################.#+####################################",
		 "#####################################-#-####################################",
		 "#####################################.#.####################################",
		 "#####################################.#.####################################",
		 "##################################+  -. ..##################################",
		 "################################### - . #+##################################",
		 "################################### # # #+##################################",
		 "################################### # # #-##################################",
		 "################################### # #.#-##################################",
		 "################################### - #--.##################################",
		 "##################################+.+.+-#.-#################################",
		 "##################################.-- ---+##################################",
		 "##################--#+###########+--##-+##+######+#######--+################",
		 "##################-+##-#.#######.##.--.#+###########+#.##+.+################",
		 "############################.-## -#-.--#++#+###--##-##-#####################",
		 "########+#############++##+#- #+ .#++-.-++#-+##-##+###.#####################",
		 "######.-.-+###########.-++#+#########-..##########################..-.######",
		 "########+#####.#. .-+#  ..  #####..##-####.-#####..######-+--#-#############",
		 "##############.# ...+#  ..-#++...##--+ #--##-##+#######-######+#############",
		 "##############.-    .+ ..+#####..#.+.+-#--++###########+..++##-#############",
		 "##############--    .-  . -- . .# +--# #-##---#+##.-###.. .-##+#############",
		 "##############-  .. +# .  .      .     .   --.. ...-+#####+##+++############",
		 "############## ........- . ..--+-+..######-#####+#+--++###### ++############",
		 "####.-++---#+#  -....--.--. ..++++.#.##+###+####.++########## .-##-+-++-+###",
		 "############.-.+------------+   .. .   ..-.. .-+#############.##-###########",
		 "############+. .-.   ... . .....++++#+##########-##.-#+++++#####.###########",
		 "#############--.-...----.-------+#++-########################-##+###########",
		 "############-..-.-........------+++++#######################################",
		 "############-.........-...------+++++#######################################",
		 "############################################################################",
		 "############################################################################",
		 "############################################################################",
		 "############################################################################",
		 "############################################################################",
	};

	// Определяем ширину рамки (на основе самого длинного логотипа)
	size_t maxWidth = 0;
	for (const auto& line : logo_pic) {
		if (line.length() > maxWidth) maxWidth = line.length();
	}
	for (const auto& line : logo) {
		if (line.length() > maxWidth) maxWidth = line.length();
	}

	// Создаем рамку
	std::vector<std::string> framedLogo;
	std::string topBottomBorder = "+" + std::string(maxWidth + 4, '=') + "+"; // +4 для || с каждой стороны
	std::string sideBorder = "||" + std::string(maxWidth + 2, ' ') + "||";

	// Верхняя граница
	framedLogo.push_back(topBottomBorder);

	// Добавляем logo с центрированием внутри рамки
	for (const auto& line : logo) {
		size_t padding = (maxWidth - line.length()) / 2;
		std::string paddedLine = "||" + std::string(1, ' ') + line + std::string(0, ' ') + "||";
		framedLogo.push_back(paddedLine);
	}

	// Промежуточная граница
	framedLogo.push_back(topBottomBorder);

	// Добавляем logo_pic с центрированием внутри рамки
	for (const auto& line : logo_pic) {
		size_t padding = (maxWidth - line.length()) / 2;
		std::string paddedLine = "||" + std::string(padding, ' ') + line + std::string(maxWidth - line.length() - padding, ' ') + "||";
		framedLogo.push_back(paddedLine);
	}

	// Нижняя граница
	framedLogo.push_back(topBottomBorder);

	// Выводим логотип с рамкой
	printCentered(framedLogo);

	std::cout << "Enter for continue...\n";

	while (true)
	{
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		if (enter_current) 
		{
			while (true) {
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
					// "Очистка буфера" - ждем, пока клавиша Enter отпущена
					while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
						Sleep(10); // Ждем отпускания клавиши
					}

					break; // Выход из ожидания Enter
				}
				Sleep(10);
			}

			break;
		}
	}
}

void Game::save_player_data(const std::shared_ptr<Player>& ptr_player, std::shared_ptr<GameField>& ptr_player_field, std::shared_ptr<Fleet>& ptr_player_fleet,
	std::map<Point, std::shared_ptr<Ship>>& player_point_to_ship_dict, size_t& player_id, size_t& player_point_count, std::string& player_name, bool& player_cur_state)
{
	ptr_player_field = ptr_player->get_field();
	ptr_player_fleet = ptr_player->get_fleet();
	player_point_to_ship_dict = ptr_player->get_point_to_ship_dict();
	player_id = ptr_player->get_player_id();
	player_point_count = ptr_player->get_point_count();
	player_name = ptr_player->get_player_name();
	player_cur_state = ptr_player->get_cur_state();
}

void Game::save_fleet_data(std::shared_ptr<Fleet>& ptr_player_fleet, std::vector<std::shared_ptr<Ship>>& fleet,
	std::vector<std::shared_ptr<Ship>>& wasted_ships, size_t& size_def_fleet, size_t& size_oper_fleet, size_t& size_wasted_fleet)
{
	fleet = ptr_player_fleet->get_current_fleet();
	wasted_ships = ptr_player_fleet->get_wasted_ships();
	size_def_fleet = ptr_player_fleet->get_def_size();
	size_oper_fleet = ptr_player_fleet->get_size_of_oper_fleet();
	size_wasted_fleet = ptr_player_fleet->get_size_of_wasted_fleet();
}

void Game::save_game()
{
	// Извлекаем данные из gameplay
	/*std::shared_ptr<Player> ptr_player_1 = this->ptr_gameplay->get_ptr_player_1();
	std::shared_ptr<Player> ptr_player_2 = this->ptr_gameplay->get_ptr_player_2();

	std::shared_ptr<GameField> ptr_player_1_field, ptr_player_2_field;
	std::shared_ptr<Fleet> ptr_player_1_fleet, ptr_player_2_fleet;
	std::map<Point, std::shared_ptr<Ship>> player_1_point_to_ship_dict, player_2_point_to_ship_dict;

	size_t player_1_id, player_2_id;
	size_t player_1_point_count, player_2_point_count;
	std::string player_1_name, player_2_name;
	bool player_1_cur_state, player_2_cur_state;

	save_player_data(ptr_player_1, ptr_player_1_field, ptr_player_1_fleet, player_1_point_to_ship_dict,
		player_1_id, player_1_point_count, player_1_name, player_1_cur_state);
	save_player_data(ptr_player_2, ptr_player_2_field, ptr_player_2_fleet, player_2_point_to_ship_dict,
		player_2_id, player_2_point_count, player_2_name, player_2_cur_state);

	size_t size_def_fleet_1, size_oper_fleet_1, size_wasted_fleet_1;
	size_t size_def_fleet_2, size_oper_fleet_2, size_wasted_fleet_2;
	std::vector<std::shared_ptr<Ship>> fleet_1, fleet_2;
	std::vector<std::shared_ptr<Ship>> wasted_ships_1, wasted_ships_2;

	save_fleet_data(ptr_player_1_fleet, fleet_1, wasted_ships_1, size_def_fleet_1, size_oper_fleet_1, size_wasted_fleet_1);
	save_fleet_data(ptr_player_2_fleet, fleet_2, wasted_ships_2, size_def_fleet_2, size_oper_fleet_2, size_wasted_fleet_2);

	// Создаём JSON-объект
	json j;

	// Сохраняем режим игры
	j["gameplay"]["mode"] = enGameTypesToString(ptr_gameplay->get_cur_gameplay_mode());
	j["gameplay"]["player_mode"] = enPlayerModesToString(ptr_gameplay->get_player_game_mode());

	// Сохраняем конфигурацию (пример, нужно адаптировать под Config)
	j["gameplay"]["config"]["row_size"] = Config::row_size;
	j["gameplay"]["config"]["col_size"] = Config::col_size;
	// Добавить другие параметры Config, если есть, например:
	// j["gameplay"]["config"]["ship_names"] = ptr_gameplay->get_config().get_ship_names();

	// Сохраняем данные игрока 1
	auto& p1 = j["gameplay"]["player1"];
	p1["id"] = player_1_id;
	p1["name"] = player_1_name;
	p1["point_count"] = player_1_point_count;
	p1["is_active"] = player_1_cur_state;

	// Сохраняем поле игрока 1
	auto field1 = ptr_player_1_field->get_field();
	std::vector<std::vector<std::string>> field_data1;
	for (const auto& row : field1) {
		std::vector<std::string> row_data;
		for (const auto& point : row) {
			row_data.push_back(enFieldPointTypeToString(point->get_type()));
		}
		field_data1.push_back(row_data);
	}
	p1["field"] = field_data1;

	// Сохраняем флот игрока 1
	std::vector<json> fleet_data1;
	for (const auto& ship : fleet_1) {
		json ship_json;
		ship_json["type"] = enShipTypeToString(ship->get_ship_type());
		ship_json["name"] = ship->get_ship_name();
		ship_json["size"] = ship->get_ship_size();
		ship_json["complement"] = ship->get_ship_complement();

		// Сохраняем координаты корабля
		std::vector<json> coords;
		for (const auto& point : ship->get_ship_coords()) {
			coords.push_back({ {"x", point->x}, {"y", point->y} });
		}
		ship_json["coords"] = coords;

		// Сохраняем отсеки корабля
		std::vector<json> hull;
		for (const auto& comp : ship->get_ship_hull()) {
			hull.push_back({
				 {"complement", comp->get_compartment_complement()},
				 {"state", comp->get_compartment_state()},
				 {"type", enShipCompartmentTypeToString(comp->get_compartment_type())}
				});
		}
		ship_json["hull"] = hull;

		fleet_data1.push_back(ship_json);
	}
	p1["fleet"] = fleet_data1;

	// Сохраняем уничтоженные корабли игрока 1 (только имена для упрощения)
	std::vector<std::string> wasted_ships_names1;
	for (const auto& ship : wasted_ships_1) {
		wasted_ships_names1.push_back(ship->get_ship_name());
	}
	p1["wasted_ships"] = wasted_ships_names1;

	// Сохраняем данные игрока 2 (аналогично)
	auto& p2 = j["gameplay"]["player2"];
	p2["id"] = player_2_id;
	p2["name"] = player_2_name;
	p2["point_count"] = player_2_point_count;
	p2["is_active"] = player_2_cur_state;

	// Сохраняем поле игрока 2
	auto field2 = ptr_player_2_field->get_field();
	std::vector<std::vector<std::string>> field_data2;
	for (const auto& row : field2) {
		std::vector<std::string> row_data;
		for (const auto& point : row) {
			row_data.push_back(enFieldPointTypeToString(point->get_type()));
		}
		field_data2.push_back(row_data);
	}
	p2["field"] = field_data2;

	// Сохраняем флот игрока 2
	std::vector<json> fleet_data2;
	for (const auto& ship : fleet_2) {
		json ship_json;
		ship_json["type"] = enShipTypeToString(ship->get_ship_type());
		ship_json["name"] = ship->get_ship_name();
		ship_json["size"] = ship->get_ship_size();
		ship_json["complement"] = ship->get_ship_complement();

		// Сохраняем координаты корабля
		std::vector<json> coords;
		for (const auto& point : ship->get_ship_coords()) {
			coords.push_back({ {"x", point->x}, {"y", point->y} });
		}
		ship_json["coords"] = coords;

		// Сохраняем отсеки корабля
		std::vector<json> hull;
		for (const auto& comp : ship->get_ship_hull()) {
			hull.push_back({
				 {"complement", comp->get_compartment_complement()},
				 {"state", comp->get_compartment_state()},
				 {"type", enShipCompartmentTypeToString(comp->get_compartment_type())}
				});
		}
		ship_json["hull"] = hull;

		fleet_data2.push_back(ship_json);
	}
	p2["fleet"] = fleet_data2;

	// Сохраняем уничтоженные корабли игрока 2
	std::vector<std::string> wasted_ships_names2;
	for (const auto& ship : wasted_ships_2) {
		wasted_ships_names2.push_back(ship->get_ship_name());
	}
	p2["wasted_ships"] = wasted_ships_names2;

	// Записываем JSON в файл
	std::string filename = "savegame.json"; // Можно запросить имя файла у пользователя
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file for saving!");
	}
	file << j.dump(4); // Форматированный JSON с отступами
	file.close();

	// Сохраняем данные в вектор saves (если нужно)
	auto saved_data = std::make_shared<SavedGameplayData>();
	saved_data->config = ptr_gameplay->get_config();
	saved_data->cur_gameplay_mode = ptr_gameplay->get_cur_gameplay_mode();
	saved_data->p1_data = *ptr_player_1;
	saved_data->p2_data = *ptr_player_2;
	saves.push_back(saved_data);

	std::cout << "Game saved to " << filename << std::endl;
	*/
}

void Game::load_saved_data()
{

}

void Game::game_process()
{
	logo_show();

	bool game_flag = true;

	GameModuleData module_code = { EN_MENU_MANAGER_CODE, EN_NONE_OPT };

	ptr_menu_manager = std::make_shared<MenuManager>(EN_MAIN_MENU);
	ptr_gameplay = std::make_shared<Gameplay>(EN_PAUSE_GAMEPLAY);

	game_modules.push(ptr_menu_manager);

	while (game_flag)
	{
		if (game_modules.empty())
			break;

		module_code = game_modules.top()->module_process(module_code.menu_option);

		switch (module_code.game_module_code)
		{
		case EN_MENU_MANAGER_CODE:
			game_modules.pop();
			game_modules.push(ptr_menu_manager);
			break;

		case EN_GAMEPLAY_CODE:
			game_modules.pop();
			game_modules.push(ptr_gameplay);
			break;

		case EN_EXIT_CODE:
			std::cout << "Bye" << std::endl;
			game_flag = false;
			break;
		}
	}
}