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
	system("cls");

	using json = nlohmann::json;

	// Создание директории saves, если она не существует
	const std::string save_dir = "saves";
	if (!std::filesystem::exists(save_dir)) {
		std::filesystem::create_directory(save_dir);
	}

	// Запрос имени файла
	std::string file_name;
	std::cout << "Enter filename to save (without extension): ";
	// Очистка буфера ввода
	std::cin.clear();
	std::cin.ignore(Config::max_sz_stream, '\n');
	
	std::getline(std::cin, file_name); // Используем getline вместо cin >> для корректной обработки пробелов
	std::cin >> file_name;

	if (file_name.empty()) file_name = "savegame";
	const std::string path = save_dir + "/" + file_name + ".json";

	// Сбор игроков из gameplay
	auto p1 = this->ptr_gameplay ? this->ptr_gameplay->get_ptr_player_1() : nullptr;
	auto p2 = this->ptr_gameplay ? this->ptr_gameplay->get_ptr_player_2() : nullptr;

	if (!p1 && !p2)
	{
		std::cerr << "No players available to save.\n";
		return;
	}

	json root;
	root["saved_at"] = static_cast<long long>(std::time(nullptr));

	auto serialize_field = [&](const std::shared_ptr<GameField>& gf) -> json {
		json jfield = json::array();
		if (!gf) return jfield;

		auto grid = gf->get_field(); // vector<vector<shared_ptr<FieldPoint>>>
		for (size_t r = 0; r < grid.size(); ++r)
		{
			json row_j = json::array();
			for (size_t c = 0; c < grid[r].size(); ++c)
			{
				auto fp = grid[r][c];
				json cell;
				cell["x"] = fp->get_coord_point().x;
				cell["y"] = fp->get_coord_point().y;
				cell["type"] = static_cast<int>(fp->get_type()); // serialize enum as int
				row_j.push_back(cell);
			}
			jfield.push_back(row_j);
		}
		return jfield;
		};

	auto serialize_player = [&](const std::shared_ptr<Player>& player) -> json {
		if (!player) return json();

		json pj;
		pj["player_id"] = static_cast<int>(player->get_player_id());
		pj["cur_state"] = player->get_cur_state();
		pj["point_count"] = player->get_point_count();
		pj["name"] = player->get_player_name();

		// player_messages (list -> array)
		json msgs = json::array();
		for (const auto& m : player->get_player_messages())
			msgs.push_back(m);
		pj["player_messages"] = msgs;

		// player_field and attack_field
		pj["player_field"] = serialize_field(player->get_field());
		pj["player_atack_field"] = serialize_field(player->get_atack_field());

		// fleet
		json fleet_j = json::array();
		if (auto fleet_ptr = player->get_fleet())
		{
			auto fleet = fleet_ptr->get_current_fleet();
			for (size_t si = 0; si < fleet.size(); ++si)
			{
				auto s = fleet[si];
				if (!s) continue;
				json sj;
				sj["name"] = s->get_ship_name();
				sj["type"] = s->get_ship_type_str();
				sj["crew"] = s->get_ship_complement();
				sj["size"] = s->get_ship_size();

				// coords
				json coords_j = json::array();
				auto coords = s->get_ship_coords();
				for (size_t ci = 0; ci < coords.size(); ++ci)
				{
					coords_j.push_back({ {"x", coords[ci]->x}, {"y", coords[ci]->y} });
				}
				sj["coords"] = coords_j;

				fleet_j.push_back(sj);
			}
		}
		pj["fleet"] = fleet_j;

		// point_to_ship_dict: serialize entries as { pos: {x,y}, ship_index: idx_in_fleet_or_-1 }
		json map_entries = json::array();
		auto dict = player->get_point_to_ship_dict();

		// build lookup of ship pointer -> index in fleet
		std::vector<std::shared_ptr<Ship>> fleet_lookup;
		if (auto fleet_ptr = player->get_fleet())
			fleet_lookup = fleet_ptr->get_current_fleet();

		for (const auto& kv : dict)
		{
			const Point& p = kv.first;
			const auto& ship_ptr = kv.second;

			int ship_idx = -1;
			for (size_t k = 0; k < fleet_lookup.size(); ++k)
			{
				if (fleet_lookup[k] == ship_ptr) { ship_idx = static_cast<int>(k); break; }
			}

			json me;
			me["pos"] = { {"x", p.x}, {"y", p.y} };
			me["ship_index"] = ship_idx;
			map_entries.push_back(me);
		}
		pj["point_to_ship_map"] = map_entries;

		return pj;
		};

	json players = json::array();
	if (p1) players.push_back(serialize_player(p1));
	if (p2) players.push_back(serialize_player(p2));
	root["players"] = players;

	// Запись в файл
	std::ofstream ofs(path);
	if (!ofs.is_open())
	{
		std::cerr << "Failed to open file for writing: " << path << std::endl;
		return;
	}

	ofs << std::setw(2) << root << std::endl;
	ofs.close();

	std::cout << "Game saved to: " << path << std::endl;

	std::cin >> file_name; // pause
}

void Game::load_game()
{
	system("cls");

	using json = nlohmann::json;

	// Получение списка JSON-файлов в директории saves
	const std::string save_dir = "saves";
	std::vector<std::string> json_files;

	if (std::filesystem::exists(save_dir) && std::filesystem::is_directory(save_dir)) {
		for (const auto& entry : std::filesystem::directory_iterator(save_dir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".json") {
				json_files.push_back(entry.path().stem().string());
			}
		}
	}

	// Проверка, есть ли файлы для загрузки
	if (json_files.empty()) {
		std::cout << "No save files found in directory: " << save_dir << std::endl;
		std::cout << "Press any key to return to menu...\n";
		while (!(GetAsyncKeyState(VK_RETURN) & 0x8000) && !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
			Sleep(10);
		}
		return;
	}

	// Отображение меню выбора файла
	size_t sz_files = json_files.size();
	size_t idx = 0;
	show_menu(json_files, sz_files, idx);

	// Переменные для отслеживания состояния клавиш
	bool up_pressed = false;
	bool down_pressed = false;
	bool enter_pressed = false;
	bool menu_flag = true;

	std::string file_name;

	while (menu_flag) {
		// Проверка нажатия ESC для выхода
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !enter_pressed) {
			std::cout << "Pressed ESC. Exit.\n";
			Sleep(150);

			return; // Возвращаем, чтобы выйти в меню
		}

		// Перехват стрелок и WASD
		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current && !up_pressed) {
			if (idx > 0) {
				--idx;
				show_menu(json_files, sz_files, idx);
			}
			Sleep(150); // Задержка после изменения
		}

		// Обработка нажатия клавиши ВНИЗ/S
		if (down_current && !down_pressed) {
			if (idx < sz_files - 1) {
				++idx;
				show_menu(json_files, sz_files, idx);
			}
			Sleep(150);
		}

		// Обработка нажатия ENTER
		if (enter_current && !enter_pressed) {
			// Ждем отпускания клавиши Enter
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				Sleep(10);
			}
			file_name = json_files[idx];
			menu_flag = false; // Выход из цикла меню
		}

		// Обновление состояния клавиш
		up_pressed = up_current;
		down_pressed = down_current;
		enter_pressed = enter_current;

		Sleep(10); // Основная задержка для снижения нагрузки на процессор
	}

	// Формирование пути к файлу
	if (file_name.empty()) file_name = "savegame";
	const std::string path = save_dir + "/" + file_name + ".json";

	// Открытие и парсинг файла
	std::ifstream ifs(path);
	if (!ifs.is_open())
	{
		std::cerr << "Failed to open save file: " << path << std::endl;
		return;
	}

	json root;
	try
	{
		ifs >> root;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
		return;
	}

	if (!root.contains("players") || !root["players"].is_array())
	{
		std::cerr << "Invalid save file format (missing players array)." << std::endl;
		return;
	}

	// Конструируем SavedGameplayData и добавляем в saves
	auto cfg = (this->ptr_gameplay) ? this->ptr_gameplay->get_config() : Config();

	std::shared_ptr<SavedGameplayData> saved = std::make_shared<SavedGameplayData>();
	saved->config = cfg;
	saved->cur_gameplay_mode = EN_PAUSE_GAMEPLAY;

	const auto& players_j = root["players"];

	// Вспомогательная функция для создания и заполнения игрока из JSON
	auto build_player_from_json = [&](const json& pj) -> std::shared_ptr<Player> {
		if (!pj.is_object()) return nullptr;

		int pid_int = pj.value("player_id", static_cast<int>(EN_PLAYER_1));
		EnPlayers pid = static_cast<EnPlayers>(pid_int);
		std::string pname = pj.value("name", std::string("Player"));

		// Создаем HumanPlayer (предполагаем, что в файле сохранены HumanPlayer)
		auto player = std::make_shared<HumanPlayer>(pname, pid, cfg);

		// Устанавливаем cur_state, если присутствует
		if (pj.contains("cur_state"))
		{
			player->set_cur_state(pj["cur_state"].get<bool>());
		}

		// player_messages
		if (pj.contains("player_messages") && pj["player_messages"].is_array())
		{
			auto& msgs = player->get_player_messages();
			msgs.clear();
			for (const auto& m : pj["player_messages"])
			{
				if (m.is_string()) msgs.push_back(m.get<std::string>());
			}
		}

		// Восстановление позиций флота из массива fleet
		if (pj.contains("fleet") && pj["fleet"].is_array())
		{
			auto fleet_ptr = player->get_fleet();
			if (fleet_ptr)
			{
				auto fleet = fleet_ptr->get_current_fleet();
				const auto& fleet_j = pj["fleet"];
				size_t limit = fleet.size() < fleet_j.size() ? fleet.size() : fleet_j.size();
				for (size_t si = 0; si < limit; ++si)
				{
					const auto& sj = fleet_j[si];
					if (!sj.is_object()) continue;

					// Чтение координат
					std::vector<Point> coords;
					if (sj.contains("coords") && sj["coords"].is_array())
					{
						for (const auto& c : sj["coords"])
						{
							if (c.is_object() && c.contains("x") && c.contains("y"))
							{
								size_t x = c["x"].get<size_t>();
								size_t y = c["y"].get<size_t>();
								coords.push_back(Point{ x, y });
							}
						}
					}

					// Установка координат корабля на карте
					if (!coords.empty())
					{
						try
						{
							fleet[si]->set_position_on_the_map(coords);
							player->get_field()->put_ship_on_the_map(coords);
						}
						catch (...)
						{
							// Игнорируем ошибки размещения
						}
					}
				}
			}
		}

		// Восстановление состояния player_field
		if (pj.contains("player_field") && pj["player_field"].is_array())
		{
			const auto& field_j = pj["player_field"];
			for (size_t r = 0; r < field_j.size(); ++r)
			{
				const auto& row_j = field_j[r];
				if (!row_j.is_array()) continue;
				for (size_t c = 0; c < row_j.size(); ++c)
				{
					const auto& cell = row_j[c];
					if (!cell.is_object()) continue;
					int type_int = cell.value("type", static_cast<int>(EN_EMPTY_POINT));
					EnFieldPointType t = static_cast<EnFieldPointType>(type_int);

					if (t == EN_FIRED_POINT || t == EN_DESTROY_COMPARTMENT)
					{
						Point p{ cell.value("x", c), cell.value("y", r) };
						try { player->get_field()->give_fire_point(p); }
						catch (...) { /* игнорируем */ }
					}
				}
			}
		}

		// Восстановление состояния attack_field
		if (pj.contains("player_atack_field") && pj["player_atack_field"].is_array())
		{
			const auto& field_j = pj["player_atack_field"];
			for (size_t r = 0; r < field_j.size(); ++r)
			{
				const auto& row_j = field_j[r];
				if (!row_j.is_array()) continue;
				for (size_t c = 0; c < row_j.size(); ++c)
				{
					const auto& cell = row_j[c];
					if (!cell.is_object()) continue;
					int type_int = cell.value("type", static_cast<int>(EN_EMPTY_POINT));
					EnFieldPointType t = static_cast<EnFieldPointType>(type_int);
					if (t == EN_FIRED_POINT || t == EN_DESTROY_COMPARTMENT)
					{
						Point p{ cell.value("x", c), cell.value("y", r) };
						try { player->get_atack_field()->give_fire_point(p); }
						catch (...) { /* игнорируем */ }
					}
				}
			}
		}

		// Восстановление point_to_ship_map
		if (pj.contains("point_to_ship_map") && pj["point_to_ship_map"].is_array())
		{
			auto fleet_ptr = player->get_fleet();
			std::vector<std::shared_ptr<Ship>> fleet_lookup;
			if (fleet_ptr) fleet_lookup = fleet_ptr->get_current_fleet();

			auto& dict_ref = const_cast<std::map<Point, std::shared_ptr<Ship>>&>(player->get_point_to_ship_dict());
			dict_ref.clear();
			for (const auto& me : pj["point_to_ship_map"])
			{
				if (!me.is_object()) continue;
				if (!me.contains("pos")) continue;
				const auto& pos = me["pos"];
				if (!pos.is_object() || !pos.contains("x") || !pos.contains("y")) continue;

				Point p{ pos["x"].get<size_t>(), pos["y"].get<size_t>() };
				int ship_idx = me.value("ship_index", -1);
				if (ship_idx >= 0 && static_cast<size_t>(ship_idx) < fleet_lookup.size())
				{
					dict_ref[p] = fleet_lookup[static_cast<size_t>(ship_idx)];
				}
			}
		}

		return player;
		};

	// Создание игроков
	std::shared_ptr<Player> p1 = nullptr;
	std::shared_ptr<Player> p2 = nullptr;

	if (players_j.size() > 0) p1 = build_player_from_json(players_j[0]);
	if (players_j.size() > 1) p2 = build_player_from_json(players_j[1]);

	// Сохранение в вектор saves
	saved->p1_data = p1;
	saved->p2_data = p2;

	this->saves.push_back(saved);

	std::cout << "Loaded save: " << path << " (players: " << (p1 ? 1 : 0) << ", " << (p2 ? 1 : 0) << ")\n";
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

		if (module_code.menu_option == EN_SAVE_GAME)
		{
			save_game();
		}
		else if (module_code.menu_option == EN_LOAD_GAME)
		{
			load_game();
			/*if(!this->saves.empty())
				this->ptr_gameplay->set_saves(this->saves);
			else
				module_code = { EN_MENU_MANAGER_CODE, EN_BACK_MAIN_MENU};*/
		}


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