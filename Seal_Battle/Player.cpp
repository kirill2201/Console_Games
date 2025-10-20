#include "Player.h"

EnShipDirection Player::parse_direction(std::string direction_str)
{
	std::string cleaned;
	for (char c : direction_str) {
		cleaned += std::tolower(c);
	}

	std::string trimmed;
	for (char c : cleaned)
	{
		if (!std::isspace(c)) {
			trimmed += c;
		}
	}

	if (trimmed.empty())
	{
		throw ExceptionInvalidArgument("[Chief Officer] Captain, you didn't specify a direction! I need 'left', 'right', 'top', 'bottom', or 'reset'!");
	}

	if (trimmed == "left")
	{
		return EN_SHIP_LEFT;
	}
	else if (trimmed == "right")
	{
		return EN_SHIP_RIGHT;
	}
	else if (trimmed == "top")
	{
		return EN_SHIP_TOP;
	}
	else if (trimmed == "bottom")
	{
		return EN_SHIP_BOTTOM;
	}
	else if (trimmed == "reset")
	{
		return EN_SHIP_RESET;
	}
	else
	{
		throw ExceptionInvalidArgument("[Chief Officer] Captain, I don't understand that heading! Use 'left', 'right', 'top', 'bottom', or 'reset'!");
	}
}

void Player::parse_coordinates(const std::string& input, size_t& row, size_t& col)
{
	// Удаляем пробелы из входной строки
	std::string cleaned;
	for (char c : input) {
		if (!std::isspace(c)) {
			cleaned += c;
		}
	}

	// Проверяем длину очищенной строки
	if (cleaned.empty()) {
		throw ExceptionInvalidArgument("[Chief Officer] Captain, your order is unclear! No coordinates provided for the stern!");
	}

	// Форматы: [A-J][0-9], [a-j][0-9], [0-9][0-9], []:[] или []:[]
	size_t pos = cleaned.find(':');
	std::string first, second;

	if (pos != std::string::npos) {
		// Формат с двоеточием, например "A:1" или "1:2"
		first = cleaned.substr(0, pos);
		second = cleaned.substr(pos + 1);
	}
	else {
		// Формат без двоеточия, например "A1" или "12"
		if (cleaned.length() < 2 || cleaned.length() > 2) {
			throw ExceptionInvalidArgument("[Chief Officer] Captain, I can't make sense of this! Please specify a proper square and number, like 'A1' or '1:2'!");
		}
		first = cleaned.substr(0, 1);
		second = cleaned.substr(1, 1);
	}

	// Проверяем, что обе части не пустые
	if (first.empty() || second.empty()) {
		throw ExceptionInvalidArgument("[Chief Officer] Captain, your coordinates are incomplete! I need both a square and a number!");
	}

	// Обработка форматов
	if (std::isalpha(first[0])) {
		// Формат [A-J][0-9] или [a-j][0-9], включая "A1"
		char letter = std::toupper(first[0]);
		if (letter < 'A' || letter > 'J') {
			throw ExceptionInvalidArgument("[Chief Officer] Captain, that square is off the charts! Use letters A to J only!");
		}
		row = letter - 'A'; // A=0, B=1, ..., J=9

		// Вторая часть должна быть цифрой
		if (!std::isdigit(second[0])) {
			throw ExceptionInvalidArgument("[Chief Officer] Captain, the number for the row is missing! Give me a digit from 0 to 9!");
		}
		col = second[0] - '0';
	}
	else if (std::isdigit(first[0])) {
		// Формат [0-9][0-9]
		if (!std::isdigit(second[0])) {
			throw ExceptionInvalidArgument("[Chief Officer] Captain, if you're using numbers, both must be digits! Try again, like '12'!");
		}
		row = first[0] - '0';
		col = second[0] - '0';
	}
	else {
		throw ExceptionInvalidArgument("[Chief Officer] Captain, I can't plot that course! Use a letter A-J or a number, followed by a number!");
	}

	// Проверяем диапазон значений (0-9 для строк и столбцов)
	if (row > 9 || col > 9) {
		throw ExceptionInvalidArgument("[Chief Officer] Captain, those coordinates are beyond our map! Keep rows and columns between 0 and 9!");
	}
}

bool Player::modify_ship_hull(std::vector<Point>& ship_hull, size_t data_raw, size_t data_col)
{
	try
	{
		ptr_player_field.get()->check_coords(data_raw, data_col);
	}
	catch (const MyException& e)
	{
		throw;

		std::cerr << e.what() << std::endl;
		printf("[Chief Officer] We can\'t put our ship this way...\n");
		while (getchar() != '\n');
		ship_hull.clear();
		return false;
	}

	Point p;
	p.x = data_col;
	p.y = data_raw;

	ship_hull.push_back(p);

	return true;
}

EnSystemCode Player::set_positions(Ship& ship, std::vector<Point>& ship_hull, EnShipDirection en_ship_direction, size_t data_raw, size_t data_col)
{
	size_t ship_sz = ship.get_ship_size() - 1;

	switch (en_ship_direction)
	{
	case EN_SHIP_LEFT:
		for (size_t i = 0; i < ship_sz; i++)
		{
			data_col -= 1;

			if (!modify_ship_hull(ship_hull, data_raw, data_col))
			{
				throw ExceptionFieldCoords("[Chief Officer] We can\'t put our ship this way...");
			}
		}

		break;

	case EN_SHIP_RIGHT:
		for (size_t i = 0; i < ship_sz; i++)
		{
			data_col += 1;

			if (!modify_ship_hull(ship_hull, data_raw, data_col))
			{
				throw ExceptionFieldCoords("[Chief Officer] We can\'t put our ship this way...");
			}
		}
		break;

	case EN_SHIP_TOP:
		for (size_t i = 0; i < ship_sz; i++)
		{
			data_raw -= 1;

			if (!modify_ship_hull(ship_hull, data_raw, data_col))
			{
				throw ExceptionFieldCoords("[Chief Officer] We can\'t put our ship this way...");
			}
		}
		break;

	case EN_SHIP_BOTTOM:
		for (size_t i = 0; i < ship_sz; i++)
		{
			data_raw += 1;

			if (!modify_ship_hull(ship_hull, data_raw, data_col))
			{
				throw ExceptionFieldCoords("[Chief Officer] We can\'t put our ship this way...");
			}
		}
		break;

	case EN_SHIP_RESET:
		return EN_RESET_CODE; // написать новый Exception, который должен отменить выбор начала позиции и запросить его снова
	}

	return EN_OK_CODE;
}

EnSystemCode Player::set_ship_hull(Ship& ship, std::vector<Point>& ship_hull)
{
	std::string direction_str;
	bool c_flag = true;

	size_t data_raw = ship_hull[0].y;
	size_t data_col = ship_hull[0].x;

	while (true)
	{
		printf("[Chief Officer] Enter a direction for the bow of the ship (left, right, top, bottom, other for reset): ");
		getline(std::cin, direction_str);

		EnShipDirection en_ship_direction;

		try
		{
			en_ship_direction = parse_direction(direction_str);
		}
		catch (const MyException& e)
		{
			std::cerr << e.what() << std::endl;
			continue;
		}

		try
		{
			if (set_positions(ship, ship_hull, en_ship_direction, data_raw, data_col) == EN_RESET_CODE)
			{
				std::cout << "[Chief Officer] Denied all commands!" << std::endl;
				ship_hull.clear();

				return EN_RESET_CODE;
			}
		}
		catch (const MyException& e)
		{
			std::cerr << e.what() << std::endl;
			ship_hull.erase(ship_hull.begin() + 1, ship_hull.end());

			continue;
		}

		return EN_OK_CODE;
	}
}

void Player::set_ship_stern(Point& stern_point)
{
	size_t row, col;

	while (true)
	{
		std::string user_input;

		std::cout << ("[Chief Officer] Enter a start point for the stern of the ship (Square, Number): ");
		getline(std::cin, user_input);
		std::cout << std::endl;

		try
		{
			parse_coordinates(user_input, row, col);
		}
		catch (const MyException& e)
		{
			std::cerr << e.what() << std::endl;
			continue;
		}

		try
		{
			ptr_player_field.get()->check_coords(row, col);
		}
		catch (const MyException& e)
		{
			std::cerr << e.what() << std::endl;
			std::cerr.flush(); // !!! виснет до нажатия enter
			continue;
		}
		stern_point.x = col;
		stern_point.y = row;

		break;

		// !!! НАДО переделать цикл на возможность выхода из выбора позиции, по большому счету нужно реализовать класс меню с состояниями игры
	}
}

void Player::set_player_ship(std::shared_ptr<Ship> ship)
{
	ptr_player_field.get()->print_field_large();

	printf("\n[Chief Officer] We have to make a decision about this ship:\n\t");
	ship.get()->print_ship_info();
	printf("\n");

	std::vector<Point> ship_coords;
	Point stern_point;

	while (true)
	{
		set_ship_stern(stern_point);
		ship_coords.push_back(stern_point);

		if (ship->get_ship_size() == EN_TORPEDO_BOAT_SIZE)
			break;

		if (set_ship_hull(*ship.get(), ship_coords) == EN_OK_CODE) {
			break;
		}
	}

	ship->set_position_on_the_map(ship_coords);

	ptr_player_field.get()->put_ship_on_the_map(ship_coords);
}

void Player::set_random_location_ship(std::shared_ptr<Ship> ship) {
	srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator if not already done elsewhere.

	size_t ship_size = ship->get_ship_size();
	std::vector<Point> ship_hull;
	bool placed = false;

	while (!placed) {
		// Step 1: Generate random starting position (stern) within 0-9 for row and col.
		size_t row = rand() % 10;
		size_t col = rand() % 10;

		ship_hull.clear();
		Point stern;
		stern.x = col;
		stern.y = row;

		// Step 2: Attempt to add the stern to the hull and check if it's valid.
		try {
			ptr_player_field.get()->check_coords(row, col);
			ship_hull.push_back(stern);
		}
		catch (const MyException& e) {
			// If stern position is invalid (occupied or out of bounds), retry.
			continue;
		}

		// Step 3: If ship size is 1, it's already placed successfully.
		if (ship_size == 1) {
			placed = true;
			break;
		}

		// Step 4: Generate random direction (0-3 for LEFT, RIGHT, TOP, BOTTOM).
		EnShipDirection dir = static_cast<EnShipDirection>(rand() % 4);

		// Step 5: Try to place the rest of the hull in the chosen direction.
		size_t data_row = row;
		size_t data_col = col;
		bool valid_placement = true;

		try {
			for (size_t i = 0; i < ship_size - 1; ++i) {
				switch (dir) {
				case EN_SHIP_LEFT:
					data_col -= 1;
					break;
				case EN_SHIP_RIGHT:
					data_col += 1;
					break;
				case EN_SHIP_TOP:
					data_row -= 1;
					break;
				case EN_SHIP_BOTTOM:
					data_row += 1;
					break;
				default:
					valid_placement = false;
					break;
				}

				if (!valid_placement) {
					break;
				}

				// Use modify_ship_hull to add and check the new position.
				if (!modify_ship_hull(ship_hull, data_row, data_col)) {
					valid_placement = false;
					break;
				}
			}
		}
		catch (const MyException& e) {
			// If any exception during placement (e.g., out of bounds or occupied), retry.
			valid_placement = false;
		}

		// Step 6: If all parts placed without issues, mark as placed.
		if (valid_placement && ship_hull.size() == ship_size) {
			placed = true;
		}
		// Otherwise, loop will continue to try a new position/direction.
	}

	// Step 7: Set the position on the ship and place on the field.
	ship->set_position_on_the_map(ship_hull);
	ptr_player_field.get()->put_ship_on_the_map(ship_hull);
}

bool Player::get_fleet_damage(const Point& fire_point)
{
	// определить положение пораженного участка относительно кормы - 0-ого элемента, можно сделать через поиск точки в векторе и возврат индекса
	// выносим этот участок, hit по части корабля, высчитываем жертвы и т.д

	size_t count = 0;
	auto ptr_ship = point_to_ship_dict[fire_point];

	for (auto cmprt : ptr_ship->get_ship_coords())
	{
		if (cmprt->x == fire_point.x && cmprt->y == fire_point.y)
			break;

		count++;
	}

	ptr_ship->destroy_ship_compartment(count); // добавить проверку на уничтожение если вернет true

	this->point_count++;

	return ptr_ship->get_is_active();
}

void Player::print_player_field() const
{
	this->ptr_player_field->print_field_large();
	return;
}

const std::shared_ptr<GameField> Player::get_field() const
{
	return ptr_player_field;
}

const std::shared_ptr<GameField> Player::get_atack_field() const
{
	return this->ptr_player_atack_field;
}

const std::shared_ptr<Fleet> Player::get_fleet() const
{
	return ptr_player_fleet;
}

const std::map<Point, std::shared_ptr<Ship>>& Player::get_point_to_ship_dict() const
{
	return this->point_to_ship_dict;
}

EnPlayers Player::get_player_id() const
{
	return this->player_id;
}

size_t Player::get_point_count() const
{
	return this->point_count;
}

const std::string& Player::get_player_name() const
{
	return this->name;
}

bool Player::get_cur_state() const
{
	return this->cur_state;
}

void Player::set_cur_state(bool state)
{
	this->cur_state = state;
}

std::list<std::string>& Player::get_player_messages()
{
	return this->player_messages;
}

//----------------------------------------------------------------------------

EnMenuOptions HumanPlayer::make_turn(Point& fire_point)
{
	fire_point.x = this->fire_ptr_map.x;
	fire_point.y = this->fire_ptr_map.y;

	while (this->cur_state)
	{
		EnMenuOptions opt = user_field_input(fire_point.y, fire_point.x);

		this->fire_ptr_map.x = fire_point.x;
		this->fire_ptr_map.y = fire_point.y;

		if (opt == EN_PAUSE_GAME)
			return EN_PAUSE_GAME;

		return EN_NONE_OPT;
	}
}

void HumanPlayer::print_info(size_t row_u_ptr, size_t col_u_ptr)
{
	system("cls");

	std::string p_name = this->name;

	// Заголовки карт: ширина 31 символ, текст центрирован
	printf("+======================================================+    +======================================================+   +====================+==============+========+========+\n");
	printf("|                     Attack Map                       |    |                      Your Fleet                      |   |        Name        |      Type    |  Crew  |  Size  |\n");
	printf("|      0    1    2    3    4    5    6    7    8    9  |    |      0    1    2    3    4    5    6    7    8    9  |   |                    |              |        |        |\n");
	printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +=====================================================+\n");

	std::vector<std::string> fleet_info(Config::row_size);

	//Заполнение таблицы флота
	size_t fleet_idx = 0;
	// Вывод карт и таблицы
	wchar_t litera = L'A';

	for (size_t i = 0; i < ptr_player_fleet.get()->get_def_size() && fleet_idx < Config::row_size; ++i, ++fleet_idx)
	{
		std::string name = ptr_player_fleet.get()->get_current_fleet()[i]->get_ship_name();
		std::string ship_type = ptr_player_fleet.get()->get_current_fleet()[i]->get_ship_type_str();

		size_t crew = ptr_player_fleet.get()->get_current_fleet()[i]->get_ship_complement();
		size_t size = ptr_player_fleet.get()->get_current_fleet()[i]->get_ship_size();

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
			ptr_player_atack_field->print_row_with_u_ptr(litera, row_i, col_u_ptr, false);
		}
		else
		{
			ptr_player_atack_field->print_row(litera, row_i, false);
		}
		printf(" |    ");

		ptr_player_field->print_row(litera, row_i, this->cur_state);
		printf(" |   %s\n", fleet_info[row_i].c_str());
		litera++;

		if (row_i < Config::row_size - 1)
		{
			printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
		}
	}

	// Нижняя рамка карт
	printf("+====+====+====+====+====+====+====+====+====+====+====+    +====+====+====+====+====+====+====+====+====+====+====+   +====================+==============+========+========+\n");
	std::cout << std::endl;

	// Вывод окна лога сообщений
	// Ширина окна: 2 карты (2 * 55) + таблица (47) + пробелы (2 * 4) = 165 символов
	printf("+=============================================================================================================================================================+\n");
	printf("|                                                                  Message Log                                                                               |\n");
	printf("+=============================================================================================================================================================+\n");

	// Вывод сообщений (ограничим количеством строк, равным Config::row_size, для соответствия высоте карт)
	size_t max_messages = Config::row_size; // Максимум строк для лога
	for (std::string str : player_messages)
	{
		// Форматируем строку лога, обрезая до ширины окна (165 - 2 для рамок = 163 символа)
		std::string message = str.substr(0, 163);
		printf("| %-155s |\n", message.c_str());
	}

	// Заполняем пустые строки, если сообщений меньше, чем Config::row_size
	for (size_t i = player_messages.size(); i < max_messages; ++i)
	{
		printf("| %-155s |\n", "");
	}

	// Нижняя рамка окна лога
	printf("+=============================================================================================================================================================+\n");
	std::cout << std::endl;

	// Инструкция для игрока
	std::cout << "[Chief Officer] Captain " << p_name << ", it's your turn to fire! Use the arrow keys or W/A/S/D to move the target marker, and press Enter to fire. Press Esc to pause the game." << std::endl;
}

EnMenuOptions HumanPlayer::user_field_input(size_t& row, size_t& col)
{
	print_info(row, col);

	bool up_pressed = false;
	bool left_pressed = false;
	bool down_pressed = false;
	bool right_pressed = false;
	bool enter_pressed = false;
	bool esc_pressed = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !enter_pressed) {
			return EN_PAUSE_GAME;
		}

		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool left_current = (GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
		bool right_current = (GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000);

		bool esc_current = GetAsyncKeyState(VK_ESCAPE) & 0x8000;
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current && !up_pressed) {
			if (row > 0) {
				--row;
				print_info(row, col);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши LEFT/A
		if (left_current && !left_pressed) {
			if (col > 0) {
				--col;
				print_info(row, col);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши DOWN/S
		if (down_current && !down_pressed) {
			if (row < Config::row_size - 1) {
				++row;
				print_info(row, col);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши RIGHT/D
		if (right_current && !right_pressed) {
			if (col < Config::col_size - 1) {
				++col;
				print_info(row, col);
			}
			Sleep(150); // Задержка только после изменения
		}

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

			return EN_PAUSE_GAME;
		}
	}

	return EN_NONE_OPT;
}

void HumanPlayer::set_player_fleet()
{
	system("cls");

	bool random_location = false;

	printf("[Chief Officer] Good afternoon Cap. %s, nowdays we have to locate our fleet, let\'s start\n\n", name.c_str());
	printf("[print random for quick fleet location?] y/n: ");

	std::string ans;

	std::cin >> ans;
	std::cin.ignore(Config::max_sz_stream, '\n');

	std::cout << std::endl;

	if (ans == "y" || ans == "Y")
	{
		random_location = true;
	}

	auto fleet = ptr_player_fleet.get()->get_current_fleet();

	for (size_t i = 0; i < fleet.size(); i++)
	{
		if (!random_location)
		{
			set_player_ship(fleet[i]);
		}
		else
		{
			set_random_location_ship(fleet[i]);
		}

		auto ship_coords = fleet[i]->get_ship_coords();

		for (size_t j = 0; j < fleet[i]->get_ship_size(); j++)
		{
			Point p{ ship_coords[j]->x, ship_coords[j]->y };

			point_to_ship_dict[p] = fleet[i];
		}
	}
}

void AiPlayer::easy_mode_ai(Point& fire_point)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9); // Предполагаем поле 10x10
	size_t row = dis(gen);
	size_t col = dis(gen);

	fire_point.y = row;
	fire_point.x = col;
}

EnMenuOptions AiPlayer::make_turn(Point& fire_point)
{
	// Сделать ввод здесь, перенести его из класса Gameplay
	switch (this->difficulty_level)
	{
	case EN_EASY_AI:
		this->easy_mode_ai(fire_point);
		break;
	case EN_MIDDLE_AI:
		this->easy_mode_ai(fire_point);
		break;
	case EN_HARD_AI:
		this->easy_mode_ai(fire_point);
		break;
	}

	return EN_NONE_OPT;
}

void AiPlayer::set_player_fleet()
{
	auto fleet = ptr_player_fleet.get()->get_current_fleet();

	for (size_t i = 0; i < fleet.size(); i++)
	{
		set_random_location_ship(fleet[i]);

		auto ship_coords = fleet[i]->get_ship_coords();

		for (size_t j = 0; j < fleet[i]->get_ship_size(); j++)
		{
			Point p{ ship_coords[j]->x, ship_coords[j]->y };

			point_to_ship_dict[p] = fleet[i];
		}
	}
}