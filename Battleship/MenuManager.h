#pragma once

#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>

#include "GameModule.h"

class MainMenu;
class PauseMenu;
class SettingsMenu;
class LoadingMenu;

class MenuManager : public GameModule
{
private:
	EnGameTypes cur_menu_code;

	std::shared_ptr<MainMenu> main_menu;
	std::shared_ptr<PauseMenu> pause_menu;
	std::shared_ptr<SettingsMenu> settings_menu;
	std::shared_ptr<LoadingMenu> load_menu;

public:
	MenuManager(EnGameTypes st_menu_code) : cur_menu_code(st_menu_code), GameModule(EN_MENU_MANAGER_CODE)
	{
		std::vector<std::string> main_menu_str = {"continue", "new game", "load game", "settings", "exit"};
		std::vector<std::string> pause_menu_str = {"continue", "save game", "load game", "settings", "back to main menu", "exit"};
		std::vector<std::string> settings_menu_str = {"difficulty", "back to main menu"};
		std::vector<std::string> load_menu_str = {"game_1", "game_2", "game_3", "game_4", "back to main menu"};

		main_menu = std::make_shared<MainMenu>(main_menu_str, EN_MAIN_MENU);
		pause_menu = std::make_shared<PauseMenu>(pause_menu_str, EN_PAUSE_MENU);
		settings_menu = std::make_shared<SettingsMenu>(settings_menu_str, EN_SETTING_MENU);
		load_menu = std::make_shared<LoadingMenu>(load_menu_str, EN_LOAD_MENU);
	}

	GameModuleData module_process(EnMenuOptions option) override;
};

class Menu
{
	EnGameTypes menu_type;
	std::vector<std::string> words;

public:
	Menu(std::vector<std::string> words, EnGameTypes menu_type) : words(words), menu_type(menu_type) {}
	virtual ~Menu() {}

	virtual EnMenuOptions menu_process() = 0;

	virtual void show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const;
	virtual const std::vector<std::string>& get_words() const;
};

class MainMenu : public Menu
{
public:
	MainMenu(std::vector<std::string> words, EnGameTypes menu_type) : Menu(words, menu_type)
	{}

	EnMenuOptions menu_process() override;
	//void show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const override;
};

class PauseMenu : public Menu
{
public:
	PauseMenu(std::vector<std::string> words, EnGameTypes menu_type) : Menu(words, menu_type)
	{

	}

	EnMenuOptions menu_process() override;
	//void show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const override;
};

class LoadingMenu : public Menu
{
public:
	LoadingMenu(std::vector<std::string> words, EnGameTypes menu_type) : Menu(words, menu_type)
	{

	}

	EnMenuOptions menu_process() override;
	//void show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const override;
};

class SettingsMenu : public Menu
{
public:
	SettingsMenu(std::vector<std::string> words, EnGameTypes menu_type) : Menu(words, menu_type)
	{

	}

	EnMenuOptions menu_process() override;
	//void show_menu(const std::vector<std::string>& words, size_t sz_words, size_t idx) const override;
};