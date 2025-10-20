#include "MenuManager.h"

GameModuleData MenuManager::module_process(EnMenuOptions option)
{
	EnMenuOptions action_menu_key = option;

	while (true)
	{
		switch (action_menu_key)
		{
		case EN_BACK_MAIN_MENU:
			this->cur_menu_code = EN_MAIN_MENU;
			break;
		case EN_LOAD_GAME:
			this->cur_menu_code = EN_LOAD_MENU;
			break;
		case EN_PAUSE_GAME:
			this->cur_menu_code = EN_PAUSE_MENU;
			break;
		}

		switch (this->cur_menu_code)
		{
		case EN_MAIN_MENU:
			action_menu_key = this->main_menu->menu_process();
			break;
		case EN_LOAD_MENU:
			//action_menu_key = this->load_menu->menu_process();
			return GameModuleData{ EN_MENU_MANAGER_CODE, EN_LOAD_GAME };

		case EN_PAUSE_MENU:
			action_menu_key = this->pause_menu->menu_process();
			break;
		case EN_SETTING_MENU:
			action_menu_key = this->settings_menu->menu_process();
			break;
		}

		switch (action_menu_key)
		{
		case EN_PM_CONTINUE:
			return GameModuleData{ EN_GAMEPLAY_CODE, EN_PM_CONTINUE };

		case EN_PM_NEW_GAME:
			return GameModuleData{ EN_GAMEPLAY_CODE, EN_PM_NEW_GAME };

		case EN_SAVE_GAME:
			return GameModuleData{ EN_MENU_MANAGER_CODE, EN_SAVE_GAME };

		case EN_LOAD_GAME:
			return GameModuleData{ EN_MENU_MANAGER_CODE, EN_LOAD_GAME };

		case EN_SETTINGS:
			this->cur_menu_code = EN_SETTING_MENU;
			break;

		case EN_BACK_MAIN_MENU:
			this->cur_menu_code = EN_MAIN_MENU;
			break;

		case EN_EXIT_GAME:
			return GameModuleData{ EN_EXIT_CODE, EN_EXIT_GAME };
		}
	}
}

void Menu::show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const
{
	system("cls");

	for (size_t i = 0; i < sz_words; i++)
	{
		if (i == idx)
		{
			std::cout << "> ";
		}
		std::cout << words[i] << std::endl;
	}
}

const std::vector<std::string>& Menu::get_words() const
{
	return this->words;
}

EnMenuOptions MainMenu::menu_process()
{
	const std::vector<std::string>& words = this->get_words();
	size_t sz_words = words.size();
	size_t idx = 0;
	show_menu(words, sz_words, idx);

	// Переменные для отслеживания состояния клавиш
	bool up_pressed = false;
	bool down_pressed = false;
	bool enter_pressed = false;
	bool menu_flag = true;

	while (menu_flag) {
		// Проверка нажатия ESC для выхода
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !enter_pressed) {
			std::cout << "Pressed ESC. Exit.\n";
			return EN_EXIT_GAME;
		}

		// Перехват стрелок и WASD
		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current && !up_pressed) {
			if (idx > 0) {
				--idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши ВНИЗ/S
		if (down_current && !down_pressed) {
			if (idx < sz_words - 1) {
				++idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150);
		}

		// Обработка нажатия ENTER
		if (enter_current && !enter_pressed) {
			// Ждем отпускания клавиши Enter (аналог очистки буфера)
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				Sleep(10);
			}
			// Возвращаем соответствующее действие
			switch (idx) {
			case 0:
				return EN_PM_CONTINUE;
			case 1:
				return EN_PM_NEW_GAME;
			case 2:
				return EN_LOAD_GAME;
			case 3:
				return EN_SETTINGS;
			case 4:
				return EN_EXIT_GAME;
			}
		}

		// Обновление состояния клавиш
		up_pressed = up_current;
		down_pressed = down_current;
		enter_pressed = enter_current;

		Sleep(10); // Основная задержка для снижения нагрузки на процессор
	}

	return EN_EXIT_GAME; // На случай выхода из цикла
}

EnMenuOptions PauseMenu::menu_process()
{
	const std::vector<std::string>& words = this->get_words();
	size_t sz_words = words.size();
	size_t idx = 0;
	show_menu(words, sz_words, idx);

	// Переменные для отслеживания состояния клавиш
	bool up_pressed = false;
	bool down_pressed = false;
	bool enter_pressed = false;
	bool menu_flag = true;

	while (menu_flag) {
		// Проверка нажатия ESC для выхода
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !enter_pressed) {
			std::cout << "Pressed ESC. Exit.\n";
			return EN_EXIT_GAME;
		}

		// Перехват стрелок и WASD
		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current && !up_pressed) {
			if (idx > 0) {
				--idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши ВНИЗ/S
		if (down_current && !down_pressed) {
			if (idx < sz_words - 1) {
				++idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150);
		}

		// Обработка нажатия ENTER
		if (enter_current && !enter_pressed) {
			// Ждем отпускания клавиши Enter (аналог очистки буфера)
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				Sleep(10);
			}
			// Возвращаем соответствующее действие
			// "continue", "save game", "load game", "settings", "back to main menu", "exit"
			switch (idx) {
			case 0:
				return EN_PM_CONTINUE;
			case 1:
				return EN_SAVE_GAME;
			case 2:
				return EN_LOAD_GAME;
			case 3:
				return EN_SETTINGS;
			case 4:
				return EN_BACK_MAIN_MENU;
			case 5:
				return EN_EXIT_GAME;
			}
		}

		// Обновление состояния клавиш
		up_pressed = up_current;
		down_pressed = down_current;
		enter_pressed = enter_current;

		Sleep(10); // Основная задержка для снижения нагрузки на процессор
	}

	return EN_EXIT_GAME; // На случай выхода из цикла
}

EnMenuOptions SettingsMenu::menu_process()
{
	const std::vector<std::string>& words = this->get_words();
	size_t sz_words = words.size();
	size_t idx = 0;
	show_menu(words, sz_words, idx);

	// Переменные для отслеживания состояния клавиш
	bool up_pressed = false;
	bool down_pressed = false;
	bool enter_pressed = false;
	bool menu_flag = true;

	while (menu_flag) {
		// Проверка нажатия ESC для выхода
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !enter_pressed) {
			std::cout << "Pressed ESC. Exit.\n";
			return EN_EXIT_GAME;
		}

		// Перехват стрелок и WASD
		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current && !up_pressed) {
			if (idx > 0) {
				--idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши ВНИЗ/S
		if (down_current && !down_pressed) {
			if (idx < sz_words - 1) {
				++idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150);
		}

		// Обработка нажатия ENTER
		if (enter_current && !enter_pressed) {
			// Ждем отпускания клавиши Enter (аналог очистки буфера)
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				Sleep(10);
			}
			// Возвращаем соответствующее действие
			// "difficulty", "back to main menu"
			switch (idx) {
			case 0:
				return EN_DIFFICULTY;
			case 1:
				return EN_BACK_MAIN_MENU;
			}
		}

		// Обновление состояния клавиш
		up_pressed = up_current;
		down_pressed = down_current;
		enter_pressed = enter_current;

		Sleep(10); // Основная задержка для снижения нагрузки на процессор
	}

	return EN_EXIT_GAME; // На случай выхода из цикла
}

EnMenuOptions LoadingMenu::menu_process()
{
	const std::vector<std::string>& words = this->get_words();
	size_t sz_words = words.size();
	size_t idx = 0;
	show_menu(words, sz_words, idx);

	// Переменные для отслеживания состояния клавиш
	bool up_pressed = false;
	bool down_pressed = false;
	bool enter_pressed = false;
	bool menu_flag = true;

	while (menu_flag) {
		// Проверка нажатия ESC для выхода
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !enter_pressed) {
			std::cout << "Pressed ESC. Exit.\n";
			return EN_EXIT_GAME;
		}

		// Перехват стрелок и WASD
		bool up_current = (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000);
		bool down_current = (GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000);
		bool enter_current = GetAsyncKeyState(VK_RETURN) & 0x8000;

		// Обработка нажатия клавиши ВВЕРХ/W
		if (up_current && !up_pressed) {
			if (idx > 0) {
				--idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150); // Задержка только после изменения
		}

		// Обработка нажатия клавиши ВНИЗ/S
		if (down_current && !down_pressed) {
			if (idx < sz_words - 1) {
				++idx;
				show_menu(words, sz_words, idx);
			}
			Sleep(150);
		}

		// Обработка нажатия ENTER
		if (enter_current && !enter_pressed) {
			// Ждем отпускания клавиши Enter (аналог очистки буфера)
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				Sleep(10);
			}
			// Возвращаем соответствующее действие
			// "difficulty", "back to main menu"
			switch (idx) {
			default:
				return EN_BACK_MAIN_MENU;
			}
		}

		// Обновление состояния клавиш
		up_pressed = up_current;
		down_pressed = down_current;
		enter_pressed = enter_current;

		Sleep(10); // Основная задержка для снижения нагрузки на процессор
	}

	return EN_EXIT_GAME; // На случай выхода из цикла
}