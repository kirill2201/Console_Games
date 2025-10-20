#pragma once

#include "Config.h"

struct GameModuleData
{
	EnGameModuleCodes game_module_code;
	EnMenuOptions menu_option;
};

class GameModule
{
private:
	EnGameModuleCodes code;

public:
	GameModule(EnGameModuleCodes code): code(code) {}
	virtual ~GameModule() {}

	virtual GameModuleData module_process(EnMenuOptions option) = 0;

	EnGameModuleCodes get_code() const
	{
		return this->code;
	}
};